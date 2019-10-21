package logic;

import java.io.File;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Iterator;

import logic.CompilationFile;

import javax.swing.JOptionPane;

import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.lang.acl.ACLMessage;

public class CPU extends ExtendedAgent
{
	int id = 0;
	ArrayList<CompilationFile> files;
	String projectPath;
	
	AID clientAID;
	boolean clientFolder;
	
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
		new File("CPU-Projects").mkdirs();
		
		addBehaviour(new ReceiveProjectBehaviour());
		
		println("Ola!");
	}

	
	class ReceiveProjectBehaviour extends Behaviour
	{
		String pathToFolder;
		
		public ReceiveProjectBehaviour()
		{
			files = new ArrayList<CompilationFile>();
		}
		
		@Override
		public void action()
		{
			if (!selectProject()) 
			{
				errorPrintln("ERROR: CPU: Error receiving file");
				return;
			}
		
			addBehaviour(new CompileProjectBehaviour(pathToFolder));
		}
		
		public boolean selectProject()
		{
			DFAgentDescription dfad = new DFAgentDescription();
			ServiceDescription sd = new ServiceDescription();
			sd.setType("project");
			dfad.addServices(sd);
			
			DFAgentDescription[] projects;
			
			try
			{
				projects = DFService.search(this.myAgent, dfad);
			}
			catch (FIPAException e)
			{
				e.printStackTrace();
				return false;
			}
			
			DFAgentDescription project = null;
			Integer deadline = null;
			
			for (int i = 0; i < projects.length; i++) // Searches for the project with the lowest deadline
			{
				dfad = projects[i];
				sd = (ServiceDescription) dfad.getAllServices().next();
				
				for (Iterator it = sd.getAllProperties(); it.hasNext();) // Gets the deadline property of the service and saves it if it is lower than the current one
				{
					Property p = (Property) it.next();
					
					if (p.getName().equals("deadline"))
					{
						if (project == null || (Integer)p.getValue() < deadline)
						{
							project = dfad;
							deadline = (Integer)p.getValue();
						}
					}
					
					break;
				}
			}
			
			  
			return saveProject(project);
		}
		
		public boolean saveProject(DFAgentDescription project)
		{
			ServiceDescription sd = (ServiceDescription) project.getAllServices().next();
			String projectName = sd.getName();
			createFileFolder(projectName);
			
			for (Iterator it = sd.getAllProperties(); it.hasNext();)
			{
				Property p = (Property) it.next();
				
				if (p.getName().equals("file"))
				{
					CompilationFile cf = (CompilationFile) p.getValue();
					files.add(cf);
					
					File f = new File("CPU-Projects" + File.separator + clientAID.getLocalName() + File.separator + projectName + File.separator + cf.filename);
					pathToFolder = f.getPath().substring(0, f.getPath().lastIndexOf(File.separator));
							
					try
					{	
						Files.write(f.toPath(), cf.text.getBytes(), StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
					}
					catch (IOException e)
					{
						e.printStackTrace();
						return false;
					}

				}
			}

			return true;
		}
		
		public boolean createClientFolder()
		{
			return new File("CPU-Projects/" + clientAID.getLocalName()).mkdirs();
		}
		
		public boolean createFileFolder(String filename)
		{
			return new File("CPU-Projects/" + clientAID.getLocalName() + File.separator + filename).mkdirs();
		}	
		

		@Override
		public boolean done()
		{
			return true;
		}
		
	}
	
	class CompileProjectBehaviour extends Behaviour
	{
		String path;
	
		public CompileProjectBehaviour(String path)
		{
			this.path = path;
		}
		
		@Override
		public void action()
		{
			CompilationFile cf = null;

            for (int i = 0; i < files.size(); i++)
            {
            	cf = files.get(i);
            	
            	if (!cf.compile())
            	{
            		errorPrintln("Failed to compile " + cf.filename);
            		return;
            	}
    		}
	        
	        println("Successfully compiled!");
	        addBehaviour(new SendCompilationFilesBehaviour());
		}

		@Override
		public boolean done()
		{
			return true;
		}
	}
	
	class SendCompilationFilesBehaviour extends Behaviour
	{
		@Override
		public void action()
		{
			for	(int i = 0; i < files.size(); i++)
			{
				ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
				msg.addReceiver(clientAID);
				msg.setByteSequenceContent(files.get(i).binary);
				msg.addUserDefinedParameter("filename", files.get(i).filename);
				send(msg);
			}
			
		}

		@Override
		public boolean done()
		{
			return true;
		}
		
	}
}
