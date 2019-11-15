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
	
	public SendNegotiationBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (CPU) myAgent;
		
		if (agent.bidIsAcceptable)
		{
			if(sendClientProposal() != 0)
				return;
		}
		
		agent.addBehaviour(new ReceiveResponseBehaviour(agent.projectPath));

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
	
	public String calculateNewProposedDeadline()
	{
		double average = agent.getAverageCPUCompilationTimes();
		
		int deadline = agent.info.deadline.getDeadlineInMilliSeconds();
		int numBytes = agent.info.calculateCompileNumBytes();
		double predictedCompilationTime = numBytes/average;
		int newDeadLine;
		
		if (average == 0.0 || predictedCompilationTime <= deadline)
		{
			// ACCEPT
			agent.acceptableDeadline = true;
			return Macros.deadlineAcceptable;
		}
		else
		{
			// Calculate new deadline (Caculates the new deadline by selecting a uniform random time between -15% to +15% of the predictedCompilationTime 
			
			double variance = 0.15;
			newDeadLine = (int)((Math.random()-0.5) * variance * 2 * predictedCompilationTime + predictedCompilationTime) * 1000; 
		}
		
		
		return new Integer(newDeadLine).toString();
	}
	

	
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}
