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
		
		while (agent.files.size() > 0)
		{
			if (agent.files.get(0).binary != null)
			{
				ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
				msg.addReceiver(agent.getClientAID());
				msg.setByteSequenceContent(agent.files.get(0).getBinary());
				msg.addUserDefinedParameter("filename", agent.files.get(0).getFilename());
				agent.send(msg);
			}
			
			agent.files.remove(0);
		}
		
	}

	@Override
	public boolean done()
	{
		return true;
	}
	
}
