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

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;

public class CPU extends ExtendedAgent
{
	int id = 0;
	ArrayList<CompilationFile> files;
	String projectPath;
	
	boolean receivedProjects;
	String client;
	String clientName;
	String clientIP;
	boolean clientFolder;
	
	@Override
	protected void setup()
	{
		super.setup();
		
		files = new ArrayList<CompilationFile>();
		receivedProjects = new File("../AgentProject/CPU-Projects").mkdirs();
		
		addBehaviour(new ReceiveProjectBehaviour());
		
		println("Ola!");
	}
	

	
	class ReceiveProjectBehaviour extends Behaviour
	{
		int iterationCounter = 0;
		File f;
		byte[] fileContent = null;
		String clientName;
		
		public ReceiveProjectBehaviour()
		{
			
		}
		
		
		public boolean createClientFolder()
		{
			return new File("../AgentProject/CPU-Projects/" + clientName).mkdirs();
		}
		
		public boolean createFileFolder(String filename)
		{
			return new File("../AgentProject/CPU-Projects/" + clientName + File.separator + filename).mkdirs();
		}
		
		public int receiveFile()
		{
			ACLMessage msg = getMessage();
			
			String filename = msg.getUserDefinedParameter("filename");
			String filenameNoExtention = filename.substring(0, filename.indexOf('.'));

			createFileFolder(filenameNoExtention);
			
			f = new File("CPU-Projects" + File.separator + clientName + File.separator + filenameNoExtention + File.separator + filename);
		 
			try
			{
				fileContent = msg.getByteSequenceContent();
								
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
		
		public int receiveClientAID()
		{
			ACLMessage msg = getMessage();	
			
			if (msg != null)
			{
				String info = msg.getContent();
				
				clientName = info.substring(0, info.indexOf('@'));
				println("Clientname: " + clientName);
				clientIP = info.substring(info.indexOf('@') + 1, info.indexOf('/'));
				
				createClientFolder();
				
				println(msg.getContent());
				
//				JOptionPane.showMessageDialog(null, msg.getContent());	
				return 0;
			}
			else
				errorPrintln("Failed to received message!");
			
			return -1;
			
		}
		
		@Override
		public void action()
		{			
			if(receiveClientAID() != 0) {println("Error receiving client AID"); block();}
			if(receiveFile() != 0) {errorPrintln("ERROR: CPU: Error receiving file"); return;}
			
			String pathToFolder = f.getPath().substring(0, f.getPath().lastIndexOf(File.separator));
			addBehaviour(new CompileProjectBehaviour(pathToFolder));
					
			block();
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
	        block();
		}

		@Override
		public boolean done()
		{
			return true;
		}		
	}
}
