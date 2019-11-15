package logic.CPU.Behaviours.Negotiation;

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
import logic.CPU.Behaviours.CompileProjectBehaviour;
import logic.CPU.Behaviours.Negotiation.ReceiveResponseBehaviour;

public class SendNegotiationBehaviour extends Behaviour
{
	CPU agent;	
	boolean sentClient = false;
	String pathToFolder;
	
	public SendNegotiationBehaviour(String p)
	{
		this.pathToFolder = p;
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
		
		agent.addBehaviour(new ReceiveResponseBehaviour(pathToFolder));

	}
	
	public String calculateNewProposedDeadline()
	{
		float average = agent.getAverageCPUCompilationTimes();
		
		int d = agent.b.getDeadlineInSeconds();

		
		// TODO calculate new deadline
		/*if(average <= d/2)
		{
			agent.acceptableDeadline = true;
			return Macros.deadlineAcceptable;
		}*/
		
		// incrementar D com valor da funçao
		d += 120;
		
		return Integer.toString(d);
	}
	
	public int sendClientProposal()
	{
		ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
		msg.setContent(calculateNewProposedDeadline());
		agent.println("CPU sending: " + msg.getContent());
		msg.addReceiver(new AID("Client", AID.ISLOCALNAME));
		agent.send(msg);
		
		return 0;
	}
	
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}
