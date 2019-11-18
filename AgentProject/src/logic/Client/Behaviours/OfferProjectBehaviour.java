package logic.Client.Behaviours;

import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import logic.Bid;
import logic.CompilationFile;
import logic.Macros;
import logic.ProjectInfo;
import logic.Client.Client;

public class OfferProjectBehaviour extends Behaviour
{
	Client agent;	
	boolean sentClient = false;
	ArrayList<ProjectInfo> infos;
	
	public OfferProjectBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (Client) myAgent;
		
		publishProject();
	}
	
	public boolean publishProject()
	{		
		agent.info = new ProjectInfo();
		agent.info.name = agent.projectName;
		agent.info.deadline = agent.deadline;
		
        try (DirectoryStream<Path> dirStream = Files.newDirectoryStream(Paths.get(agent.projectPath)))
        {
        	// Add files to agent and to info
    		int fileIndex = 0;
            for (Path child : dirStream)
            {
            	String filename = child.toFile().getName();
            	if (filename.endsWith(Macros.codeFileExtension) || filename.endsWith(Macros.headerFileExtension))
            	{
            		CompilationFile cf = new CompilationFile(child.toFile());
            		
            		if (filename.endsWith(Macros.codeFileExtension))
                		agent.info.toBeCompiled.add(new Integer(fileIndex));
            		
            		agent.info.files.add(cf);
            		fileIndex++;
            	}
    		}
            
            agent.info.timestamp = new Long(System.currentTimeMillis());
            agent.cpus = new ArrayList<DFAgentDescription>(Arrays.asList(agent.searchDF("CPU")));
            infos = new ArrayList<ProjectInfo>();
            
            // Initialize ProjectInfos, one for each CPU
            for (int i = 0; i < agent.cpus.size(); i++)
            {
            	infos.add(agent.info.Clone());
            	infos.get(i).toBeCompiled = new ArrayList<Integer>();
            }
            
            // Assign code CompilationFiles to CPUs. Only the CompilationFiles in agent.files are to be compiled (.cpp)
            distributeFilesRandomly();
            
    		for (int i = 0; i < infos.size(); i++)
    		{
    			DFAgentDescription dfad = agent.cpus.get(i);
    			AID cpuName = dfad.getName();

    			if (infos.get(i).toBeCompiled.size() == 0)
    			{
    				agent.cpus.remove(i);
    				infos.remove(i);
    				i--;
    				continue;
    			}
    			
    			infos.get(i).deadline = calculateDeadline(infos.get(i));
    			agent.addBehaviour(new NegotiationInitiator(agent, infos.get(i), cpuName));
      		}
    		
        }
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}			
		
		return true;
	}
	
	private Bid calculateDeadline(ProjectInfo info)
	{
		int projectNumBytes = agent.info.calculateCompileNumBytes();
		int proposalNumBytes = info.calculateCompileNumBytes();
		int estimatedCompilationTime = (int)((double)agent.deadline.getDeadlineInMilliSeconds() / (double)projectNumBytes * (double)proposalNumBytes);
		
		return new Bid(estimatedCompilationTime + "ms");
	}
	

	// Distributes The files randomly
	private void distributeFilesRandomly()
	{
        for (int i = 0; i < agent.info.toBeCompiled.size(); i++)
        {
        	int fileIndex = agent.info.toBeCompiled.get(i);
        	int randomCPU = (int)(Math.random() * infos.size());
        	infos.get(randomCPU).toBeCompiled.add(fileIndex);
        }
	}
	
    // Distributes The files randomly in a way such that no two CPUs differ in the number of files to be compiled by more than 1 (balanced)	
	private void distributeFilesRandomlyBalanced()
	{
        ArrayList<Integer> unbalanced = new ArrayList<Integer>();
        initializeUnbalancedArray(unbalanced);
      
        for (int i = 0; i < agent.info.toBeCompiled.size(); i++)
        {
        	int fileIndex = agent.info.toBeCompiled.get(i);
        	int unbalancedCPUIndex = (int)(Math.random() * unbalanced.size());
        	int randomCPU = unbalanced.get(unbalancedCPUIndex);
        	
        	infos.get(randomCPU).toBeCompiled.add(fileIndex);
        	
        	unbalanced.remove(unbalancedCPUIndex);
        	if (unbalanced.size() == 0)
                initializeUnbalancedArray(unbalanced);
        }
	}
	
	// Distributes the files in a way such that the total size of the files to be compiled to each CPU is as close as possible
	private void initializeUnbalancedArray(ArrayList<Integer> unbalanced)
	{
        for (int i = 0; i < infos.size(); i++)
        {
        	unbalanced.add(i);
        }
	}
	
	private void distributeFilesEvenlyBySize()
	{
		// Initialize sum array
		ArrayList<Integer> sum = new ArrayList<Integer>();
		for (int i = 0; i < infos.size(); i++)
		{
			sum.add(0);
		}
		
		ArrayList<Integer> fileIndexes = sortFiles();

        for (int i = 0; i < fileIndexes.size(); i++)
        {
        	int fileIndex = fileIndexes.get(i);
        	int lowestIndex = findLowestSum(sum);
        	int newSum = sum.get(lowestIndex) + agent.info.files.get(fileIndex).text.length();
        	
        	sum.set(lowestIndex, newSum); // Update sum
        	infos.get(lowestIndex).toBeCompiled.add(fileIndex);
        }
	}
	
	private int findLowestSum(ArrayList<Integer> sum)
	{
		int minIndex = 0;
		for (int i = 0; i < sum.size(); i++)
		{
			if (sum.get(i) < sum.get(minIndex))
				minIndex = i;
		}
		
		return minIndex;
	}
	
	private ArrayList<Integer> sortFiles()
	{
		ArrayList<Integer> fileIndexes = (ArrayList<Integer>) agent.info.toBeCompiled.clone();
		
		int minIndex = 0;
		for (int i = 0; i < fileIndexes.size(); i++)
		{
			minIndex = i;
			for (int j = i+1; j < fileIndexes.size(); j++)
			{
				if (agent.info.files.get(fileIndexes.get(j)).text.length() > agent.info.files.get(fileIndexes.get(minIndex)).text.length())
					minIndex = j;
			}
			
			Collections.swap(fileIndexes, minIndex, i);
		}
		
		return fileIndexes;
	}
	
	@Override
	public boolean done()
	{
		return true;
	}
}
