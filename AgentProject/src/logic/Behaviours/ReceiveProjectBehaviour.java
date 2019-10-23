package logic.Behaviours;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Iterator;

import jade.core.Agent;
import jade.core.behaviours.Behaviour;
import jade.core.behaviours.TickerBehaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import logic.CPU;
import logic.Client;
import logic.CompilationFile;
import logic.Macros;
import logic.Behaviours.CompileProjectBehaviour;

/*TODO
 * 
 *  ReceiveProjectBehaviour() - change .files to get method
 * 
 *  112, 133, 138 - change .clientAID to get method
 * */

public class ReceiveProjectBehaviour extends TickerBehaviour
{
	CPU agent;
	String pathToFolder;

	public ReceiveProjectBehaviour(CPU agent)
	{
		super(agent, 1000);
		
		this.agent = agent;
	}
	
	@Override
	public void onTick()
	{
		if (!selectProject())
			agent.errorPrintln("ERROR: CPU: Error receiving file");
		else
			agent.addBehaviour(new CompileProjectBehaviour(pathToFolder));
	}
	
	public boolean selectProject()
	{
		agent.initializeFiles();
		
		DFAgentDescription dfad = new DFAgentDescription();
		ServiceDescription sd = new ServiceDescription();
		sd.setType("project");
		dfad.addServices(sd);
		
		DFAgentDescription[] projects;
		
		try
		{
			projects = DFService.search(this.myAgent, dfad);
		}
		catch (FIPAException e)
		{
			e.printStackTrace();
			return false;
		}
		
		if (projects.length == 0)
			return false;
		
		DFAgentDescription project = null;
		Integer deadline = null;
		Property p;
		
		for (int i = 0; i < projects.length; i++) // Searches for the project with the lowest deadline
		{
			dfad = projects[i];
			sd = (ServiceDescription) dfad.getAllServices().next();
						
			for (Iterator it = sd.getAllProperties(); it.hasNext();) // Gets the deadline property of the service and saves it if it is lower than the current one
			{
				p = (Property) it.next();

				if (p.getName().equals("deadline"))
				{
					if (project == null || (Integer)p.getValue() < deadline)
					{
						project = dfad;
						deadline = Integer.parseInt((String)p.getValue());
					}
					
					break;
				}
			}
		}
		
		agent.setClientAID(project.getName());
		
		return saveProject(project);
	}
	
	public boolean saveProject(DFAgentDescription project)
	{
		ServiceDescription sd = (ServiceDescription) project.getAllServices().next();
		String projectName = sd.getName();
		pathToFolder = Macros.cpuProjectPath + "/" + agent.getClientAID().getLocalName() + "/" + projectName;
		createProjectFolder(new File(projectName).getName());
		
		for (Iterator it = sd.getAllProperties(); it.hasNext();)
		{
			Property p = (Property) it.next();
			
			if (p.getName().equals("file"))
			{
				Object o = p.getValue();
				CompilationFile cf = CompilationFile.deserialize((String)p.getValue());
				agent.getFiles().add(cf); 
				
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
		}

		return true;
	}
	
	public boolean createClientFolder()
	{
		return new File(Macros.cpuProjectPath + "/" + agent.getClientAID().getLocalName()).mkdirs();
	}
	
	public boolean createProjectFolder(String filename)
	{
		return new File(Macros.cpuProjectPath + "/" + agent.getClientAID().getLocalName() + "/" + filename).mkdirs();
	}	
	
}