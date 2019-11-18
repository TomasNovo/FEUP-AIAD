package logic.Client;

import java.io.File;
import java.util.ArrayList;
import java.util.Random;

import jade.core.AID;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import logic.Bid;
import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Macros;
import logic.ProjectInfo;
import logic.Client.Behaviours.OfferProjectBehaviour;


public class Client extends ExtendedAgent
{
	public int id = 0;
	public ProjectInfo info;
	public ArrayList<DFAgentDescription> cpus;
	public String projectName;
	public String projectPath;
	
	public boolean successfulProject;
	
	//initial bid
	public Bid deadline;
	public float tolerance;
	
	public ArrayList<String> projectFiles;
	public double totalCompilationTime;
		
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
//		println("Hey! Its me, " + getAID().getName());
		
		Object[] args = getArguments();
		
		if(args != null && args.length > 0 && args.length == 2) 
        {
			projectName = args[0].toString();
			projectPath = Macros.clientProjectPath + File.separator + projectName;
			
            deadline = new Bid(this, args[1].toString());
            
            this.setTolerance(true);
    		        
    		addBehaviour(new OfferProjectBehaviour());
            
        }
	}
	
	/*
	 * Tolerance will be a random percentage
	 * 
	 * int t is for testing purposes if random == false
	 */
	protected void setTolerance(boolean random)
	{
		Random r = new Random();
		int low = 1; //inclusive
		int high = 101; // exclusive
		float result = r.nextInt(high-low) + low;
		this.tolerance = result / 100;
	
		this.println("Tolerance: " + this.tolerance);
	}
	
	public boolean checkCPUProposal(Bid bcpu, Bid deadline)
	{		
	  return (bcpu.getDeadlineInMilliSeconds() < deadline.getDeadlineInMilliSeconds() + this.getToleranceOfDeadline());
	}
	
	public void initializeClient()
	{
		projectFiles = new ArrayList<String>();
		totalCompilationTime = 0.0;
		successfulProject = true;
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
		return this.tolerance * this.deadline.getDeadlineInMilliSeconds();
	}
	
	public int searchCPU(AID cpuName)
	{
		for (int i = 0; i < cpus.size(); i++)
		{
			if (cpus.get(i).getName().equals(cpuName))
				return i;
		}
		
		return -1;
	}
	
}
