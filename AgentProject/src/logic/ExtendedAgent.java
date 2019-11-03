package logic;

import jade.core.Agent;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import logic.CPU.CPU;
import logic.Client.Client;

public class ExtendedAgent extends Agent
{
	public ExtendedAgent()
	{
		
	}
	
	
	public void registerDF()
	{
		DFAgentDescription dfd = new DFAgentDescription();
		dfd.setName(getAID());
		ServiceDescription sd = new ServiceDescription();
		
		if (this instanceof CPU)
			sd.setType("CPU");
		else if (this instanceof Client)
			sd.setType("Client");
		else
		{
			errorPrintln("Failed to get class of object ExtendedAgent");
			return;
		}
				
		String name = getLocalName();
		sd.setName(name);
		
		dfd.addServices(sd);
		
		try
		{
			DFService.register(this, dfd);
		}
		catch (FIPAException e)
		{
			e.printStackTrace();
			return;
		}
		
	}
	
	public void println(String message)
	{
		System.out.println(buildMessage("INFO", message));
	}
	
	public void errorPrintln(String message)
	{
		System.out.println(buildMessage("ERROR", message));
	}
	
	private String buildMessage(String printType, String message)
	{
		return printType + "\t| " + getAID().getLocalName() + "\t| " + message;
	}
}
