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
import java.util.ArrayList;

import javax.swing.JOptionPane;

import jade.core.Agent;
import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;

public class CPU extends Agent
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
		
		System.out.println("Ola! " + getAID().getName() );
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
		
		public int saveFile(String cn)
		{
			String path = "CPU-Projects/";
			path += cn;
			
			File newFile = new File(path);
			
			try {
				if(newFile.createNewFile())
				{
					newFile.mkdir();
				    System.out.println("File created");
				} else {
				    System.out.println("File already exists.");
				}
			} catch (IOException e) {
				System.out.println("ERROR: CPU: Error creating file to save");
				e.printStackTrace();
				return -1;
			}
			
			try (FileOutputStream stream = new FileOutputStream(path)) {
			    stream.write(fileContent);
			} catch (FileNotFoundException e) {
				System.out.println("ERROR: CPU: Error writing to new file");
				e.printStackTrace();
				return -1;
			} catch (IOException e) {
				System.out.println("ERROR: CPU: Error writing to new file");
				e.printStackTrace();
				return -1;
			}
			return 0;
		}
		
		public int receiveFile()
		{
			ACLMessage msg = null;
			
			for (int i = 0; msg == null; i++)
			{
				//System.out.println(i);
				msg = receive();
			}
			if (msg != null) 
			{
			  String filename = msg.getUserDefinedParameter("filename");
			  f = new File(filename);// create file called fileName
			  fileContent = msg.getByteSequenceContent();

			  return 0;
			}
			else return -1;
			
		}
		
		public int receiveClientAID()
		{
			ACLMessage msg = null;
			
			for (int i = 0; msg == null; i++)
			{
				//System.out.println(i);
				msg = receive();
			}
		
			
			if (msg != null)
			{
				String info = msg.getContent();
				
				clientName = info.substring(0, info.indexOf('@'));
				System.out.println("Clientname: " + clientName);
				clientIP = info.substring(info.indexOf('@') + 1, info.indexOf('/'));
				
				clientFolder = new File("../AgentProject/CPU-Projects/" + clientName).mkdirs();
				
				System.out.println(msg.getContent());
				
//				JOptionPane.showMessageDialog(null, msg.getContent());	
				return 0;
			}
			
			return -1;
			
		}
		
		@Override
		public void action()
		{			
			if(receiveClientAID() != 0) {System.out.println("ERROR: CPU: Error receiving AID"); block();}
			if(receiveFile() != 0) {System.out.println("ERROR: CPU: Error receiving file"); return;}
			//if(saveFile(this.clientName) != 0) {System.out.println("ERROR: CPU: Error saving file"); return;}	
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
