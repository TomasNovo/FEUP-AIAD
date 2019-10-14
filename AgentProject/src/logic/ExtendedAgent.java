package logic;

import jade.core.Agent;
import jade.lang.acl.ACLMessage;

public class ExtendedAgent extends Agent
{
	
	public ACLMessage getMessage()
	{
		ACLMessage msg = null;
		for (int i = 0; msg == null; i++)
		{
			//println(i);
			msg = receive();
		}
		
		return msg;
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
