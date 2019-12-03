/*
 * SummerSchool.h
 *
 *  Created on: Nov 14, 2017
 */

#ifndef SUMMERSCHOOL_H_
#define SUMMERSCHOOL_H_
#include <list>
#include <string>
#include "Event.h"

class Associate;

//! The Trainer Class
/*!
 * Trainers are the people who lecture during the summerschools
 */
class Trainer {
public:
	/**
	 * @brief Full Trainer Constructor
	 *
	 * @param name - The name of the trainer
	 * @param institution - The institution of the trainer
	 */
	Trainer(std::string name, std::string institution) :
			name(name), institution(institution) {
	}
	;

	/**
	 * @brief Default Trainer Destructor
	 */
	~Trainer();

	/**
	 * @brief Returns the name of the trainer
	 *
	 */
	std::string getName() const {
		return this->name;
	}
	;

	/**
	 * @brief Returns the institution of the trainer
	 *
	 */
	std::string getInstitution() const {
		return this->institution;
	}
	;

private:
	std::string name; ///< The name of the trainer
	std::string institution; ///< The institution of the trainer
};

//!  The SummerSchool Class - Derived Class from the Super Event Class
/*!
 * A summerSchool is a special type of event. This one has some trainers who will give lectures during the event
 */
class SummerSchool: public Event {
public:

	//=========================CONSTRUCTORS===============================
	//====================================================================
	/*
	 * @brief Default Constructor
	 */
	SummerSchool();

	/**
	 * @brief Full SummerSchool Constructor
	 *
	 * @param event_request - The associates that requested the summerschool (up to 3)
	 * @param event_organizers - The associates that requested the summerschool (up to 3) and the ones who will help organize
	 * @param date - The date of the summerschool
	 * @param local - The local of the summerschool
	 * @param theme - The theme of the summerschool
	 * @param phase - The phase of the summerschool
	 * @param association - The Association that promotes the summerschool
	 * @param trainers - A list of all the trainers that will lecture during the summerschool
	 */
	SummerSchool(std::vector<Associate *> event_request,
			std::vector<Associate *> event_organizers, std::string date,
			std::string local, std::string theme, int phase,
			Association * association, std::list<Trainer *> trainers);

	/**
	 * @brief Full SummerSchool Constructor
	 *
	 * @param event_request - The associates that requested the summerschool (up to 3)
	 * @param event_organizers - The associates that requested the summerschool (up to 3) and the ones who will help organize
	 * @param date - The date of the summerschool
	 * @param local - The local of the summerschool
	 * @param theme - The theme of the summerschool
	 * @param phase - The phase of the summerschool
	 * @param association - The Association that promotes the summerschool
	 * @param trainers - A list of all the trainers that will lecture during the summerschool
	 * @param given_support - The amount the Association gives to promote de event
	 */
	SummerSchool(std::vector<Associate *> event_request,
			std::vector<Associate *> event_organizers, std::string date,
			std::string local, std::string theme, int phase,
			Association * association, std::list<Trainer *> trainers,
			long double given_support);

	//=========================DESTRUCTORS================================

	//====================================================================

	/**
	 * @brief Default SummerSchool Destructor
	 */
	virtual ~SummerSchool();

	//=========================GET METHODS================================

	//====================================================================

	/**
	 * @brief Returns the money the Association gave to support the event
	 *
	 */
	long double getSupport() const;

	/**
	 * @brief Returns the type of the event
	 */
	std::string getType() const;

	/**
	 * @brief Returns all the trainers who will lecture during the summerSchool
	 *
	 */
	std::list<Trainer *> getTrainers() const;

	/**
	 * @brief Returns the estimative of people attending the summerSchool
	 *
	 */
	int getEstimative() const;

	//=========================GENERAL METHODS============================

	//====================================================================

	/**
	 * @brief Returns (in a string) all the information about a summerSchool
	 *
	 */
	std::string showInfo() const;

private:
	std::string type = "SummerSchool";///< The type of the Event (SummerSchool)
	std::list<Trainer *> trainers;	///< All trainers in the SummerSchool
	long double given_support; ///< The value of the monetary support given by the association
};

#endif /* SUMMERSCHOOL_H_ */
