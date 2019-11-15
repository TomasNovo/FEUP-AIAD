package logic.Client.Behaviours.Negotiation;


import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.Macros;
import logic.Auction.Bid;
import logic.Client.Client;
import logic.Client.Behaviours.ReceiveCompiledFilesBehaviour;
import logic.Client.Behaviours.Negotiation.SendResponseBehaviour;

public class ReceiveNegotiationBehaviour extends Behaviour
{

	Client agent;	
	boolean received = false;
	AID cpuName;
	
	public ReceiveNegotiationBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (Client) myAgent;
		
		String negotiation = receiveNegotiation();
		
		if(negotiation.equals("-1"))
		{
			agent.println("ERROR: CPU: Error receiving negotiation");
		}
		else if(negotiation.equals(Macros.deadlineAcceptable)) // deadline aceite
		{
			agent.acceptedDeadline = true;
			agent.addBehaviour(new SendResponseBehaviour("Negotiation accepted", cpuName));	
		}
		else
		{
			agent.acceptedDeadline = false;
			
			boolean result = agent.checkCPUProposal();
			
			System.out.println(result);
			
			//negociação
			if(result)
			{
				agent.acceptedNegotiation = true;
				agent.addBehaviour(new SendResponseBehaviour("Negotiation accepted", cpuName));
			}
			else 
			{
				agent.acceptedNegotiation = false;
			
				// Remove cpu from list
				int cpuIndex = agent.searchCPU(cpuName);
				if (cpuIndex == -1)
					agent.errorPrintln("This CPU shouldn't be answering!");
				else
					agent.cpus.remove(cpuIndex);
			
				agent.addBehaviour(new SendResponseBehaviour("Negotiation rejected", cpuName));
			}
		}	
	}
	
	public String receiveNegotiation()
	{
		ACLMessage msg = agent.blockingReceive(); // Wait 10 secs for message
		
        if (msg != null )
        {
        	cpuName = msg.getSender();
        	
        	if (msg.getContent().equals(Macros.deadlineAcceptable))
        	{
        		return Macros.deadlineAcceptable;
        	}
        	else
        	{
        		agent.bcpu = new Bid(agent, msg.getContent() + 's');
        		agent.println("Client received: " + msg.getContent());
                return "0";
        	}
        }
        
        return "-1";
	}
	

	@Override
	public boolean done() 
	{ 
		return true;
	}
}
