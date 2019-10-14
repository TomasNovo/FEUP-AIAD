package logic;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;

import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.lang.acl.ACLMessage;

public class Client extends ExtendedAgent
{
	int id = 0;
	ArrayList<CompilationFile> files;
	DFAgentDescription[] CPUs;
	String projectPath;
	Object[] args;
	
	
	
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
		this.args = getArguments();
		
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
			if (!findCPUs())
				errorPrintln("Failed to find CPUs!");
			
			sendClientAID();
			
			if (sendFileToCompile() == 0)
				sentClient = true;
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
			msg.addReceiver(CPUs[0].getName());
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
