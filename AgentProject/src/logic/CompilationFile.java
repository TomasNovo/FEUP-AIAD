package logic;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class CompilationFile
{
	String path;
	String filename;
	String text;
	byte[] binary;
	int size;
	double compilationTime;
	
	public CompilationFile(File file)
	{
        try
		{
    		path = file.getAbsolutePath();
			filename = file.getName();
			
    		BufferedReader in = new BufferedReader(new FileReader(file));
			String line = "";
			
			while ((line = in.readLine()) != null)
				text += line;
			
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
	
	
	public double Compile()
	{	
		long start = System.nanoTime();
		double time = -1;
		
		Process process;
		try
		{
			process = Runtime.getRuntime().exec("g++ -c " + path + filename);
			BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
			BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(process.getOutputStream()));
			
			while (process.isAlive())
			
			if (process.exitValue() == 0)
				time = (start - System.nanoTime()) / (double)10E9;
			else
				time = -1;

		}
		catch (IOException e)
		{
			time = -1;
			e.printStackTrace();
		}
		
		return time;
	}
	
}
