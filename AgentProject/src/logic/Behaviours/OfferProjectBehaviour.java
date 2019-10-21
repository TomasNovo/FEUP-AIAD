package logic.Behaviours;

import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.lang.acl.ACLMessage;
import logic.Client;
import logic.CompilationFile;
import logic.Macros;
import logic.Behaviours.ReceiveCompiledFilesBehaviour;;

public class OfferProjectBehaviour extends Behaviour
{
	Client agent;
	
	boolean sentClient = false;
	String projectPath;
	
	public OfferProjectBehaviour(String f)
	{
		this.projectPath = f;
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
		DFAgentDescription dfad = new DFAgentDescription();
		ServiceDescription sd = new ServiceDescription();
		
		sd.setName(projectPath);
		sd.setType("project");
		
		Property p = new Property("deadline", new Integer(agent.b.getDeadlineInSeconds()).toString()); // Sets project deadline
		sd.addProperties(p);
		
        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(Macros.clientProjectPath + "/" + projectPath)))
        {
            for (Path child : dirStream)
            {
            	if (child.toFile().getName().contains(Macros.codeFileExtension))
            	{
            		CompilationFile cf = new CompilationFile(child.toFile());
            		agent.files.add(cf);
            		
            		p = new Property("file", cf.serialize());
            		sd.addProperties(p);
            	}
    		}
            
			dfad.addServices(sd);
			DFService.modify(this.myAgent, dfad);
            
        }
		catch (IOException | FIPAException e)
		{
			e.printStackTrace();
			return false;
		}			
		
		return true;
	}
	
	public boolean findCPUs()
	{
		DFAgentDescription dfad = new DFAgentDescription();
		
		ServiceDescription sd = new ServiceDescription();
		sd.setType("CPU");
		dfad.addServices(sd);
		
		try
		{
			agent.CPUs = DFService.search(this.myAgent, dfad);
		}
		catch (FIPAException e)
		{
			e.printStackTrace();
			return false;
		}
		
		return true;
	}

	public void sendClientAID()
	{
		ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
		msg.setContent(agent.getAID().getName());
		msg.addReceiver(agent.CPUs[0].getName());
		agent.send(msg);
	}
	
	public boolean sendFileToCompile()
	{
		agent.files = new ArrayList<CompilationFile>();
		
        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(projectPath)))
        {
            for (Path child : dirStream)
            {
            	if (child.toFile().getName().contains(Macros.codeFileExtension))
            		agent.files.add(new CompilationFile(child.toFile()));
    		}
            
        }
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}
		
        byte[] fileContent = null;
		
		for (int i = 0; i < agent.files.size(); i++)
		{
			CompilationFile cf = agent.files.get(i);
			
			ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
			msg.addReceiver(agent.CPUs[0].getName());
			msg.setByteSequenceContent(cf.getText().getBytes());
			msg.addUserDefinedParameter("filename", cf.getFilename());
			agent.send(msg);
		}
		
		return true;
	}
	
	@Override
	public boolean done()
	{
		return sentClient;
	}
	
}
