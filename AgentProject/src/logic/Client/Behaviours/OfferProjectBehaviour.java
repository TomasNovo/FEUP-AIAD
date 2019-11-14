package logic.Client.Behaviours;

import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
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
import logic.Client.Behaviours.ReceiveCompiledFilesBehaviour;
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
		agent.files = new ArrayList<CompilationFile>();
		
		publishProject();
		
		agent.addBehaviour(new ReceiveCompiledFilesBehaviour());
	}
	
	public boolean publishProject()
	{		
		ProjectInfo baseInfo = new ProjectInfo();
		baseInfo.name = agent.projectName;
		baseInfo.deadline = agent.deadline;

        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(agent.projectPath)))
        {
        	// Add files to agent and to info
            for (Path child : dirStream)
            {
            	String filename = child.toFile().getName();
            	if (filename.endsWith(Macros.codeFileExtension) || filename.endsWith(Macros.headerFileExtension))
            	{
            		CompilationFile cf = new CompilationFile(child.toFile());
            		
            		if (filename.endsWith(Macros.codeFileExtension))
            			agent.files.add(cf);
            		
            		baseInfo.files.add(cf);
            	}
    		}
            
            baseInfo.timestamp = new Long(System.currentTimeMillis());
            DFAgentDescription[] cpus = agent.searchDF("CPU");
            ProjectInfo[] infos = new ProjectInfo[cpus.length];
            
            // Initialize ProjectInfos, one for each CPU
            for (int i = 0; i < infos.length; i++)
            {
            	infos[i] = baseInfo.Clone();
            }
            
            // Randomly assign code CompilationFiles to CPUs. Only the CompilationFiles in agent.files are to be compiled (.cpp)
            for (int i = 0; i < baseInfo.files.size(); i++)
            {
            	if (baseInfo.files.get(i).filename.endsWith(Macros.codeFileExtension))
            	{            		
                	int randomCPU = (int)(Math.random() * infos.length);	
                	infos[randomCPU].toBeCompiled.add(i);
            	}
            }
            
            /* TODO: Calculate deadline
             * 
             * 
             */
    		
    		for (int i = 0; i < infos.length; i++)
    		{
    			DFAgentDescription dfad = cpus[i];
    			AID cpuName = dfad.getName();
    			
    			sendProjectInfo(cpuName, infos[i]);
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
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}
