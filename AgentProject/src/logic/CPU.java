package logic;

import java.io.File;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import logic.CompilationFile;

import javax.swing.JOptionPane;

import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;

public class CPU extends ExtendedAgent
{
	int id = 0;
	ArrayList<CompilationFile> files;
	String projectPath;
	
	boolean receivedProjects;
	AID clientAID;
	boolean clientFolder;
	
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
		files = new ArrayList<CompilationFile>();
		receivedProjects = new File("../AgentProject/CPU-Projects").mkdirs();
		
		addBehaviour(new ReceiveProjectBehaviour());
		
		println("Ola!");
	}

	
	class ReceiveProjectBehaviour extends Behaviour
	{
		String pathToFolder;
		
		public ReceiveProjectBehaviour()
		{
			
		}
		
		@Override
		public void action()
		{			
			if (receiveClientAID() != 0)
			{
				println("Error receiving client AID");
				return;
			}
			
			if (receiveFile() != 0) 
			{
				errorPrintln("ERROR: CPU: Error receiving file");
				return;
			}
		
			addBehaviour(new CompileProjectBehaviour(pathToFolder));
		}
		
		public int receiveClientAID()
		{
			ACLMessage msg = blockingReceive();	
			
			if (msg != null)
			{
				String info = msg.getContent();
				
				clientAID = msg.getSender();
				
				createClientFolder();
				println(msg.getContent());
				
				return 0;
			}
				
			errorPrintln("Failed to received message!");
			return -1;
		}
		
		public int receiveFile()
		{
			ACLMessage msg = blockingReceive();
			
			String filename = msg.getUserDefinedParameter("filename");
			String filenameNoExtention = filename.substring(0, filename.indexOf('.'));

			createFileFolder(filenameNoExtention);
			
			File f = new File("CPU-Projects" + File.separator + clientAID.getLocalName() + File.separator + filenameNoExtention + File.separator + filename);
			pathToFolder = f.getPath().substring(0, f.getPath().lastIndexOf(File.separator));
					
			try
			{
				byte[] fileContent = msg.getByteSequenceContent();
								
				Files.write(f.toPath(), fileContent, StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
				
				files.add(new CompilationFile(f));
			}
			catch (IOException e)
			{
				e.printStackTrace();
				return -1;
			}
			
			  
			return 0;
		}
		
		public boolean createClientFolder()
		{
			return new File("../AgentProject/CPU-Projects/" + clientAID.getLocalName()).mkdirs();
		}
		
		public boolean createFileFolder(String filename)
		{
			return new File("../AgentProject/CPU-Projects/" + clientAID.getLocalName() + File.separator + filename).mkdirs();
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
