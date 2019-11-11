package logic.CPU.Behaviours;

import java.util.ArrayList;

import jade.core.behaviours.Behaviour;
import logic.CPU.CPU;
import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.CPU.Behaviours.SendCompilationFilesBehaviour;

public class CompileProjectBehaviour extends Behaviour
{
	CPU agent;
	String path;

	public CompileProjectBehaviour(String path)
	{
		this.path = path;
	}
	
	@Override
	public void action()
	{
		agent = (CPU) myAgent;
		
		CompilationFile cf = null;
		ArrayList<CompilationFile> files = agent.getFiles();
		
		if (files.size() == 0)
			return;

        for (int i = 0; i < files.size(); i++)
        {
        	cf = files.get(i);
        	
        	if (cf.getBinary() == null) // Not already compiled
        	{
        		if (!cf.compile())
            	{
            		((ExtendedAgent)myAgent).errorPrintln("Failed to compile " + cf.getFilename());
            		return;
            	}
        		
        		agent.files.set(i, cf);
        	}
		}
        
        agent.println("Successfully compiled!");
        agent.addBehaviour(new SendCompilationFilesBehaviour());
	}

	@Override
	public boolean done()
	{
		return true;
	}
}
