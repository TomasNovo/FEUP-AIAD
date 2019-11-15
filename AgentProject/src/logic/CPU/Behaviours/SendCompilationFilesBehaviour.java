package logic.CPU.Behaviours;

import java.util.ArrayList;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.CompilationFile;
import logic.CompiledProject;
import logic.CPU.CPU;


public class SendCompilationFilesBehaviour extends Behaviour
{
	@Override
	public void action()
	{
		CPU agent = (CPU) myAgent;
		CompiledProject cp = new CompiledProject(agent.info.deadline);
		
		for (int i = 0; i < agent.info.toBeCompiled.size(); i++)
		{
        	int index = agent.info.toBeCompiled.get(i);
        	CompilationFile cf = agent.info.files.get(index);
        	cp.addCompiledFile(cf);
		}
		
		ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
		msg.addReceiver(agent.getClientAID());
		msg.setByteSequenceContent(cp.serialize());
		agent.send(msg);
		
		agent.addBehaviour(new ReceiveProjectBehaviour(agent));
	}

	@Override
	public boolean done()
	{
		return true;
	}
	
}
