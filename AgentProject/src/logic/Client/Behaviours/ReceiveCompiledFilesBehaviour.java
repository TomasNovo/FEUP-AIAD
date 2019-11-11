package logic.Client.Behaviours;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.Macros;
import logic.Client.Client;
import logic.Client.Behaviours.RemoveProjectBehaviour;

public class ReceiveCompiledFilesBehaviour extends Behaviour
{
	Client agent;
	
	public ReceiveCompiledFilesBehaviour()
	{
		
	}
	
	@Override
	public void action()
	{
		agent = (Client) myAgent;

		for	(int i = 0; i < agent.files.size(); i++) // Iterates through every file to receive the binary
		{
			ACLMessage msg = this.myAgent.blockingReceive();
			String filename = msg.getUserDefinedParameter("filename");
			
			boolean found = false;
			
			for	(int j = 0; j < agent.files.size(); j++)
			{
				if (agent.files.get(j).getFilename().equals(filename)) // Sets the binary to the respective CompilationFile
				{
					CompilationFile cf = agent.files.get(i);
					cf.setBinary(msg.getByteSequenceContent());
					agent.files.set(j, cf);
					
					if (!saveBinary(cf))
					{
						agent.errorPrintln("Failed to save binary!");
						return;
					}
					
					found = true;
					break;
				}
			}
			
			if (!found)
			{
				agent.errorPrintln("Failed to find respective CompilationFile!");
				return;
			}
		}
		
		agent.println("Successfully received compilation files");
		agent.addBehaviour(new RemoveProjectBehaviour());
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
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}