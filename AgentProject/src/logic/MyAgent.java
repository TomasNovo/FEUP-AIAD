package logic;

import jade.core.*;
import jade.core.behaviours.Behaviour;

public class MyAgent extends Agent
{
	@Override
	protected void setup()
	{
		super.setup();
		
		addBehaviour(new WorkingBehaviour());
		
		System.out.println("Ola!");
	}
	
	class WorkingBehaviour extends Behaviour
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
