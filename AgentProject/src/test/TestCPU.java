package test;

import java.util.ArrayList;
import java.util.Random;

import jade.core.AID;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Macros;
import logic.Auction.Bid;
import test.SendCPUNegotiationBehaviour;


public class TestCPU extends ExtendedAgent
{
	public Bid b;
	public boolean bidIsAcceptable;
	
	@Override
	protected void setup()
	{
		super.setup();
		
		addBehaviour(new SendCPUNegotiationBehaviour());
		
		System.out.println("Hey! Its me, " + getAID().getName());
	}
	
}
