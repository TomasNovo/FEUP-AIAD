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


public class TestClient extends ExtendedAgent
{
	
	// Initial bid
	public Bid bi = new Bid(this, "10m");
	
	// Received bid
	public Bid b;
	
	public float tolerance;
	
	@Override
	protected void setup()
	{
		super.setup();
			
		this.setTolerance(true, 0);
		
		System.out.println("Hey! Its me, " + getAID().getName());
		
		addBehaviour(new ReceiveNegotiationClientBehaviour());
	}
	
	/*
	 * Tolerance will be a random percentage
	 * 
	 * int t is for testing purposes if random == false
	 */
	protected void setTolerance(boolean random, int t)
	{
		if(random)
		{
			Random r = new Random();
			int low = 1; //inclusive
			int high = 101; // exclusive
			float result = r.nextInt(high-low) + low;
			this.tolerance = (float) 0.01;
		}
		else
		{
			this.tolerance = t / 100;
			
		}
	}
	
	protected boolean checkCPUProposal()
	{		
	  if(b.getDeadlineInSeconds() < bi.getDeadlineInSeconds() + this.getToleranceOfDeadline())
	  {
		  System.out.println("New deadline accepted");
		  return true;
	  }
			
	  	System.out.println("New deadline rejected");
		return false;
	}
	
	/*
	 * This value is used in negotiations in the following way:
	 * 
	 * Client has a random % value of tolerance. While negotiating,
	 * if the CPU knows that it can't compile on the deadline that the Client
	 * specified, the CPU will propose a new deadline. According to Client's 
	 * tolerance he will do the following:
	 * 
	 * if deadline proposed of CPU <= initial deadline + Client Tolerance * initial deadline
	 * 		accept negotiation
	 * 
	 * else 
	 * 		reject negotiation
	 * 
	 */
	protected float getToleranceOfDeadline()
	{
		return this.tolerance * this.b.getDeadlineInSeconds();
	}
	
}