package logic.CPU.Behaviours;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;

import jade.core.behaviours.Behaviour;
import jade.core.behaviours.TickerBehaviour;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.Macros;
import logic.ProjectInfo;
import logic.CPU.Behaviours.CompileProjectBehaviour;
import logic.CPU.Behaviours.Negotiation.SendNegotiationBehaviour;
import logic.Client.Behaviours.Negotiation.ReceiveNegotiationBehaviour;
import logic.CPU.CPU;


public class ReceiveProjectBehaviour extends Behaviour
{
	CPU agent;
	ArrayList<ProjectInfo> finishedProjects;

	public ReceiveProjectBehaviour(CPU agent)
	{
		this.agent = agent;
		finishedProjects = new ArrayList<ProjectInfo>();
	}
	
	@Override
	public void action()
	{
		if (selectProject())
		{
			agent.println("Received a proposal from \"" + agent.clientAID.getLocalName() + "\" for project \"" + agent.info.name + "\"");
			agent.addBehaviour(new SendNegotiationBehaviour());
		}
	}
	
	
	public boolean selectProject()
	{
		ACLMessage msg = this.myAgent.blockingReceive();
		agent.initializeFiles();
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
		agent.projectPath = Macros.cpuProjectPath + "/" + agent.getClientAID().getLocalName() + "/" + projectName;
		createProjectFolder();
		
		for (int i = 0; i < info.files.size(); i++)
		{
			CompilationFile cf = info.files.get(i);
			cf.path = agent.projectPath;
						
			File f = new File(agent.projectPath + "/" + cf.getFilename());
					
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
		
		
		agent.info = info;
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
		return new File(agent.projectPath).mkdirs();
	}

	@Override
	public boolean done()
	{
		return true;
	}	
	
}