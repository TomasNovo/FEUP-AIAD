package logic.Client.Behaviours;

import jade.core.behaviours.Behaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;

public class RemoveProjectBehaviour extends Behaviour
{

	@Override
	public void action()
	{		
		try 
		{
			DFService.modify(this.myAgent, new DFAgentDescription());
		} 
		catch (FIPAException e) 
		{
			e.printStackTrace();
		}
	}

	@Override
	public boolean done() 
	{
		return true;
	}

}
