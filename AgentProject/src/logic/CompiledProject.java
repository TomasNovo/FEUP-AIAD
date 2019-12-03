package logic;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class CompiledProject implements java.io.Serializable
{
	private static final long serialVersionUID = -272036790499164670L;

	public CompiledProjectErrorType errorType;
	public ArrayList<Pair<String, byte[]>> compiledFiles;
	public Bid deadline;
	public double totalCompilationTime = 0.0; // In seconds
	
	public CompiledProject(Bid deadline)
	{
		this.errorType = CompiledProjectErrorType.SUCCESS;
		this.compiledFiles = new ArrayList<Pair<String,byte[]>>();
		this.deadline = deadline;
	}
	
	public void addCompiledFile(CompilationFile cf)
	{
		if (cf.compilationTime == -1)
		{
			errorType = CompiledProjectErrorType.COMPILATIONERROR;
			return;
		}
		
		totalCompilationTime += cf.compilationTime;
		
		if ((int)(totalCompilationTime * 1000.0) > deadline.getDeadlineInMilliSeconds())
		{
			errorType = CompiledProjectErrorType.DEADLINEEXCEEDED;
		}
				
		compiledFiles.add(new Pair<String, byte[]>(cf.filename, cf.binary));
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
	
	
	public static CompiledProject deserialize(byte[] serializedObject)
	{
		CompiledProject cf;
		
		try
		{
		     byte b[] = serializedObject;
		     ByteArrayInputStream bi = new ByteArrayInputStream(b);
		     ObjectInputStream si = new ObjectInputStream(bi);
		     cf = (CompiledProject) si.readObject();
		}
		catch (Exception e) 
		{
		     return null;
		}
		
		return cf;
	}
	
}

