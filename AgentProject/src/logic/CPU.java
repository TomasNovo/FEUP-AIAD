package logic;

import java.io.File;

import javax.swing.JOptionPane;

import jade.core.Agent;
import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;

public class CPU extends Agent
{
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
		String[] files;
		double[] times;
		
		public CompilingBehaviour(String[] files)
		{
			if (files == null)
				this.files = new String[0];
			else
				this.files = files;
			
			times = new double[this.files.length];
		}
		
		@Override
		public void action()
		{
			//System.out.println(++iterationCounter);
			
			//ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
//			msg.setContent("Send");
//			msg.addReceiver(new AID("", AID.ISLOCALNAME));

			
			/*for(int i = 0; i < files.length; i++)
			{
				
			}*/
			
			ACLMessage msg = receive();
			
			if(msg != null)
			{
				String info = msg.getContent();
				
				clientName = info.substring(0, info.indexOf('@'));
				clientIP = info.substring(info.indexOf('@') + 1, info.indexOf('/'));
				
				clientFolder = new File("../AgentProject/CPU-Projects/" + clientName).mkdirs();
				
				JOptionPane.showMessageDialog(null, msg.getContent());
				
			}
			else block();
		}

		@Override
		public boolean done()
		{
			return (iterationCounter == 15);
		}
		
	}
}
