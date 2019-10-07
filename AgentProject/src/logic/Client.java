package logic;

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

public class Client extends Agent
{
	int id = 0;
	ArrayList<CompilationFile> files;
	String projectPath;
	
	@Override
	protected void setup()
	{
		super.setup();

		Object[] args = getArguments();
		
//		System.out.println(System.getProperty("user.dir"));

		addBehaviour(new ReadProject((String)args[0]));
		
		System.out.println("Hey! Its me, " + getAID().getName());
	}
	
	class OfferProjectBehaviour extends Behaviour
	{
		boolean sent = false;
		
		@Override
		public void action()
		{
//			System.out.println(++iterationCounter);
			
			ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
			msg.setContent("Send");
			msg.addReceiver(new AID("CPU", AID.ISLOCALNAME));
			send(msg);
			sent = true;

		}

		@Override
		public boolean done()
		{
			return sent;
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
