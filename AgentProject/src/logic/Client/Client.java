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
	public int numberOfProjectFiles;
	public int numberOfUtilProjectFiles;
	
	public boolean acceptedDeadline = false; 
	public boolean acceptedNegotiation = false;
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
		
		println("Hey! Its me, " + getAID().getName());
		
		Object[] args = getArguments();
		
		if(args != null && args.length > 0 && args.length == 2) 
        {
			projectName = args[0].toString();
			projectPath = Macros.clientProjectPath + File.separator + projectName;
			numberOfProjectFiles = getNumberOfProjectFiles();
			numberOfUtilProjectFiles = getNumberOfUtilProjectFiles();
			
            deadline = new Bid(this, args[1].toString());
            
            this.setTolerance(false, 5);
    		        
    		addBehaviour(new OfferProjectBehaviour());
            
        }
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
	
	public boolean checkCPUProposal(Bid bcpu, Bid deadline)
	{		
	  if (bcpu.getDeadlineInMilliSeconds() < deadline.getDeadlineInMilliSeconds() + this.getToleranceOfDeadline())
	  {
		  return true;
	  }
			
		return false;
	}
	
	public void initializeClient()
	{
		projectFiles = new ArrayList<String>();
		totalCompilationTime = 0.0;
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
	
	public int getNumberOfProjectFiles()
	{
		return new File(this.projectPath).list().length;
	}
	
	public int getNumberOfUtilProjectFiles()
	{
		int counter = 0;
		String[] f = new File(this.projectPath).list();
		String extension = "cpp";

		for(int i = 0; i < f.length; i++)
		{
			int j = f[i].lastIndexOf('.');
			if (j > 0) 
			{
			    extension = f[i].substring(j+1);
			}
			
			if(extension.equals("cpp") || extension.equals("h"))
			{
				counter++;
			}
		}
		
		return counter;
		
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
