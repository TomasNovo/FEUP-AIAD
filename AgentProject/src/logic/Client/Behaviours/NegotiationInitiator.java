package logic.Client.Behaviours;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Vector;

import jade.core.AID;
import jade.domain.FIPANames;
import jade.lang.acl.ACLMessage;
import jade.proto.ContractNetInitiator;
import logic.Bid;
import logic.CompilationFile;
import logic.CompiledProject;
import logic.CompiledProjectErrorType;
import logic.Macros;
import logic.ProjectInfo;
import logic.Client.Client;

public class NegotiationInitiator extends ContractNetInitiator
{

	Client agent;	
	boolean received = false;
	ProjectInfo info;
	AID cpuName;

	
	public NegotiationInitiator(Client agent, ProjectInfo info, AID cpuName)
	{
		super(agent, null);
		this.agent = agent;
		this.info = info;
		this.cpuName = cpuName;
		
		agent.initializeClient();		
	}
	
	@Override
	protected Vector<ACLMessage> prepareCfps(ACLMessage cfp)
	{
		Vector<ACLMessage> v = new Vector<ACLMessage>();
		
		v.add(createCfpMessage());
		
		return v;
	}
	
	@Override
	protected void handlePropose(ACLMessage propose, Vector acceptances)
	{
		Vector<ACLMessage> newAcceptances = (Vector<ACLMessage>) acceptances;
		
		ACLMessage msg = propose.createReply();

    	if (propose.getContent().equals(Macros.deadlineAcceptable))
    	{
    		msg.setPerformative(ACLMessage.ACCEPT_PROPOSAL);
    		newAcceptances.addElement(msg);
    	}
    	else
    	{
    		Bid bcpu = new Bid(agent, propose.getContent());	
    		agent.println("Client received: " + propose.getContent());
			boolean result = agent.checkCPUProposal(bcpu, info.deadline);
						
			if (result)
			{
	    		msg.setPerformative(ACLMessage.ACCEPT_PROPOSAL);
				newAcceptances.addElement(msg);
			}
			else 
			{			
//				// Remove cpu from list
//				agent.cpus.remove(cpuIndex);
				
	    		msg.setPerformative(ACLMessage.REJECT_PROPOSAL);
				newAcceptances.addElement(msg);
			}
    	}
	}
	
	@Override
	protected void handleRefuse(ACLMessage refuse)
	{
		AID cpuName = refuse.getSender();
		agent.errorPrintln("Received refuse from " + cpuName.getLocalName() + "!");
	}
	
	@Override
	protected void handleInform(ACLMessage inform)
	{
		AID cpuName = inform.getSender();
		CompiledProject cp = CompiledProject.deserialize(inform.getByteSequenceContent());
		
		if (cp.errorType == CompiledProjectErrorType.COMPILATIONERROR)
		{
			agent.errorPrintln("CPU \"" + cpuName + "\" generated a compilation error!");
			agent.successfulProject = false;
			return;
		}
		
		if (cp.errorType == CompiledProjectErrorType.DEADLINEEXCEEDED)
		{
			agent.errorPrintln("CPU \"" + cpuName + "\" exceeded the deadline!");
			agent.successfulProject = false;
			return;
		}
		
		// Iterate compiledFiles and save the binary on a successful CompiledProject
		for (int j = 0; j < cp.compiledFiles.size(); j++)
		{
			String filename = cp.compiledFiles.get(j).first;
			int fileIndex = searchFile(filename);
			if (fileIndex == -1)
			{
				agent.errorPrintln("Failed to find respective CompilationFile!");
				continue;
			}
			
			CompilationFile cf = agent.info.files.get(fileIndex);
			cf.setBinary(cp.compiledFiles.get(j).second);
			
			if (!saveBinary(cf))
			{
				agent.errorPrintln("Failed to save binary!");
				continue;
			}
			
			agent.projectFiles.add(cf.path + "/" + cf.filenameNoExtention + Macros.binaryFileExtension);
		}
		
		if (agent.projectFiles.size() == agent.info.toBeCompiled.size())
		{
			linkProject();
		}
	}


	
	private ACLMessage createCfpMessage()
	{
		ACLMessage msg = new ACLMessage(ACLMessage.CFP);
		msg.setProtocol(FIPANames.InteractionProtocol.FIPA_CONTRACT_NET);
		msg.addReceiver(cpuName);
		msg.setByteSequenceContent(info.serialize());
		
		return msg;
	}

	public boolean saveBinary(CompilationFile cf)
	{
		try
		{
			Files.write(Paths.get(cf.path + "/" + cf.filenameNoExtention + Macros.binaryFileExtension), cf.getBinary(), StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
		}
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}
		
		return true;
	}
	
	private int searchFile(String filename)
	{
		for	(int i = 0; i < agent.info.files.size(); i++)
		{
			if (agent.info.files.get(i).getFilename().equals(filename)) // Sets the binary to the respective CompilationFile
				return i;
		}
		
		return -1;
	}
	
	public boolean linkProject()
	{
		try
		{
			String execName = "main";
			String command = "g++ -o " + agent.projectPath + "/" + execName;
			
			for (int i = 0; i < agent.projectFiles.size(); i++)
			{
				command += " " + agent.projectFiles.get(i);
			}
			
			Process process;
			process = Runtime.getRuntime().exec(command);
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
			
			while (process.isAlive())
			{}
			
			String line;
			while ((line = reader.readLine()) != null)
			{
				System.err.println(line);
			}
			
			int returnValue = process.exitValue();

			if (returnValue != 0)
			{
				agent.errorPrintln("Failed to link!");
				return false;
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		
		agent.println("Successfully built project " + agent.projectName);
		return true;
	}
}