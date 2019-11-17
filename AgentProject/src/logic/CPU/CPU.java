package logic.CPU;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

import logic.Bid;
import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Macros;
import logic.Pair;
import logic.ProjectInfo;
import logic.CPU.Behaviours.NegotiationResponder;
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
	
	public boolean clientFolder;
	
	// Negotiation Attributes
	public boolean bidIsAcceptable;
	
	public ArrayList<Pair<Double, Integer>> compilationTimes = new ArrayList<Pair<Double, Integer>>(); 
	
	public boolean acceptableDeadline = false;
	
	public static final int compilationTimesSize = 15;
	
	@Override
	protected void setup()
	{
		super.setup();
		
//		System.out.println("Hey! Its me, " + getAID().getName());
//		println(Float.toString(this.getAverageCPUCompilationTimes()));
		
		bidIsAcceptable = true;
				
		registerDF();
		
		new File("CPU-Projects").mkdirs();
		
		addBehaviour(new NegotiationResponder(this));
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

	
	// Get e Set Methods
	public int getID()
	{
		return this.id;
	}
	
	public String getProjectPath()
	{
		return this.projectPath;
	}

	public boolean getClientFolder()
	{
		return this.clientFolder;
	}
	

}
