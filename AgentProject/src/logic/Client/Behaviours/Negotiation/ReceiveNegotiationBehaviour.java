package logic.Client.Behaviours.Negotiation;


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
	
	public ReceiveNegotiationBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (Client) myAgent;
		
		String negotiation = receiveNegotiation();
		
		if(negotiation.equals("-1"))
		{agent.println("ERROR: CPU: Error receiving negotiation"); block();}
		
		else if(negotiation.equals(Macros.deadlineAcceptable)) // deadline aceite
		{
			agent.acceptedDeadline = true;
			agent.addBehaviour(new SendResponseBehaviour("Negotiation accepted"));	
			block();
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
				agent.addBehaviour(new SendResponseBehaviour("Negotiation accepted"));
			}
			else 
			{	agent.acceptedNegotiation = false;
				agent.addBehaviour(new SendResponseBehaviour("Negotiation rejected"));
			}
			block();
		}	
	}
	
	public String receiveNegotiation()
	{
		ACLMessage msg = null;
		
		for (int i = 0; msg == null; i++)
		{
			msg = agent.receive();
		}
		
        if (msg != null )
        {
        	if(msg.getContent().equals(Macros.deadlineAcceptable))
        	{
        		block();
        		return Macros.deadlineAcceptable;
        	}
        	else
        	{
        		agent.bcpu = new Bid(agent, msg.getContent() + 's');
        		agent.println("Client received: " + msg.getContent());
        	}
        			
            return "0";
        }
        else return "-1";
	}
	

	@Override
	public boolean done() 
	{ 
		return true;
	}
}
