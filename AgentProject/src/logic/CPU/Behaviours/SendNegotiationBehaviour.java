package logic.CPU.Behaviours;

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
import logic.CPU.CPU;
import logic.Client.Client;

public class SendNegotiationBehaviour extends Behaviour
{
	CPU agent;	
	boolean sentClient = false;
	
	public SendNegotiationBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (CPU) myAgent;
		
		if(!agent.bidIsAcceptable)
		{
			if(sendClientProposal() != 0)
				return;
		}

	}
	
	public String calculateNewProposedDeadline()
	{
		// chamar função que define incremento do proposed deadline
		
		int d = agent.b.getDeadlineInSeconds();

		d += 120;
		
		// incrementar D com valor da funçao
		
		return Integer.toString(d);
	}
	
	public int sendClientProposal()
	{
		ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
		msg.setContent(calculateNewProposedDeadline());
		System.out.println("CPU sending: " + msg.getContent());
		msg.addReceiver(new AID("TestClient", AID.ISLOCALNAME));
		agent.send(msg);
		
		return 0;
	}
	
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}
