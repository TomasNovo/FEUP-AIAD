/*
 * Network.h
 *
 *  Created on: Nov 10, 2017
 *      Author: jubas
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <vector>
#include <string>

class Mail;

//!  The Network Class
/*!
 * The Network is used by the associates to send and receive mails.
 * Only associates which have paid all the annual pays in the last 5 years can send and receive mails.
 * The associates which have not paid any of the last 5 annual pays can neither receive or send mails.
 * The rest of the associates can only receive mails.
 */
class Network {
public:

	//Constructors
	/**
	 * @brief Default Network Constructor
	 */
	Network();

	/**
	 * @brief Full Network Constructor
	 *
	 * @param mails - A vector containing pointers to all the mails in the network
	 */
	Network(std::vector<Mail *> mails);

	//Destructors
	/**
	 * @brief Default Network Destructor
	 */
	virtual ~Network();

	//Set Methods
	/**
	 * @brief Sets/Changes the vector containing the mails the network has in it
	 *
	 * @param mails - vector of pointers to mails
	 */
	void setMails(std::vector<Mail *> mails);

	//Get Methods

	/**
	 * @brief Returns, in a vector, all the mails the network has in it
	 *
	 */
	std::vector<Mail *> getMails() const;

	//General

	/**
	 * @brief add a mail do the vector containing all the mails
	 *
	 * @param newMail - the new mail to be added
	 */
	void addMail(Mail * newMail);

	/**
	 * @brief Sorts the mails by their title and date
	 *
	 * @param type - receives a string with all the information of the mails
	 */
	void sortMails(std::string type);

private:
	std::vector<Mail *> mails; ///< A vector of mails containing all the mails the network has in it
};

#endif /* NETWORK_H_ */
