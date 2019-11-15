package logic.CPU.Behaviours.Negotiation;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.Auction.Bid;
import logic.CPU.CPU;
import logic.CPU.Behaviours.CompileProjectBehaviour;
import logic.CPU.Behaviours.ReceiveProjectBehaviour;
import logic.Client.Behaviours.ReceiveCompiledFilesBehaviour;

public class ReceiveResponseBehaviour extends Behaviour
{

	CPU agent;	
	boolean received = false;
	String pathToFolder;
	
	
	public ReceiveResponseBehaviour(String p)
	{
		pathToFolder = p;
	}
	
	@Override
	public void action()
	{
		agent = (CPU) myAgent;
		
		int response = receiveResponse();
		
		if (response == -1)
		{
			agent.errorPrintln("ERROR: CPU: Error receiving negotiation");
			agent.addBehaviour(new ReceiveProjectBehaviour(agent));
		}
		else if (response == 0)
			agent.addBehaviour(new CompileProjectBehaviour(pathToFolder));
		else
		{
			agent.println("Negotiation is rejected! #TODO");
			agent.addBehaviour(new ReceiveProjectBehaviour(agent));
		}
		
	}
	
	public int receiveResponse()
	{
		ACLMessage msg = agent.blockingReceive(); // Wait 10 secs for message
		
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
