package logic.CPU.Behaviours;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

import jade.core.behaviours.Behaviour;
import logic.CPU.CPU;
import logic.CompilationFile;
import logic.ExtendedAgent;
import logic.Macros;
import logic.Pair;
import logic.Auction.Bid;
import logic.CPU.Behaviours.SendCompilationFilesBehaviour;

public class CompileProjectBehaviour extends Behaviour
{
	CPU agent;
	String path;
	CompilationFile cf;

	public CompileProjectBehaviour(String path)
	{
		this.path = path;
	}
	
	@Override
	public void action()
	{
		agent = (CPU) myAgent;

        for (int i = 0; i < agent.info.toBeCompiled.size(); i++)
        {
        	int index = agent.info.toBeCompiled.get(i);
        	cf = agent.info.files.get(index);
        	
        	if (cf.getBinary() == null && cf.extension.equals(Macros.codeFileExtension)) // Not already compiled code file
        	{
        		saveCompilationTime();
        		
        		if (!cf.compile())
            		agent.errorPrintln("Failed to compile " + cf.getFilename());
        		else
            		agent.println("Successfully compiled " + cf.getFilename());
        	}
		}
        
        agent.println("Successfully compiled project \"" + agent.info.name + "\"!");
        agent.addBehaviour(new SendCompilationFilesBehaviour());
	}

	public void saveCompilationTime()
	{
		agent.compilationTimes.add(new Pair<Double, Integer>(cf.getCompilationTime(), new Integer(cf.text.length())));
	}
	
	@Override
	public boolean done()
	{
		return true;
	}
}
