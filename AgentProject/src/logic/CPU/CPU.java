package logic.CPU;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Macros;
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
		
		b = new Bid(this, "10m");
		
		registerDF();
		
		new File("CPU-Projects").mkdirs();
		
		addBehaviour(new ReceiveProjectBehaviour(this));
		//addBehaviour(new SendNegotiationBehaviour());
	}
	
	// Returns average compilation times if exist
	public float getAverageCPUCompilationTimes()
	{
		float numberOfTimes = 0;
		float sum = 0;
		
		File file = new File(Macros.cpuProjectPath + "/times.txt");
		boolean empty = !file.exists() || file.length() == 0;
		
		if(empty)
			return 0;
		
		try {
			Scanner scanner = new Scanner(new File(Macros.cpuProjectPath + "/times.txt"));
			while (scanner.hasNextLine()) 
			{
				System.out.println("SCANNER LINE: " + scanner.nextLine());
				sum += Float.parseFloat(scanner.nextLine());
				numberOfTimes++;
			}
			
			scanner.close();
		} catch (FileNotFoundException e) 
		{
			e.printStackTrace();
		}
		
		return sum/numberOfTimes;
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
