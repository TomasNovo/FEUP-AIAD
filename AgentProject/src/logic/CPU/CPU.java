package logic.CPU;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Macros;
import logic.Pair;
import logic.ProjectInfo;
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
	public String projectPath;
	
	public AID clientAID;
	public boolean clientFolder;
	
	// Negotiation Attributes
	public Bid b;
	public boolean bidIsAcceptable;
	
	public ArrayList<Pair<Double, Integer>> compilationTimes = new ArrayList<Pair<Double, Integer>>(); 
	
	public boolean acceptableDeadline = false;
	
	public ProjectInfo info;
	
	@Override
	protected void setup()
	{
		super.setup();
		
		System.out.println("Hey! Its me, " + getAID().getName());
//		println(Float.toString(this.getAverageCPUCompilationTimes()));
		
		bidIsAcceptable = true;
				
		registerDF();
		
		new File("CPU-Projects").mkdirs();
		
		addBehaviour(new ReceiveProjectBehaviour(this));
	}
	
	// Returns average compilation times if exist
	public double getAverageCPUCompilationTimes()
	{
		double sumTimes = 0;
		double sumBytes = 0;
		
		for(int i = 0; i < compilationTimes.size(); i++)
		{
			sumTimes += compilationTimes.get(i).first;
			sumBytes += compilationTimes.get(i).second;
		}
		
		if (sumTimes == 0.0)
			return 0.0;
		
		return sumBytes/sumTimes;
	}

	
	public void initializeFiles()
	{
		this.info = null;
	}
	
	// Get e Set Methods
	public int getID()
	{
		return this.id;
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
	

}
