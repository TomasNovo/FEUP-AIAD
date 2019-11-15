package logic.Client.Behaviours;

import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.Macros;
import logic.ProjectInfo;
import logic.Auction.Bid;
import logic.Client.Behaviours.ReceiveCompiledFilesBehaviour;
import logic.Client.Behaviours.Negotiation.ReceiveNegotiationBehaviour;
import logic.Client.Client;;

public class OfferProjectBehaviour extends Behaviour
{
	Client agent;	
	boolean sentClient = false;
	
	public OfferProjectBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (Client) myAgent;
		
		publishProject();
	}
	
	public boolean publishProject()
	{		
		agent.info = new ProjectInfo();
		agent.info.name = agent.projectName;
		agent.info.deadline = agent.deadline;
		
        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(agent.projectPath)))
        {
        	// Add files to agent and to info
    		int fileIndex = 0;
            for (Path child : dirStream)
            {
            	String filename = child.toFile().getName();
            	if (filename.endsWith(Macros.codeFileExtension) || filename.endsWith(Macros.headerFileExtension))
            	{
            		CompilationFile cf = new CompilationFile(child.toFile());
            		
            		if (filename.endsWith(Macros.codeFileExtension))
                		agent.info.toBeCompiled.add(new Integer(fileIndex));
            		
            		agent.info.files.add(cf);
            		fileIndex++;
            	}
    		}
            
            agent.info.timestamp = new Long(System.currentTimeMillis());
            agent.cpus = new ArrayList<DFAgentDescription>(Arrays.asList(agent.searchDF("CPU")));
            ArrayList<ProjectInfo> infos = new ArrayList<ProjectInfo>();
            
            // Initialize ProjectInfos, one for each CPU
            for (int i = 0; i < agent.cpus.size(); i++)
            {
            	infos.add(agent.info.Clone());
            	infos.get(i).toBeCompiled = new ArrayList<Integer>();
            }
            
            // Randomly assign code CompilationFiles to CPUs. Only the CompilationFiles in agent.files are to be compiled (.cpp)
            // TODO: Balance this random assignment
            for (int i = 0; i < agent.info.files.size(); i++)
            {
            	if (agent.info.files.get(i).filename.endsWith(Macros.codeFileExtension))
            	{            		
                	int randomCPU = (int)(Math.random() * infos.size());	
                	infos.get(randomCPU).toBeCompiled.add(i);
            	}
            }
    		
    		for (int i = 0; i < infos.size(); i++)
    		{
    			DFAgentDescription dfad = agent.cpus.get(i);
    			AID cpuName = dfad.getName();
    			
    			if (infos.get(i).toBeCompiled.size() == 0)
    			{
    				agent.cpus.remove(i);
    				infos.remove(i);
    				i--;
    				continue;    				
    			}
    			
    			infos.get(i).deadline = calculateDeadline(infos.get(i));
    			
    			sendProjectInfo(cpuName, infos.get(i));
    			agent.addBehaviour(new ReceiveNegotiationBehaviour());
    		}
    		
        }
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}			
		
		return true;
	}
	
	private void sendProjectInfo(AID cpuName, ProjectInfo info)
	{		
		ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
		msg.addReceiver(cpuName);
		msg.setByteSequenceContent(info.serialize());
		agent.send(msg);
	}
	
	private Bid calculateDeadline(ProjectInfo info)
	{
		int projectNumBytes = agent.info.calculateCompileNumBytes();
		int proposalNumBytes = info.calculateCompileNumBytes();
		int estimatedCompilationTime = (int)((double)agent.deadline.getDeadlineInMilliSeconds() / (double)projectNumBytes * (double)proposalNumBytes);
		
		return new Bid(estimatedCompilationTime + "ms");
	}
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}
