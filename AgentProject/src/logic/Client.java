package logic;

import java.io.File;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;

public class Client extends ExtendedAgent
{
	int id = 0;
	ArrayList<CompilationFile> files;
	String projectPath;
	Object[] args;
	
	
	@Override
	protected void setup()
	{
		super.setup();

		this.args = getArguments();
		
//		println(System.getProperty("user.dir"));

		//addBehaviour(new ReadProject((String)args[0]));
		
		addBehaviour(new OfferProjectBehaviour("project" + File.separator + "main.cpp"));
		
		println("Hey! Its me, " + getAID().getName());
	}
	
	class OfferProjectBehaviour extends Behaviour
	{
		boolean sentClient = false;
		String filepath;
		String filename;
		
		public OfferProjectBehaviour(String f)
		{
			this.filepath = f;
			this.filename = filepath.substring(filepath.lastIndexOf(File.separator) + 1);
		}
		
		@Override
		public void action()
		{
			sendClientAID();
			
			if (sendFileToCompile() == 0)
				sentClient = true;
			
			block();
		}

		public void sendClientAID()
		{
			ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
			msg.setContent(getAID().getName());
			msg.addReceiver(new AID("CPU", AID.ISLOCALNAME));
			send(msg);
		}
		
		public int sendFileToCompile()
		{
			File f = new File(filepath);
			byte[] fileContent = null;
			
			if(!f.exists())
			{
				println("ERROR: Client: Inexistent file, please enter a valid path !" );
				return -1;
			}
			
			try 
			{
				fileContent = Files.readAllBytes(f.toPath());
			} 
			catch (IOException e) 
			{
				println("ERROR: Client: Error sending file" );
				e.printStackTrace();
				return -1;
			}
			
			
			ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
			msg.addReceiver(new AID("CPU", AID.ISLOCALNAME));
			msg.setByteSequenceContent(fileContent);
			msg.addUserDefinedParameter("filename", filename);
			send(msg);
			
			return 0;
		}
		
		@Override
		public boolean done()
		{
			return sentClient;
		}
		
	}
	
}
