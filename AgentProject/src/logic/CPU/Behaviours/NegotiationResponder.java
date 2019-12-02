package logic.CPU.Behaviours;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.text.DecimalFormat;

import jade.core.AID;
import jade.domain.FIPANames;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import jade.proto.ContractNetResponder;
import logic.Bid;
import logic.CompilationFile;
import logic.CompiledProject;
import logic.Macros;
import logic.Pair;
import logic.ProjectInfo;
import logic.CPU.CPU;


public class NegotiationResponder extends ContractNetResponder
{
	CPU agent;
	AID clientName;
	ProjectInfo info;
	Bid deadline;
	File data; // Reject,tamanhoProj,nFicheirosProj,tempoCompila��oFicheiro,tempoM�dioAtraso,\n
	
	public NegotiationResponder(CPU agent)
	{
		super(agent, MessageTemplate.MatchProtocol(FIPANames.InteractionProtocol.FIPA_CONTRACT_NET));
		
		this.agent = agent;
		
		data = new File("Info.csv");
		try {
			data.createNewFile();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} // if file already exists will do nothing 
	}
	
	@Override
	protected ACLMessage handleCfp(ACLMessage cfp)
	{
		clientName = cfp.getSender();
		
		if (selectProject(cfp))
		{
			agent.println("Received a proposal from \"" + clientName.getLocalName() + "\" for project \"" + info.name + "\"");			
			return createProposeResponse();
		}
		
		return createRefuseResponse();
	}
	
	protected ACLMessage handleAcceptProposal(ACLMessage cfp, ACLMessage propose, ACLMessage accept)
	{
    	CompiledProject cp = new CompiledProject(info.deadline);
    	boolean failed = false;
    	
        for (int i = 0; i < info.toBeCompiled.size(); i++)
        {
        	int index = info.toBeCompiled.get(i);
        	CompilationFile cf = info.files.get(index);
        	
        	if (cf.getBinary() == null && cf.extension.equals(Macros.codeFileExtension)) // Not already compiled code file
        	{        		
        		if (cf.compile())
            		agent.println("Successfully compiled " + cf.getFilename());
        		else
        		{
        			failed = true;
            		agent.errorPrintln("Failed to compile " + cf.getFilename());        			
        		}
            	
        		saveCompilationTime(cf);       		
        		cp.addCompiledFile(cf);
        	}
		}
        
        if (failed)
        	agent.errorPrintln("Failed to compile project \"" + info.name + "\"!");
        else
        	agent.println("Successfully compiled project \"" + info.name + "\" in " + new DecimalFormat("#.00").format(cp.totalCompilationTime) + " seconds");
		
		return createCompiledProjectResponse(cp);
	}
	
	protected void handleRejectProposal(ACLMessage cfp, ACLMessage propose, ACLMessage reject)
	{
		agent.errorPrintln("Negotiation from \"" + reject.getSender().getLocalName() + "\" is rejected!");
		
		try(FileWriter fw = new FileWriter(data.getPath(), true);
			    BufferedWriter bw = new BufferedWriter(fw);
			    PrintWriter out = new PrintWriter(bw))
			{			
				out.println("Reject,"+ info.getProjectTotalSize() + "," + info.files.size() + ",0," +"tempoM�dioAtraso");
			    //more code
			} catch (IOException e) {
			    //exception handling left as an exercise for the reader
			}
	}
	
	
	public void saveCompilationTime(CompilationFile cf)
	{
		agent.compilationTimes.add(new Pair<Double, Integer>(cf.getCompilationTime(), new Integer(cf.text.length())));
		
		if (agent.compilationTimes.size() > CPU.compilationTimesSize)
			agent.compilationTimes.remove(0);
		
		try(FileWriter fw = new FileWriter(data.getPath(), true);
			    BufferedWriter bw = new BufferedWriter(fw);
			    PrintWriter out = new PrintWriter(bw))
			{			
				out.println("Accept," + info.getProjectTotalSize() +"," + info.files.size() +","+ cf.getCompilationTime() +",tempoM�dioAtraso");
			} catch (IOException e) {
			    //exception handling left as an exercise for the reader
			}
	}
	
	
	public boolean selectProject(ACLMessage msg)
	{
		info = ProjectInfo.deserialize(msg.getByteSequenceContent());
		
		if (info == null)
		{
			agent.errorPrintln("Failed to receive ProjectInfo");
			return false;
		}
		
		if (!saveProject())
		{
			agent.errorPrintln("Failed to save project " + info.name + "!");
			return false;
		}
		
		return true;
	}
	
	public boolean saveProject()
	{
		String projectName = info.name;
		agent.projectPath = Macros.cpuProjectPath + File.separator + clientName.getLocalName() + File.separator + projectName;
		createProjectFolder();
		
		for (int i = 0; i < info.files.size(); i++)
		{
			CompilationFile cf = info.files.get(i);
			cf.path = agent.projectPath;
						
			File f = new File(agent.projectPath + File.separator + cf.getFilename());
					
			try
			{	
				Files.write(f.toPath(), cf.getText().getBytes(), StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
			}
			catch (IOException e)
			{
				e.printStackTrace();
				return false;
			}
		}	
		
		return true;
	}

	public boolean createProjectFolder()
	{
		return new File(agent.projectPath).mkdirs();
	}
	
	private ACLMessage createProposeResponse()
	{
		ACLMessage msg = new ACLMessage(ACLMessage.PROPOSE);
		msg.setProtocol(FIPANames.InteractionProtocol.FIPA_CONTRACT_NET);
		msg.setContent(calculateNewProposedDeadline());
		agent.println("CPU sending PROPOSE: " + msg.getContent());
		msg.addReceiver(clientName);
		
		return msg;
	}
	
	private ACLMessage createRefuseResponse()
	{
		ACLMessage msg = new ACLMessage(ACLMessage.REFUSE);
		msg.setProtocol(FIPANames.InteractionProtocol.FIPA_CONTRACT_NET);
		msg.setContent("Failed to save project!");
		agent.println("CPU sending REFUSE: " + msg.getContent());
		msg.addReceiver(clientName);
		
		return msg;
	}

	public String calculateNewProposedDeadline()
	{
		double average = agent.getAverageCPUCompilationTimes();
		
		int deadline = info.deadline.getDeadlineInMilliSeconds();
		int numBytes = info.calculateCompileNumBytes();
		double predictedCompilationTime = numBytes/average * 1000;
		
		if (average == 0.0 || predictedCompilationTime <= deadline)
		{
			// ACCEPT
			agent.acceptableDeadline = true;
			return Macros.deadlineAcceptable;
		}
		else
		{
			// Calculate new deadline (Caculates the new deadline by selecting a uniform random time between -15% to +15% of the predictedCompilationTime
			double variance = 0.15;
			int newDeadLine = (int)((Math.random()-0.05) * variance * 2 * predictedCompilationTime + predictedCompilationTime);			
			info.deadline = new Bid(new Integer(newDeadLine).toString() + "ms");
			agent.println("Received deadline: " + deadline + " ms, proposing " + newDeadLine + "ms");
			return new Integer(newDeadLine).toString() + "ms";
		}
	}
	
	private ACLMessage createCompiledProjectResponse(CompiledProject cp)
	{
		ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
		msg.setProtocol(FIPANames.InteractionProtocol.FIPA_CONTRACT_NET);
		msg.setByteSequenceContent(cp.serialize());
		agent.println("CPU sending INFORM: " + "CompiledProject " + info.name);
		msg.addReceiver(clientName);
		
		return msg;
	}
}