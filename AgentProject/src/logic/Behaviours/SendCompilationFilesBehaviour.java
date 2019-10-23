package logic.Behaviours;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.CPU;


public class SendCompilationFilesBehaviour extends Behaviour
{
	@Override
	public void action()
	{
		for	(int i = 0; i < ((CPU) this.myAgent).getFiles().size(); i++)
		{
			ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
			msg.addReceiver(((CPU) this.myAgent).getClientAID());
			msg.setByteSequenceContent(((CPU) this.myAgent).getFiles().get(i).getBinary());
			msg.addUserDefinedParameter("filename", ((CPU) this.myAgent).getFiles().get(i).getFilename());
			((CPU) this.myAgent).send(msg);
		}
		
	}

	@Override
	public boolean done()
	{
		return true;
	}
	
}
