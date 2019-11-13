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
		{System.out.println("ERROR: CPU: Error receiving negotiation"); block();}
		
		agent.checkCPUProposal();
			
	}
	
	public int receiveNegotiation()
	{
		ACLMessage msg = null;
		
		for (int i = 0; msg == null; i++)
		{
			//System.out.println(i);
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
