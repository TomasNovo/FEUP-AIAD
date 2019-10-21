package logic;

import java.io.File;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.lang.acl.ACLMessage;

import logic.Macros;
import logic.Auction.Bid;

public class Client extends ExtendedAgent
{
	int id = 0;
	ArrayList<CompilationFile> files;
	DFAgentDescription[] CPUs;
	String projectPath;
	String deadline;
	Bid b;
	
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
		println("Hey! Its me, " + getAID().getName());
		
		Object[] args = getArguments();
		
		if(args != null && args.length > 0 && args.length == 2) 
        {
			projectPath = args[0].toString();
            System.out.println("ProjectPath: "+ projectPath);
            
            deadline = args[1].toString();
            System.out.println("Deadline: "+ deadline);
            
            b = new Bid(this, deadline);
        
    		addBehaviour(new OfferProjectBehaviour(projectPath));
        }
	}
	
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
			
//			if (!findCPUs())
//				errorPrintln("Failed to find CPUs!");
//			
//			sendClientAID();
//			
//			if (sendFileToCompile())
//				sentClient = true;
			
			addBehaviour(new ReceiveCompilationFilesBehaviour());
		}
		
		public boolean publishProject()
		{
			DFAgentDescription dfad = new DFAgentDescription();
			ServiceDescription sd = new ServiceDescription();
			
			sd.setName(filepath);
			sd.setType("project");
			
    		Property p = new Property(); // Sets project deadline
    		p.setName("dealine");
    		p.setValue(new Integer(b.getDeadlineInSeconds()));
    		
    		p = new Property(); // Sets the project name
    		p.setName("name");
    		p.setValue(filepath);
			
	        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(filepath)))
	        {
	            for (Path child : dirStream)
	            {
	            	if (child.toFile().getName().contains(Macros.codeFileExtension))
	            	{
	            		CompilationFile cf = new CompilationFile(child.toFile());
	            		files.add(cf);
	            		
	            		p = new Property();
	            		
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
	
	class ReceiveCompilationFilesBehaviour extends Behaviour
	{
		@Override
		public void action()
		{
			for	(int i = 0; i < files.size(); i++) // Iterates through every file to receive the binary
			{
				ACLMessage msg = blockingReceive();
				String filename = msg.getUserDefinedParameter("filename");
				
				boolean found = false;
				
				for	(int j = 0; j < files.size(); j++)
				{
					if (files.get(j).filename.equals(filename)) // Sets the binary to the respective CompilationFile
					{
						CompilationFile cf = files.get(i);
						cf.binary = msg.getByteSequenceContent();
						files.set(j, cf);
						
						if (!cf.saveBinary())
						{
							errorPrintln("Failed to save binary!");
							return;
						}
						
						found = true;
						break;
					}
				}
				
				if (!found)
				{
					errorPrintln("Failed to find respective CompilationFile!");
					return;
				}
			}
			
			println("Successfully received compilation files");
			
		}
		

		@Override
		public boolean done()
		{
			return true;
		}
		
	}

	
}
