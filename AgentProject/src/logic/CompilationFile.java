package logic;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class CompilationFile implements java.io.Serializable
{
	private static final long serialVersionUID = 2062965636861017777L;
	
	public String path;
	public String filename;
	public String projectname;
	public String filenameNoExtention;
	public String extension;
	public String text;
	public byte[] binary;
	public int size;
	public double compilationTime;
	
	public CompilationFile()
	{
		
	}
	
	public CompilationFile(File file)
	{
        try
		{
    		path = file.getParent();
    		projectname = file.getParentFile().getName();
			filename = file.getName();
			filenameNoExtention = filename.substring(0, filename.indexOf('.'));
			extension = filename.substring(filename.lastIndexOf('.'));
			
    		BufferedReader in = new BufferedReader(new FileReader(file));
    		text = "";
			String line;
			
			while ((line = in.readLine()) != null)
				text += line + System.lineSeparator();
			
			in.close();
			
			size = text.length();
		}
		catch (FileNotFoundException e)
		{
			size = -1;
		}
        catch (IOException e)
		{
			size = -1;
		}
        
        compilationTime = 0.0;
	}
	
	
	public boolean compile()
	{			
		Process process;
		try
		{
			String binaryPath = path + File.separator + filenameNoExtention + Macros.binaryFileExtension;
			String codePath = path + File.separator + filenameNoExtention + Macros.codeFileExtension;
			String command = "g++ -std=c++11 -c -o " + "\"" + binaryPath + "\" " + "\"" + codePath + "\"";
			
			long start = System.nanoTime();
			process = Runtime.getRuntime().exec(command);

			int returnValue;
			try
			{
				returnValue = process.waitFor();
			}
			catch (InterruptedException e)
			{
				returnValue = -1;
			}
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
			String line;
			while ((line = reader.readLine()) != null)
			{
				System.err.println(line);
			}
			
			this.compilationTime = (System.nanoTime() - start) / (double)1E9;
			
			if (returnValue != 0)
			{
				this.compilationTime = -1;
				return false;
			}
			
			binary = Files.readAllBytes(Paths.get(binaryPath));
		}
		catch (IOException e)
		{
			e.printStackTrace();
			this.compilationTime = -1;
			return false;
		}
		
		return true;
	}


	// Set methods
	public void setBinary(byte[] b)
	{
		this.binary = b;
	}
	
	// Get methods
	public String getPath()
	{
		return this.path;
	}
	
	public String getFilename()
	{
		return this.filename;
	}
	
	public String getProjectName()
	{
		return this.projectname;
	}
	
	public String getFilenameNoExtension()
	{
		return this.filename;
	}
	
	public String getText()
	{
		return this.text;
	}
	
	public byte[] getBinary()
	{
		return this.binary;
	}
	
	public int getSize()
	{
		return this.size;
	}
	
	public double getCompilationTime()
	{
		return this.compilationTime;
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
	
	public static CompilationFile deserialize(byte[] serializedObject)
	{
		CompilationFile cf;
		
		try
		{
		     byte b[] = serializedObject;
		     ByteArrayInputStream bi = new ByteArrayInputStream(b);
		     ObjectInputStream si = new ObjectInputStream(bi);
		     cf = (CompilationFile) si.readObject();
		}
		catch (Exception e) 
		{
		     return null;
		}
		
		return cf;
	}
	
}
