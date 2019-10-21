package logic;

import java.io.File;
import java.util.ArrayList;

import logic.CompilationFile;
import logic.Behaviours.ReceiveProjectBehaviour;

import jade.core.AID;

public class CPU extends ExtendedAgent
{
	int id = 0;
	public ArrayList<CompilationFile> files;
	public String projectPath;
	
	public AID clientAID;
	public boolean clientFolder;
	
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
		new File("CPU-Projects").mkdirs();
		
		addBehaviour(new ReceiveProjectBehaviour(this));
		
		println("Ola!");
	}

}
