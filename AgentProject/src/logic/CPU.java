package logic;

import java.io.File;
import java.util.ArrayList;

import logic.CompilationFile;
import logic.Behaviours.ReceiveProjectBehaviour;

import jade.core.AID;

public class CPU extends ExtendedAgent
{
	int id = 0;
	private ArrayList<CompilationFile> files;
	private String projectPath;
	
	private AID clientAID;
	private boolean clientFolder;
	
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
		new File("CPU-Projects").mkdirs();
		
		addBehaviour(new ReceiveProjectBehaviour(this));
		
		println("Ola!");
	}
	
	public void initializeFiles()
	{
		this.files = new ArrayList<CompilationFile>();
	}
	
	// Get e Set Methods
	public int getID()
	{
		return this.id;
	}
	
	public ArrayList<CompilationFile> getFiles()
	{
		return this.files;
	}
	
	public String getProjectPath()
	{
		return this.projectPath;
	}
	
	public void setClientAID(AID aid)
	{
		this.clientAID = aid;
	}
	
	public AID getClientAID()
	{
		return this.clientAID;
	}
	
	public boolean getClientFolder()
	{
		return this.clientFolder;
	}

}
