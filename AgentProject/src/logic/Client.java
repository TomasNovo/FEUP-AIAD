package logic;

import java.io.File;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

import jade.core.AID;
import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.Property;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.lang.acl.ACLMessage;

import logic.Macros;
import logic.Auction.Bid;
import logic.Behaviours.OfferProjectBehaviour;;

public class Client extends ExtendedAgent
{
	public int id = 0;
	public ArrayList<CompilationFile> files;
	public DFAgentDescription[] CPUs;
	public String projectPath;
	public String deadline;
	public Bid b;
	
	@Override
	protected void setup()
	{
		super.setup();
		registerDF();
		
		println("Hey! Its me, " + getAID().getName());
		
		Object[] args = getArguments();
		
		if(args != null && args.length > 0 && args.length == 2) 
        {
			projectPath = args[0].toString();
            System.out.println("ProjectPath: "+ projectPath);
            
            deadline = args[1].toString();
            System.out.println("Deadline: "+ deadline);
            
            b = new Bid(this, deadline);
        
    		addBehaviour(new OfferProjectBehaviour(projectPath));
        }
	
	}
}
