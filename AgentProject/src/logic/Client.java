package logic;

import jade.core.Agent;
import jade.core.behaviours.Behaviour;

public class Client extends Agent
{
	int id = 0;
	
	String[] files;
	
	@Override
	protected void setup()
	{
		super.setup();
		
		addBehaviour(new OfferProjectBehaviour());
		
		System.out.println("Ola!");
	}
	
	class OfferProjectBehaviour extends Behaviour
	{
		int iterationCounter = 0;
		
		@Override
		public void action()
		{
			System.out.println(++iterationCounter);
		}

		@Override
		public boolean done()
		{
			return (iterationCounter == 15);
		}
		
	}
}
