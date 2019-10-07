package logic;

import jade.core.Agent;
import jade.core.behaviours.Behaviour;

public class CPU extends Agent
{
	@Override
	protected void setup()
	{
		super.setup();
		
		addBehaviour(new CompilingBehaviour());
		
		System.out.println("Ola!");
	}
	
	class CompilingBehaviour extends Behaviour
	{
		int iterationCounter = 0;
		String[] files;
		double[] times;
		
		public CompilingBehaviour(String[] files)
		{
			this.files = files;
			times = new double[files.length];
		}
		
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
