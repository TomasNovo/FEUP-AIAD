package logic.CPU.Behaviours;

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

        for (int i = 0; i < agent.getFiles().size(); i++)
        {
        	cf = agent.getFiles().get(i);
        	
        	if (!cf.compile())
        	{
        		((ExtendedAgent)myAgent).errorPrintln("Failed to compile " + cf.getFilename());
        		return;
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
