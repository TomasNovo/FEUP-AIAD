package logic.Client.Behaviours;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.CompiledProject;
import logic.CompiledProjectErrorType;
import logic.Macros;
import logic.Client.Client;
import logic.Client.Behaviours.RemoveProjectBehaviour;

public class ReceiveCompiledFilesBehaviour extends Behaviour
{
	Client agent;
	ArrayList<String> projectFiles;
	String projectPath;
	
	public ReceiveCompiledFilesBehaviour()
	{
		projectFiles = new ArrayList<String>();
	}
	
	@Override
	public void action()
	{
		agent = (Client) myAgent;
		boolean successfulProject = true;
		
		for	(int i = 0; i < agent.cpus.size(); i++) // Iterates through every file to receive the binary
		{
			ACLMessage msg = this.myAgent.blockingReceive();
			CompiledProject cp = CompiledProject.deserialize(msg.getByteSequenceContent());

			if (cp.errorType == CompiledProjectErrorType.COMPILATIONERROR)
			{
				agent.errorPrintln("CPU " + msg.getSender() + " generated a compilation error!");
				successfulProject = false;
				continue;
			}
			
			if (cp.errorType == CompiledProjectErrorType.DEADLINEEXCEEDED)
			{
				agent.errorPrintln("CPU " + msg.getSender() + " exceeded the deadline!");
				successfulProject = false;
				continue;
			}
			
			// Iterate compiledFiles and save the binary on a successful CompiledProject
			for (int j = 0; j < cp.compiledFiles.size(); j++)
			{
				String filename = cp.compiledFiles.get(j).first;
				int fileIndex = searchFile(filename);
				if (fileIndex == -1)
				{
					agent.errorPrintln("Failed to find respective CompilationFile!");
					continue;
				}
				
				CompilationFile cf = agent.info.files.get(fileIndex);
				cf.setBinary(cp.compiledFiles.get(j).second);
				
				if (!saveBinary(cf))
				{
					agent.errorPrintln("Failed to save binary!");
					continue;
				}
				
				projectFiles.add(cf.path + "/" + cf.filenameNoExtention + Macros.binaryFileExtension);
			}
		}
		
		if (successfulProject)
		{
			agent.println("Successfully received compilation files");
			linkProject();			
		}
		else
			agent.errorPrintln("Failed to receive all compiled files successfully from CPUs, not linking.");
	}
	
	public boolean saveBinary(CompilationFile cf)
	{
		try
		{
			Files.write(Paths.get(cf.path + "/" + cf.filenameNoExtention + Macros.binaryFileExtension), cf.getBinary(), StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
		}
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}
		
		return true;
	}
	
	private int searchFile(String filename)
	{
		for	(int i = 0; i < agent.info.files.size(); i++)
		{
			if (agent.info.files.get(i).getFilename().equals(filename)) // Sets the binary to the respective CompilationFile
				return i;
		}
		
		return -1;
	}
	
	public boolean linkProject()
	{
		try
		{
			String execName = "main";
			String command = "g++ -o " + agent.projectPath + "/" + execName;
			
			for (int i = 0; i < projectFiles.size(); i++)
			{
				command += " " + projectFiles.get(i);
			}
			
			Process process;
			process = Runtime.getRuntime().exec(command);
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
			
			while (process.isAlive())
			{}
			
			String line;
			while ((line = reader.readLine()) != null)
			{
				System.err.println(line);
			}
			
			int returnValue = process.exitValue();

			if (returnValue != 0)
			{
				agent.errorPrintln("Failed to link!");
				return false;
			}
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		
		agent.println("Successfully built project " + agent.projectName);
		return true;
	}
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}