package logic;

import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;

public class Client extends Agent
{
	int id = 0;
	
	String[] files;
	
	@Override
	protected void setup()
	{
		super.setup();
		
		addBehaviour(new OfferProjectBehaviour());
		
		System.out.println("Ola!");
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
}
