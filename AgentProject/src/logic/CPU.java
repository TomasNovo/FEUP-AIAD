package logic;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import logic.CompilationFile;

import javax.swing.JOptionPane;

import jade.core.Agent;
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
		
		receivedProjects = new File("../AgentProject/CPU-Projects").mkdirs();
		
		addBehaviour(new CompilingBehaviour(null));
		
		println("Ola!");
	}
	
	public ACLMessage getMessage()
	{
		ACLMessage msg = null;
		for (int i = 0; msg == null; i++)
		{
			//println(i);
			msg = receive();
		}
		
		return msg;
	}
	
	class CompilingBehaviour extends Behaviour
	{
		int iterationCounter = 0;
		File f;
		byte[] fileContent = null;
		String clientName;
		
		String[] files;
		
		public CompilingBehaviour(String[] files)
		{
			if (files == null)
				this.files = new String[0];
			else
				this.files = files;
			
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
				if (f.exists())
					f.delete();

				f.createNewFile();

				fileContent = msg.getByteSequenceContent();
				
				Files.write(f.toPath(), fileContent, StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
			}
			catch (IOException e)
			{
				// TODO Auto-generated catch block
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
			
			String pathToFolder = f.getPath().substring(0,f.getPath().lastIndexOf(File.separator));
			addBehaviour(new ReadProject(pathToFolder));
					
			block();
		}

		@Override
		public boolean done()
		{
			return true;
		}
		
	}
	
	class ReadProject extends Behaviour
	{
		String path;
	
		public ReadProject(String path)
		{
			this.path = path;
		}
		
		@Override
		public void action()
		{
			files = new ArrayList<CompilationFile>();

	        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(path)))
	        {

	            for (Path child : dirStream)
	            {
	            	files.add(new CompilationFile(child.toFile()));
	            	
	    		}
	            
	        }
	        catch (IOException e) 
	        {
	            e.printStackTrace();
	        }
	        
    		println(files.get(0).path);

    		println(files.get(0).filename);
    		
	        
	        for (int i = 0; i < files.size(); i++)
	        {
	        	files.get(i).compile();

	        }
	        
	        block();

		}

		@Override
		public boolean done()
		{
			return true;
		}		
	}
}
