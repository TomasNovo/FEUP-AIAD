package logic.Auction;

import logic.ExtendedAgent;
import logic.Macros;
import logic.Client.Client;

public class Bid {

	private final ExtendedAgent	 bidder;
	
	/**
	 * Can be h(hours), m(minutes), s(seconds)
	 */
	private final String deadline;
	
	private int numberOfUnit;
	private char typeOfUnit;
	
	private int deadlineInSeconds = 0;
	
	public Bid(ExtendedAgent b, String d)
	{
		this.bidder = b;
		this.deadline = d;
		parseDeadline();
	}
	
	public String getClientName()
	{
		return this.bidder.getLocalName();
	}
	
	public String getDeadline()
	{
		return this.deadline;
	}
	
	public int getDeadlineInSeconds()
	{
		return this.deadlineInSeconds;
	}
	
	public void parseDeadline()
	{
		this.numberOfUnit = Integer.parseInt(deadline.substring(0, this.deadline.length() - 1));
		this.typeOfUnit = deadline.substring(this.deadline.length() - 1, this.deadline.length()).charAt(0);
		
		switch(typeOfUnit)
		{
			case Macros.hours:
				this.deadlineInSeconds = this.numberOfUnit * 3600;
				break;
				
			case Macros.minutes:
				this.deadlineInSeconds = this.numberOfUnit * 60;
				break;
				
			case Macros.seconds:
				this.deadlineInSeconds = this.numberOfUnit;
				break;
				
			default: break;
		}
	
	}
}
