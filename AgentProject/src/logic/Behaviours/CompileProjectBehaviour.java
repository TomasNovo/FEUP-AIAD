package logic.Behaviours;

import jade.core.behaviours.Behaviour;
import logic.CPU;
import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Behaviours.SendCompilationFilesBehaviour;

public class CompileProjectBehaviour extends Behaviour
{
	String path;

	public CompileProjectBehaviour(String path)
	{
		this.path = path;
	}
	
	@Override
	public void action()
	{
		CompilationFile cf = null;

        for (int i = 0; i < ((CPU) this.myAgent).files.size(); i++)
        {
        	cf = ((CPU) this.myAgent).files.get(i);
        	
        	if (!cf.compile())
        	{
        		((ExtendedAgent)myAgent).errorPrintln("Failed to compile " + cf.getFilename());
        		return;
        	}
		}
        
        ((CPU) this.myAgent).println("Successfully compiled!");
        ((CPU) this.myAgent).addBehaviour(new SendCompilationFilesBehaviour());
	}

	@Override
	public boolean done()
	{
		return true;
	}
}
