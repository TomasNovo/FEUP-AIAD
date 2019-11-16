package logic;

import logic.Client.Client;

public class Bid implements java.io.Serializable  
{
	private static final long serialVersionUID = -888659286753456621L;

	private final ExtendedAgent	 bidder;
	
	/**
	 * Can be h(hours), m(minutes), s(seconds)
	 */
	private final String deadline;
	
	private int numberOfUnit;
	private String typeOfUnit;
	
	private int deadlineInMilliSeconds = 0;
	
	public Bid(String d)
	{
		this.bidder = null;
		this.deadline = d;
		parseDeadline();
	}
	
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
	
	public int getDeadlineInMilliSeconds()
	{
		return this.deadlineInMilliSeconds;
	}
	
	public void parseDeadline()
	{		
		if (deadline.endsWith(Macros.milliseconds))
		{
			this.numberOfUnit = Integer.parseInt(deadline.substring(0, this.deadline.length() - 2));
			this.deadlineInMilliSeconds = this.numberOfUnit;
			this.typeOfUnit = Macros.milliseconds;
		}
		else if (deadline.endsWith(Macros.hours))
		{
			this.numberOfUnit = Integer.parseInt(deadline.substring(0, this.deadline.length() - 1));
			this.deadlineInMilliSeconds = this.numberOfUnit * 60 * 60 * 1000;
			this.typeOfUnit = Macros.hours;
		}
		else if (deadline.endsWith(Macros.minutes))
		{
			this.numberOfUnit = Integer.parseInt(deadline.substring(0, this.deadline.length() - 1));
			this.deadlineInMilliSeconds = this.numberOfUnit * 60 * 1000;
			this.typeOfUnit = Macros.minutes;
		}
		else if (deadline.endsWith(Macros.seconds))
		{
			this.numberOfUnit = Integer.parseInt(deadline.substring(0, this.deadline.length() - 1));
			this.deadlineInMilliSeconds = this.numberOfUnit * 1000;
			this.typeOfUnit = Macros.seconds;
		}
	}
}
