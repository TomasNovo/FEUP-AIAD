package logic.Client.Behaviours.Negotiation;

import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.Macros;
import logic.Client.Client;
import logic.Client.Behaviours.ReceiveCompiledFilesBehaviour;

public class SendResponseBehaviour extends Behaviour{

	Client agent;	
	String message;
	boolean sent = false;
	
	public SendResponseBehaviour(String m)
	{
		this.message = m;
	}
	
	@Override
	public void action()
	{
		agent = (Client) myAgent;
		
		
		if(sendResponse() != 0)
			agent.errorPrintln("Error sending response");
		
		if(agent.acceptedDeadline || agent.acceptedNegotiation)
			agent.addBehaviour(new ReceiveCompiledFilesBehaviour());
			
		
		else return;
	}
	
	public int sendResponse()
	{
		ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
		msg.setContent(message);
		agent.println("Client response: " + msg.getContent());
		msg.addReceiver(new AID("CPU", AID.ISLOCALNAME));
		agent.send(msg);
		
		return 0;
	}
	
	
	@Override
	public boolean done()
	{
		return true;
	}
}
