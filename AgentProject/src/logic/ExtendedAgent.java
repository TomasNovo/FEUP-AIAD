package logic;

import jade.core.Agent;

public class ExtendedAgent extends Agent
{
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
