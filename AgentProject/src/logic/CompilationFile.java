package logic;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

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
	
	
	public void compile()
	{	
		long start = System.nanoTime();
		double time = -1;
		
		Process process;
		try
		{
			String filenameNoExtention = filename.substring(0, filename.indexOf('.'));
    		String folder = path.substring(0, path.lastIndexOf(File.separator) + 1);
			String binaryPath = folder + filenameNoExtention + ".o";
			String command = "g++ -c -o " + "\"" + binaryPath + "\" " + "\"" + path + "\"";
			
			process = Runtime.getRuntime().exec(command);
			BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
			BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(process.getOutputStream()));
			
			while (process.isAlive())
			{}
			
			
			String line;
			while ((line = reader.readLine()) != null)
			{
				System.err.println(line);
			}
			
			int returnValue = process.exitValue();
			
			time = (System.nanoTime() - start) / (double)1E9;

			if (returnValue != 0)
			{
				time = -1;
				return;
			}
			
			binary = Files.readAllBytes(Paths.get(binaryPath));
			
			int a = 0;
				
		}
		catch (IOException e)
		{
			time = -1;
			e.printStackTrace();
		}
	}
	
}
