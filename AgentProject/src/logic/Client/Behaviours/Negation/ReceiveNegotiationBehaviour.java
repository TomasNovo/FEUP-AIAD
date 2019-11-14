package logic.Client.Behaviours.Negation;


import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.Auction.Bid;
import logic.Client.Client;
import logic.Client.Behaviours.Negation.SendResponseBehaviour;

public class ReceiveNegotiationBehaviour extends Behaviour
{

	Client agent;	
	boolean received = false;
	
	public ReceiveNegotiationBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (Client) myAgent;
		
		if(receiveNegotiation() != 0) 
		{agent.println("ERROR: CPU: Error receiving negotiation"); block();}
		
		if(agent.checkCPUProposal())
			agent.addBehaviour(new SendResponseBehaviour("Negotiation accepted"));
		else 
			agent.addBehaviour(new SendResponseBehaviour("Negotiation rejected"));
			
	}
	
	public int receiveNegotiation()
	{
		ACLMessage msg = null;
		
		for (int i = 0; msg == null; i++)
		{
			msg = agent.receive();
		}
		
        if (msg != null)
        {
        	agent.bcpu = new Bid(agent, msg.getContent() + 's');
    		agent.println("Client received: " + msg.getContent());

            return 0;
        }
        else return -1;
	}
	

	@Override
	public boolean done() 
	{ 
		return true;
	}
}
