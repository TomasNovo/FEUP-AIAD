package test;


import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.Auction.Bid;

public class ReceiveNegotiationClientBehaviour extends Behaviour
{

	TestClient agent;	
	boolean received = false;
	
	public ReceiveNegotiationClientBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (TestClient) myAgent;
		
		if(receiveNegotiation() != 0) 
		{agent.println("ERROR: CPU: Error receiving negotiation"); block();}
		
		if(agent.checkCPUProposal())
			agent.addBehaviour(new SendClientResponseBehaviour("Negotiation accepted"));
		else 
			agent.addBehaviour(new SendClientResponseBehaviour("Negotiation rejected"));
			
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
