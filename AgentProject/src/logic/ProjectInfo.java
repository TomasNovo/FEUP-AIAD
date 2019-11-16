package logic;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Iterator;

import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;

public class ProjectInfo implements java.io.Serializable
{
	private static final long serialVersionUID = 8401965560371787246L;
	
	public String name;
	public Bid deadline;
	public Long timestamp;
	
	public ArrayList<CompilationFile> files;
	public ArrayList<Integer> toBeCompiled;
	
	public ProjectInfo()
	{
		files = new ArrayList<CompilationFile>();
		toBeCompiled = new ArrayList<Integer>();
	}
	
	public ProjectInfo(String name, Bid deadline, Long timestamp, ArrayList<CompilationFile> files)
	{
		this.name = name;
		this.deadline = deadline;
		this.timestamp = timestamp;
		this.files = files;
	}
	
	public static ProjectInfo Parse(DFAgentDescription dfad)
	{
		ProjectInfo info = new ProjectInfo();
		ServiceDescription sd = (ServiceDescription) dfad.getAllServices().next();
		Property p = null;

		for (Iterator it = sd.getAllProperties(); it.hasNext();) // Gets the deadline property of the service and saves it if it is lower than the current one
		{
			p = (Property) it.next();

			if (p.getName().equals("ProjectInfo"))
			{
				info = (ProjectInfo) p.getValue();
//				break;
			}
		}
		
		return info;
	}
	
	public int calculateCompileNumBytes()
	{
		int sumBytes = 0;
		
		for (int i = 0; i < toBeCompiled.size(); i++)
		{
			int index = toBeCompiled.get(i);
			sumBytes += files.get(index).text.length();
		}
		
		return sumBytes;
	}
	
	public ProjectInfo Clone()
	{
		ProjectInfo info = new ProjectInfo();
		info.name = this.name;
		info.deadline = this.deadline;
		info.timestamp = this.timestamp;
		
		for (int i = 0; i < files.size(); i++)
		{
			info.files.add(files.get(i));
		}
		
		for (int i = 0; i < toBeCompiled.size(); i++)
		{
			info.toBeCompiled.add(toBeCompiled.get(i));
		}
		
		return info;
	}


	@Override
	public int hashCode()
	{
		final int prime = 31;
		int result = 1;
		result = prime * result + ((deadline == null) ? 0 : deadline.hashCode());
		result = prime * result + ((files == null) ? 0 : files.hashCode());
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		result = prime * result + ((timestamp == null) ? 0 : timestamp.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj)
	{
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (!(obj instanceof ProjectInfo))
			return false;
		ProjectInfo other = (ProjectInfo) obj;
		if (deadline == null)
		{
			if (other.deadline != null)
				return false;
		}
		else if (!deadline.equals(other.deadline))
			return false;
		if (files == null)
		{
			if (other.files != null)
				return false;
		}
		else if (!files.equals(other.files))
			return false;
		if (name == null)
		{
			if (other.name != null)
				return false;
		}
		else if (!name.equals(other.name))
			return false;
		if (timestamp == null)
		{
			if (other.timestamp != null)
				return false;
		}
		else if (!timestamp.equals(other.timestamp))
			return false;
		return true;
	}


	public byte[] serialize()
	{
		ByteArrayOutputStream bo = null;
		try
		{
			bo = new ByteArrayOutputStream();
			ObjectOutputStream so = new ObjectOutputStream(bo);
			so.writeObject(this);
			so.flush();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		 
		return bo.toByteArray();
	}
	
	public static ProjectInfo deserialize(byte[] serializedObject)
	{
		ProjectInfo cf;
		
		try
		{
		     byte b[] = serializedObject;
		     ByteArrayInputStream bi = new ByteArrayInputStream(b);
		     ObjectInputStream si = new ObjectInputStream(bi);
		     cf = (ProjectInfo) si.readObject();
		}
		catch (Exception e) 
		{
		     return null;
		}
		
		return cf;
	}
	
	
}
