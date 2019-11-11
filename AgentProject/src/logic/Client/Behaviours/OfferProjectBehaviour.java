package logic.Client.Behaviours;

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
		DFAgentDescription dfad = new DFAgentDescription();
		ServiceDescription sd = new ServiceDescription();
		
		sd.setName(agent.projectName);
		sd.setType("project");
		
		Property p = new Property("deadline", new Integer(agent.b.getDeadlineInSeconds()).toString()); // Sets project deadline
		sd.addProperties(p);
		
        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(agent.projectPath)))
        {
            for (Path child : dirStream)
            {
            	String filename = child.toFile().getName();
            	if (filename.endsWith(Macros.codeFileExtension) || filename.endsWith(Macros.headerFileExtension))
            	{
            		CompilationFile cf = new CompilationFile(child.toFile());
            		
            		if (filename.endsWith(Macros.codeFileExtension))
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
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}
