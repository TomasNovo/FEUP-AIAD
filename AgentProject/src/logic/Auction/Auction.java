package logic.Auction;

import java.util.ArrayList;

import logic.Client;

public class Auction {
	
	private ArrayList<Bid> bids;
	
	// The highest bid is the one that has the lowest deadlineInSeconds
	private Bid highestBid;
	
	public Auction()
	{
		this.bids = new ArrayList<Bid>();
		this.highestBid = null;
	}
	
	public boolean enterBid(Bid b)
	{
		return this.bids.add(b);
	}
	
	public void showBids()
	{
		System.out.println("Current bids:");
		for(Bid b : this.bids)
		{
			System.out.println("- " + b.getClientName() + ": " + b.getDeadline());
		}
	}
	
	public boolean makeABid(Client b, String d)
	{
		Bid bid = new Bid(b,d);
		boolean success = enterBid(bid);
		return success; 
	}
	
	public Bid getBidWithNearestDeadline()
	{
		Bid highest = this.bids.get(0);
		
		for(int i = 0; i < this.bids.size(); i++)
		{
		     if(this.bids.get(i).getDeadlineInSeconds() < highest.getDeadlineInSeconds())
		     {
		    	 highest = this.bids.get(i);
		     }
		}
		
		return highest;
	}

}
