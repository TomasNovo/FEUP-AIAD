package logic.CPU;

import java.io.File;
import java.util.ArrayList;

import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Auction.Bid;
import logic.CPU.Behaviours.ReceiveProjectBehaviour;
import logic.CPU.Behaviours.Negotiation.SendNegotiationBehaviour;
import jade.core.AID;

/**
 * 
 * TODO: 
 * - Get deadline by DF
 * - Create function to calculate new deadline
 */

public class CPU extends ExtendedAgent
{
	int id = 0;
	public ArrayList<CompilationFile> files;
	public String projectPath;
	
	public AID clientAID;
	public boolean clientFolder;
	
	// Negotiation Attributes
	public Bid b;
	public boolean bidIsAcceptable;
	
	@Override
	protected void setup()
	{
		super.setup();
		
		System.out.println("Hey! Its me, " + getAID().getName());
		
		bidIsAcceptable = false;
		
		// TODO receive Client's bid by DF
		b = new Bid(this, "10m");
		
		registerDF();
		
		new File("CPU-Projects").mkdirs();
		
		addBehaviour(new ReceiveProjectBehaviour(this));
		//addBehaviour(new SendNegotiationBehaviour());
	}
	
	public void initializeFiles()
	{
		this.files = new ArrayList<CompilationFile>();
	}
	
	// Get e Set Methods
	public int getID()
	{
		return this.id;
	}
	
	public ArrayList<CompilationFile> getFiles()
	{
		return this.files;
	}
	
	public String getProjectPath()
	{
		return this.projectPath;
	}
	
	public void setClientAID(AID aid)
	{
		this.clientAID = aid;
	}
	
	public AID getClientAID()
	{
		return this.clientAID;
	}
	
	public boolean getClientFolder()
	{
		return this.clientFolder;
	}
	
	public void removeFile(int index)
	{
		files.remove(index);
	}

}
