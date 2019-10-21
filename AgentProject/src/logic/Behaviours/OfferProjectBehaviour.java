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
import logic.CompilationFile;
import logic.Macros;
import logic.Client.ReceiveCompilationFilesBehaviour;

class OfferProjectBehaviour extends Behaviour
{
	boolean sentClient = false;
	String filepath;
	
	public OfferProjectBehaviour(String f)
	{
		this.filepath = f;
	}
	
	@Override
	public void action()
	{
		publishProject();
		
//		if (!findCPUs())
//			errorPrintln("Failed to find CPUs!");
//		
//		sendClientAID();
//		
//		if (sendFileToCompile())
//			sentClient = true;
		
		addBehaviour(new ReceiveCompilationFilesBehaviour());
	}
	
	public boolean publishProject()
	{
		DFAgentDescription dfad = new DFAgentDescription();
		ServiceDescription sd = new ServiceDescription();
		
		sd.setName(filepath);
		sd.setType("project");
		
        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(filepath)))
        {
            for (Path child : dirStream)
            {
            	if (child.toFile().getName().contains(Macros.codeFileExtension))
            	{
            		CompilationFile cf = new CompilationFile(child.toFile());
            		files.add(cf);
            		
            		Property p = new Property();
            		
            		p.setName(cf.filename);
            		p.setValue(cf);
            		
            		sd.addProperties(p);
            	}
    		}
            
			dfad.addServices(sd);
			DFService.modify(this.myAgent, this.myAgent.getAID(), dfad);
            
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
			CPUs = DFService.search(this.myAgent, dfad);
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
		msg.setContent(getAID().getName());
		msg.addReceiver(CPUs[0].getName());
		send(msg);
	}
	
	public boolean sendFileToCompile()
	{
		files = new ArrayList<CompilationFile>();
		
        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(filepath)))
        {
            for (Path child : dirStream)
            {
            	if (child.toFile().getName().contains(Macros.codeFileExtension))
            		files.add(new CompilationFile(child.toFile()));
    		}
            
        }
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}
		
        byte[] fileContent = null;
		
		for (int i = 0; i < files.size(); i++)
		{
			CompilationFile cf = files.get(i);
			
			ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
			msg.addReceiver(CPUs[0].getName());
			msg.setByteSequenceContent(cf.text.getBytes());
			msg.addUserDefinedParameter("filename", cf.filename);
			send(msg);
		}
		
		return true;
	}
	
	@Override
	public boolean done()
	{
		return sentClient;
	}
	
}
