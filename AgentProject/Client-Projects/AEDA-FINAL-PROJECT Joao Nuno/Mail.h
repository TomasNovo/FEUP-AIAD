/*
 * Mail.h
 *
 *  Created on: Nov 10, 2017
 *      Author: jubas
 */

#ifndef MAIL_H_
#define MAIL_H_

#include <string>

class Associate;

//!  The Mail Class
/*!
 * The Network is used by the associates to send and receive mails. So, each mail will have an author, a title,
 * the body of the mail and a data associated with it.
 */
class Mail {
public:

	//Constructor

	/**
	 * @brief Default Constructor
	 */
	Mail();

	/**
	 * @brief Creates a new mail from the associate with a title and a body
	 *
	 * @param associate - The Associate who sent the email
	 * @param title - string with the mail's name
	 * @param body - string with all the mail body text
	 * @param date - string with the mail's date
	 */
	Mail(Associate * associate, std::string title, std::string body, std::string date);

	//Destructor

	/**
	 * @brief Default Destructor
	 */
	virtual ~Mail();

	//Get Methods

	/**
	 * @brief Returns the author from the mail
	 */
	Associate * getAuthor() const;

	/**
	 * @brief Returns the mail title
	 */
	std::string getTitle() const;

	/**
	 * @brief Returns the mail body
	 */
	std::string getBody() const;

	/**
	 * @brief Returns the mail date
	 */
	std::string getDate() const;

	//Set Methods

	/**
	 * @brief Sets/Changes the author from a mail
	 *
	 * @param author - Associate who wrote the mail
	 */
	void setAuthor(Associate * author);

	/**
	 * @brief Sets/Changes the title from a mail
	 *
	 * @param title - The title of the mail
	 */
	void setTitle(std::string title);

	/**
	 * @brief Sets/Changes the body from a mail
	 *
	 * @param body - The body of the mail
	 */
	void setBody(std::string body);

	/**
	 * @brief Sets/Changes the date from a mail
	 *
	 * @param date - The date of the mail
	 */
	void setDate(std::string date);

private:
	Associate * author; ///< The mail's author
	std::string title; ///< The mail's title
	std::string body; ///< The mail's body
	std::string date; ///< The mail's date
};

#endif /* MAIL_H_ */
