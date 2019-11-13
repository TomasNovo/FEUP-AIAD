package logic.CPU.Behaviours.Negotiation;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.Auction.Bid;
import logic.CPU.CPU;

public class ReceiveResponseBehaviour extends Behaviour
{

	CPU agent;	
	boolean received = false;
	
	public ReceiveResponseBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (CPU) myAgent;
		
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
