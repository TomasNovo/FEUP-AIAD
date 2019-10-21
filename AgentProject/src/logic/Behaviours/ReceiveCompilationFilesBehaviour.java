package logic.Behaviours;

import java.util.ArrayList;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.Client;
import logic.CompilationFile;

class ReceiveCompilationFilesBehaviour extends Behaviour
{
	ArrayList<CompilationFile> files;
	
	public ReceiveCompilationFilesBehaviour(ArrayList<CompilationFile> f)
	{
		files = f;
	}
	
	@Override
	public void action()
	{
		for	(int i = 0; i < files.size(); i++) // Iterates through every file to receive the binary
		{
			ACLMessage msg = this.myAgent.blockingReceive();
			String filename = msg.getUserDefinedParameter("filename");
			
			boolean found = false;
			
			for	(int j = 0; j < files.size(); j++)
			{
				if (files.get(j).getFilename().equals(filename)) // Sets the binary to the respective CompilationFile
				{
					CompilationFile cf = files.get(i);
					cf.setBinary(msg.getByteSequenceContent());
					files.set(j, cf);
					
					if (!cf.saveBinary())
					{
						((Client) this.myAgent).errorPrintln("Failed to save binary!");
						return;
					}
					
					found = true;
					break;
				}
			}
			
			if (!found)
			{
				((Client) this.myAgent).errorPrintln("Failed to find respective CompilationFile!");
				return;
			}
		}
		
		((Client) this.myAgent).println("Successfully received compilation files");
		
	}
	
	@Override
	public boolean done()
	{
		return true;
	}
	
}