package logic;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class CompilationFile
{
	private String path;
	private String filename;
	private String projectname;
	private String filenameNoExtention;
	private String text;
	private byte[] binary;
	private int size;
	private double compilationTime;
	
	public CompilationFile()
	{
		
	}
	
	public CompilationFile(File file)
	{
        try
		{
    		path = file.getAbsolutePath();
    		projectname = file.getParentFile().getName();
			filename = file.getName();
			filenameNoExtention = filename.substring(0, filename.indexOf('.'));
			
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
		long start = System.nanoTime();
		
		Process process;
		try
		{
    		String folder = path.substring(0, path.lastIndexOf(File.separator) + 1);
			String binaryPath = folder + filenameNoExtention + Macros.binaryFileExtension;
			String command = "g++ -c -o " + "\"" + binaryPath + "\" " + "\"" + path + "\"";
			
			process = Runtime.getRuntime().exec(command);
			BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
			
			while (process.isAlive())
			{}
			
			
			String line;
			while ((line = reader.readLine()) != null)
			{
				System.err.println(line);
			}
			
			int returnValue = process.exitValue();
			
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
	
	public boolean saveBinary()
	{
		try
		{
			Files.write(Paths.get("Client-Project/" + projectname + "/" + filenameNoExtention + Macros.binaryFileExtension), binary, StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
		}
		catch (IOException e)
		{
			e.printStackTrace();
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
	
}
