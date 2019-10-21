package logic.Behaviours;

import jade.core.behaviours.Behaviour;
import jade.lang.acl.ACLMessage;
import logic.CPU;

/* TODO
 * 
 * 20 + 1- .file => getFiles()
 * 23 + 1- .clientAID => getClientAID()     
 * 24 + 1- .file => getFiles()    
 * 25 + 1 - .file => getFiles() 
 * 
 * */

public class SendCompilationFilesBehaviour extends Behaviour
{
	@Override
	public void action()
	{
		for	(int i = 0; i < ((CPU) this.myAgent).files.size(); i++)
		{
			ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
			msg.addReceiver(((CPU) this.myAgent).clientAID);
			msg.setByteSequenceContent(((CPU) this.myAgent).files.get(i).getBinary());
			msg.addUserDefinedParameter("filename", ((CPU) this.myAgent).files.get(i).getFilename());
			((CPU) this.myAgent).send(msg);
		}
		
	}

	@Override
	public boolean done()
	{
		return true;
	}
	
}
