package logic.Auction;

import logic.Client;

public class Bid {

	private final Client bidder;
	
	/**
	 * Can be h(hours), m(minutes), s(seconds)
	 */
	private final String deadline;
	
	private int numberOfUnit;
	private char typeOfUnit;
	
	private int deadlineInSeconds = 0;
	
	public Bid(Client b, String d)
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
			case 'h':
				this.deadlineInSeconds = this.numberOfUnit * 3600;
				break;
				
			case 'm':
				this.deadlineInSeconds = this.numberOfUnit * 60;
				break;
				
			case 's':
				this.deadlineInSeconds = this.numberOfUnit;
				break;
				
			default: break;
		}
	
	}
}
