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
		
		cf = null;
		
		if (agent.files.size() == 0)
			return;

        for (int i = 0; i < agent.files.size(); i++)
        {
        	cf = agent.files.get(i);
        	
        	if (cf.getBinary() == null && cf.extension.equals(Macros.codeFileExtension)) // Not already compiled code file
        	{
        		saveTimeToFile();
        		
        		if (!cf.compile())
            	{
            		((ExtendedAgent)myAgent).errorPrintln("Failed to compile " + cf.getFilename());
            		return;
            	}
        	}
		}
        
        agent.println("Successfully compiled!");
        agent.addBehaviour(new SendCompilationFilesBehaviour());
	}

	public boolean saveTimeToFile()
	{
		System.out.println("Time :" + cf.getCompilationTime());
		File f = new File(Macros.cpuProjectPath + "/" + "times.txt");
		try {
			f.createNewFile();
			
			FileWriter fw = new FileWriter(f, true);
		    BufferedWriter bw = new BufferedWriter(fw);
		    bw.write(Double.toString(cf.getCompilationTime()));
		    bw.newLine();
		    bw.close();
			
			return true;
		} catch (IOException e) {
			agent.println("Error creating times file");
			e.printStackTrace();
		}
		
		return false;
	}
	
	@Override
	public boolean done()
	{
		return true;
	}
}
