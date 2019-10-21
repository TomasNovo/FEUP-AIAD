package logic.Behaviours;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Iterator;

import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import logic.CPU;
import logic.Client;
import logic.CompilationFile;
import logic.Behaviours.CompileProjectBehaviour;

/*TODO
 * 
 *  ReceiveProjectBehaviour() - change .files to get method
 * 
 *  112, 133, 138 - change .clientAID to get method
 * */

public class ReceiveProjectBehaviour extends Behaviour
{
	
	String pathToFolder;
	
	public ReceiveProjectBehaviour()
	{
		((CPU) this.myAgent).files = new ArrayList<CompilationFile>();
	}
	
	@Override
	public void action()
	{
		if (!selectProject()) 
		{
			((Client) this.myAgent).errorPrintln("ERROR: CPU: Error receiving file");
			return;
		}
	
		((CPU) this.myAgent).addBehaviour(new CompileProjectBehaviour(pathToFolder));
	}
	
	public boolean selectProject()
	{
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
		
		DFAgentDescription project = null;
		Integer deadline = null;
		
		for (int i = 0; i < projects.length; i++) // Searches for the project with the lowest deadline
		{
			dfad = projects[i];
			sd = (ServiceDescription) dfad.getAllServices().next();
			
			for (Iterator it = sd.getAllProperties(); it.hasNext();) // Gets the deadline property of the service and saves it if it is lower than the current one
			{
				Property p = (Property) it.next();
				
				if (p.getName().equals("deadline"))
				{
					if (project == null || (Integer)p.getValue() < deadline)
					{
						project = dfad;
						deadline = (Integer)p.getValue();
					}
				}
				
				break;
			}
		}
		
		  
		return saveProject(project);
	}
	
	public boolean saveProject(DFAgentDescription project)
	{
		ServiceDescription sd = (ServiceDescription) project.getAllServices().next();
		String projectName = sd.getName();
		createFileFolder(projectName);
		
		for (Iterator it = sd.getAllProperties(); it.hasNext();)
		{
			Property p = (Property) it.next();
			
			if (p.getName().equals("file"))
			{
				CompilationFile cf = (CompilationFile) p.getValue();
				((Client) this.myAgent).files.add(cf);
				
				File f = new File("CPU-Projects" + File.separator + ((CPU) this.myAgent).clientAID.getLocalName() + File.separator + projectName + File.separator + cf.getFilename());
				pathToFolder = f.getPath().substring(0, f.getPath().lastIndexOf(File.separator));
						
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
		return new File("CPU-Projects/" + ((CPU) this.myAgent).clientAID.getLocalName()).mkdirs();
	}
	
	public boolean createFileFolder(String filename)
	{
		return new File("CPU-Projects/" + ((CPU) this.myAgent).clientAID.getLocalName() + File.separator + filename).mkdirs();
	}	
	

	@Override
	public boolean done()
	{
		return true;
	}
	
}