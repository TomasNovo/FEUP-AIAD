package logic.Client;

import java.io.File;
import java.util.ArrayList;
import java.util.Random;

import jade.domain.FIPAAgentManagement.DFAgentDescription;
import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Macros;
import logic.Auction.Bid;
import logic.Client.Behaviours.OfferProjectBehaviour;
import logic.Client.Behaviours.Negation.ReceiveNegotiationBehaviour;


public class Client extends ExtendedAgent
{
	public int id = 0;
	public ArrayList<CompilationFile> files;
	public DFAgentDescription[] CPUs;
	public String projectName;
	public String projectPath;
	public String deadline;
	public int numberOfProjectFiles;
	
	//initial bid
	public Bid b;
	public float tolerance;
	
	//received bid 
	public Bid bcpu;
	
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
		println("Hey! Its me, " + getAID().getName());
		
		Object[] args = getArguments();
		
		if(args != null && args.length > 0 && args.length == 2) 
        {
			projectName = args[0].toString();
			projectPath = Macros.clientProjectPath + "/" + projectName;
			numberOfProjectFiles = getNumberOfProjectFiles();
			
            deadline = args[1].toString();
            
            this.setTolerance(true, 0);
    		
            b = new Bid(this, deadline);
        
    		addBehaviour(new OfferProjectBehaviour());
            
        }
	

        //addBehaviour(new ReceiveNegotiationBehaviour());
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
			this.tolerance = result / 100;
		}
		else
		{
			this.tolerance = t / 100;
		}
		
		this.println("Tolerance: " + this.tolerance);
	}
	
	public boolean checkCPUProposal()
	{		
	  if(bcpu.getDeadlineInSeconds() < b.getDeadlineInSeconds() + this.getToleranceOfDeadline())
	  {
		  this.println("New deadline accepted");
		  return true;
	  }
			
	  	this.println("New deadline rejected");
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
	public float getToleranceOfDeadline()
	{
		return this.tolerance * this.b.getDeadlineInSeconds();
	}
	
	public int getNumberOfProjectFiles()
	{
		return new File(this.projectPath).list().length;
	}
}
