package logic.Client;

import java.util.ArrayList;
import java.util.Random;

import jade.domain.FIPAAgentManagement.DFAgentDescription;
import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Macros;
import logic.Auction.Bid;
import logic.Client.Behaviours.OfferProjectBehaviour;


public class Client extends ExtendedAgent
{
	public int id = 0;
	public ArrayList<CompilationFile> files;
	public DFAgentDescription[] CPUs;
	public String projectName;
	public String projectPath;
	public String deadline;
	public Bid b;
	public float tolerance;
	
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
			
            deadline = args[1].toString();
            System.out.println("Deadline: "+ deadline);
            
            b = new Bid(this, deadline);
        
    		addBehaviour(new OfferProjectBehaviour());
        }
	
	}
	
	/*
	 * Tolerance will be a random percentage
	 */
	protected void setTolerance(boolean random, int t)
	{
		if(random)
		{
			Random r = new Random();
			int low = 1; //inclusive
			int high = 101; // exclusive
			int result = r.nextInt(high-low) + low;
			this.tolerance = result / 100;
		}
		else 
		{
			this.tolerance = t / 100;
		}
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
