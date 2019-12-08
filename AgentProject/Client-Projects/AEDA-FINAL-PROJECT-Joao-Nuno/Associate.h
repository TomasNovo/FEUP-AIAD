/*
 * Associate.h
 *
 */

#ifndef ASSOCIATE_H_
#define ASSOCIATE_H_

#include <vector>
#include <string>

class Area;
class SubArea;
class Association;

//! The NotUpToDate Class
/*!
 * NotUpToDate is a class which instances are called when an associate decides to pay the annual pay, but he still has not
 * paid a previous year.
 * Its useful in throwing exceptions, outside of that it has no real use.
 */
class NotUpToDate {

public:
	/**
	 * @brief Full NotUpToDate Constructor
	 *
	 * @param triedYear - The id of the associate who is trying to pay the annual pay
	 * @param uniqueID - The year the associate is trying to pay
	 * @param lastPaid - The last year the associate has paid
	 */
	NotUpToDate(int triedYear, int uniqueID, int lastPaid) :
			triedYear(triedYear), uniqueID(uniqueID), lastPaid(lastPaid) {
	}
	;

	/**
	 * @brief Returns the id of the associate trying to pay the annual pay
	 */
	int getID() const {
		return this->uniqueID;
	}

	/**
	 * @brief Returns the year the associate is trying to pay
	 */
	int getYear() const {
		return this->triedYear;
	}

	/**
	 * @brief Returns the last year the associate has paid
	 */
	int getLast() const {
		return this->lastPaid;
	}

private:
	int uniqueID; ///< The id of the associate who is trying to pay the annual pay
	int triedYear;		///< The year the associate is trying to pay
	int lastPaid;		///< The last year the associate has paid
};

//! The NotEnoughMoney Class
/*!
 * NotEnoughMoney is a class which instances are called when an associate does not have enough money in his wallet to pay
 * the annual pay.
 * Its useful in throwing exceptions, outside of that it has no real use.
 */
class NotEnoughMoney {
private:
	int uniqueID;///< The id of the associate who is trying to pay the annual pay

public:
	/**
	 * @brief Full NotEnoughMoney Constructor
	 *
	 * @param uniqueID - The id of the associate who is trying to pay the annual pay
	 */
	NotEnoughMoney(int uniqueID) :
			uniqueID(uniqueID) {
	}
	;

	/**
	 * @brief Returns the id of the associate trying to pay the annual pay
	 */
	int getID() const {
		return this->uniqueID;
	}

};

//! The NotAlreadyPaid Class
/*!
 * AlreadyPaid is a class which instances are called when an associate tries to pay the annual pay of an year
 * he has already paid.
 * Its useful in throwing exceptions, outside of that it has no real use.
 */
class AlreadyPaid {
private:
	int year;		///< The year the associate is trying to pay
	int uniqueID;///< The id of the associate who is trying to pay the annual pay
public:
	/**
	 * @brief Full AlreadyPaid Constructor
	 *
	 * @param year - The year the associate is trying to pay
	 * @param uniqueID - The id of the associate who is trying to pay the annual pay
	 */
	AlreadyPaid(int year, int uniqueID) :
			uniqueID(uniqueID), year(year) {
	}
	;

	/**
	 * @brief Returns the id of the associate trying to pay the annual pay
	 */
	int getID() const {
		return this->uniqueID;
	}

	/**
	 * @brief Returns the year the associate is trying to pay
	 */
	int getYear() const {
		return this->year;
	}
};

//!  The Associate Class
/*!
 * An Association consists in a group of associates. Although each associate has a name, they are distinguished by
 * their unique ID. Besides this, each one also works for an Institution and has some scientific areas of interest.
 * They also have access to a Network where the associates can send and receive emails, taking into account the
 * frequency the associates pay the annual pay.
 */
class Associate {

public:

	//=============================================Constructors================================================

	//=========================================================================================================

	/**
	 * @brief Default Associate Constructor
	 *
	 */
	Associate();

	/**
	 * @brief Temporary constructor to look in unordered_set
	 *
	 *
	 *
	 */
	Associate(int uniqueID);


	/**
		 * @brief Full Associate Constructor
		 *
		 * The uniqueID is given automatically and incrementally.
		 * Every associate has a predefined 500 personal Wallet start.
		 *
		 * @param asso - The Association the associate belongs to
		 * @param name - The associate's name
		 * @param institution - The associate's institution
		 * @param interests - The associate's areas of interest
		 */
		Associate(Association * asso, std::string name, std::string institution,
				std::vector<Area*> interests);

	/**
	 * @brief Full Associate Constructor
	 *
	 * The uniqueID is given automatically and incrementally.
	 * Every associate has a predefined 500 personal Wallet start.
	 *
	 * @param asso - The Association the associate belongs to
	 * @param name - The associate's name
	 * @param institution - The associate's institution
	 * @param interests - The associate's areas of interest
	 * @param status - The associate's status
	 * @param paidYears - The Yeas Paid
	 * @param uniqueID - the copied ID
	 * @param divulgations - number of divulgations
	 * @param personalWallet - the money
	 *
	 */
	Associate(Association * asso, std::string name, std::string institution,
			std::vector<Area*> interests, float personalWallet,
			std::string status, std::vector<int> paidYears, int uniqueID,
			int divulgations);

	/**
	 * @brief Associate Constructor
	 *
	 * @param association - The Association the associate belongs tu
	 * @param file_string - a string from a file containing all the info in the following order:
	 *  ID/ Name/ Instituion/ Interest Areas/ Wallet/ PaidYears/ Number of divulgations
	 */
	Associate(Association * association, std::string file_string);
	//=============================================Destructors================================================

	//========================================================================================================

	/**
	 * @brief Default Associate Destructor
	 */
	virtual ~Associate();

	//=============================================Get Methods================================================

	//========================================================================================================

	/**
	 * @brief Returns the name of the Associate
	 *
	 */

	std::string getName() const;

	/**
	 * @brief Returns the uniqueID of the Associate
	 *
	 */
	int getUniqueID() const;

	/**
	 * @brief Returns a string containing the status of the Associate
	 *
	 *  E.g, "contributor", "normal"
	 *
	 */
	std::string getStatus() const;

	/**
	 * @brief Returns a vector containing all the years the Associate has paid
	 *
	 */
	std::vector<int> getPaidYears() const;

	/**
	 * @brief Returns the amount of money the Associate has (in float)
	 *
	 */
	float getPersonalWallet() const;

	/**
	 * @brief Returns the associate's institution
	 *
	 */
	std::string getInstitution() const;

	/**
	 * @brief Returns a vector with all the associate's interest areas
	 *
	 */
	std::vector<Area *> getInterestAreas() const;

	/**
	 * @brief Returns the number of divulgations the associate has done so far
	 *
	 */
	int getDivulgations() const;

	//=============================================Set Methods================================================

	//========================================================================================================

	/**
	 * @brief Sets/Changes the vector containing the interest areas of an associate
	 *
	 * @param interest - vector of pointers to areas
	 */
	void setInterestAreas(std::vector<Area *> interest);

	/**
	 * @brief Sets/Changes the string representing the current status of an associate
	 *
	 * The possible status are "normal", "subscriber", "normal".
	 *
	 * @param newStatus - String with the new status
	 */
	void setStatus(std::string newStatus);

	/**
	 * @brief Sets/Changes the vector containing the years that the associate has paid
	 *
	 * @param paid - a vector of ints representing the years
	 */
	void setPaidYears(std::vector<int> paid);

	/**
	 * @brief Sets/Changes the amount of money the associate has paid
	 *
	 * @param money - the new amount of money (float)
	 */
	void setPersonallWallet(float money);

	/**
	 * @brief Sets/Changes the associate's institution
	 *
	 * @param inst - the new institution
	 */
	void setInstitution(std::string inst);

	/**
	 * @brief Sets/Changes the number of divulgations the associate has done so far
	 *
	 * @param divulgation - the new number of divulgations
	 */
	void setDivulgations(int divulgation);

	//=============================================General Methods================================================

	//============================================================================================================

	/**
	 * @brief Adds a certain amount to the associate wallet
	 *
	 * @param more_money - the amount to be added
	 */
	void addToWallet(float more_money);

	/**
	 * @brief Subtracts a certain amount from the associate wallet
	 *
	 * @param less_money - the amount to be subtracted
	 */
	void payFromWallet(float less_money);

	/**
	 * @brief Adds a year to the vector containing all the paid years
	 *
	 * Applicable after doing a yearly payment
	 *
	 * @param year - the year paid
	 */
	void addPaidYear(int year);

	/**
	 * @brief Effectuates the payment of a year
	 *
	 * Checks if the associate has enough money to do such payment
	 * and if the associate has all the years before paid up to date.
	 * If it has no money, throws the correspondent exception (NotEnoughMoney).
	 * If his payments are not up to date, throws the exception NotUpToDate.
	 *
	 * @param year - the year to be paid
	 */
	void payYear(int year);

	/**
	 * @brief Update the string representing the status of the associate
	 *
	 * Checks with the static variable of the Association Current Year to see
	 * if the associate has the payments up to date (with the 5 years delay)
	 * and updates the string to its correspondent value.
	 *
	 */
	void updateStatus();

	/**
	 * @brief Increments the number of divulgations to the network by the associate.
	 * Occurs every time a new Mail is sent.
	 */

	void incDivulgations();

	/**
	 * @brief Determines if the associate has access to see the contents of the network.
	 * Return true if so, false otherwise;
	 */

	bool accessNetwork();

	/**
	 * @brief Determines if the associate can share a Mail in the network.
	 * Return true if so, false otherwise.
	 */

	bool shareNetwork();

	/**
	 * @brief Returns a string containing all the info of a Associate, in readable and user-friendly format
	 */
	std::string showInfo() const;

	//=============================================Operators================================================

	//=======================================================================================================

	/**
	 * @brief Overloading  < operator
	 * If two associates have the same status, they will be ordered accordingly to their name, otherwise:
	 *  contributor > subscribe > normal
	 *
	 */

	bool operator<(const Associate & lhs) const;

	/**
	 * @brief Overloading = operator
	 */

	Associate &  operator=( const Associate & lhs);

private:
	Association * association; ///< The connection between the associate and the association
	std::string name; 					///< The associate's name
	float personalWallet;  			///< The amount of money the associate has
	std::string institution; ///< The institution to which the associate is connected
	std::vector<Area *> interestAreas; ///< A vector containing pointers to all the Associate interest areas
	std::string status; ///< contributor, subscriber, normal, the possible status
	std::vector<int> paidYears; ///< A vector of integers containing all the year the Associate has paid
	int uniqueID;  						///< The unique Identifier
	static int id_provider; ///< Will ensure that every instance of this class gets a unique identifier
	int divulgations; 			///< The number of divulgations to the network

};

#endif /* ASSOCIATE_H_ */
