package logic.Client.Behaviours;


import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.Auction.Bid;
import logic.Client.Client;

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
		{System.out.println("ERROR: CPU: Error receiving negotiation"); block();}
		
		agent.checkCPUProposal();
			
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
        	agent.b = new Bid(agent, msg.getContent() + 's');
    		System.out.println("Client received: " + msg.getContent());

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
