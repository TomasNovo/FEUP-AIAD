package logic.CPU.Behaviours;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;

import jade.core.behaviours.TickerBehaviour;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.Macros;
import logic.ProjectInfo;
import logic.CPU.Behaviours.CompileProjectBehaviour;
import logic.CPU.Behaviours.Negotiation.SendNegotiationBehaviour;
import logic.Client.Behaviours.Negotiation.ReceiveNegotiationBehaviour;
import logic.CPU.CPU;


public class ReceiveProjectBehaviour extends TickerBehaviour
{
	CPU agent;
	String pathToFolder;
	ArrayList<ProjectInfo> finishedProjects;

	public ReceiveProjectBehaviour(CPU agent)
	{
		super(agent, 1000);
		this.agent = agent;
		finishedProjects = new ArrayList<ProjectInfo>();
	}
	
	@Override
	public void onTick()
	{
		if (selectProject())
		{
			/* TODO: Handle deadline negociation
			 * 
			 */
			agent.addBehaviour(new SendNegotiationBehaviour(pathToFolder));
			
		}
			
//		else
//			agent.println("No project");
		
		

	}
	
	
	public boolean selectProject()
	{
		agent.initializeFiles();
		
		ACLMessage msg = this.myAgent.blockingReceive();
		agent.clientAID = msg.getSender();
		ProjectInfo info = ProjectInfo.deserialize(msg.getByteSequenceContent());
		
		if (!saveProject(info))
		{
			agent.errorPrintln("Failed to save project " + info.name + "!");
			return false;			
		}
		
		return true;
	}
	
	public boolean saveProject(ProjectInfo info)
	{
		String projectName = info.name;
		pathToFolder = Macros.cpuProjectPath + "/" + agent.getClientAID().getLocalName() + "/" + projectName;
		createProjectFolder();
		
		int j = 0;
		for (int i = 0; i < info.files.size(); i++)
		{
			CompilationFile cf = info.files.get(i);
			cf.path = pathToFolder;
			
			if (cf.extension.equals(Macros.codeFileExtension))
			{
				agent.files.add(cf);
			}
						
			File f = new File(pathToFolder + "/" + cf.getFilename());
					
			try
			{	
				Files.write(f.toPath(), cf.getText().getBytes(), StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
			}
			catch (IOException e)
			{
				e.printStackTrace();
				return false;
			}
		}


		return true;
	}
	
	private int searchOldProject(ProjectInfo info)
	{
		for (int i = 0; i < finishedProjects.size(); i++)
		{
			if (finishedProjects.get(i).equals(info))
				return i;
		}
		
		return -1;
	}
	
	public boolean createProjectFolder()
	{
		return new File(pathToFolder).mkdirs();
	}	
	
}