package logic.CPU.Behaviours;

import java.util.ArrayList;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.CPU.CPU;


public class SendCompilationFilesBehaviour extends Behaviour
{
	@Override
	public void action()
	{
		CPU agent = (CPU) myAgent;
		ArrayList<CompilationFile> files = agent.getFiles();
		
		for	(int i = 0; i < files.size(); i++)
		{
			ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
			msg.addReceiver(agent.getClientAID());
			msg.setByteSequenceContent(files.get(i).getBinary());
			msg.addUserDefinedParameter("filename", files.get(i).getFilename());
			agent.send(msg);
			
			agent.removeFile(i);
		}
		
	}

	@Override
	public boolean done()
	{
		return true;
	}
	
}
