package test;


import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.Auction.Bid;

public class ReceiveResponseBehaviour extends Behaviour
{

	TestCPU agent;	
	boolean received = false;
	
	public ReceiveResponseBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (TestCPU) myAgent;
		
		if(receiveResponse() == -1) 
		{agent.errorPrintln("ERROR: CPU: Error receiving negotiation"); block();}
		
	}
	
	public int receiveResponse()
	{
		ACLMessage msg = null;
		
		for (int i = 0; msg == null; i++)
		{
			msg = agent.receive();
		}
		
        if (msg != null)
        {
    		agent.println("CPU received response: " + msg.getContent());

            if(msg.getContent().equals("Negotiation accepted"))
    		{
            	return 0;
    		}
            else if(msg.getContent().equals("Negotiation rejected"))
    		{
            	return 1;
    		}
        }
        
        return -1;
	}
	

	@Override
	public boolean done() 
	{ 
		return true;
	}
}
