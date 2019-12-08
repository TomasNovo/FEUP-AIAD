/*
 * Conference.h
 *
 *  Created on: Nov 14, 2017
 */

#ifndef CONFERENCE_H_
#define CONFERENCE_H_

#include "Event.h"

//!  The Conference Class - Derived Class from the Super Event Class
/*!
 * A conference is a special type of event. This one has a estimative of people who will attend to the conference.
 */
class Conference: public Event {
public:

	//=========================CONSTRUCTORS===============================
	//====================================================================
	/**
	 * @brief Default Constructor
	 */
	Conference();

	/**
	 * @brief Full Conference Constructor
	 *
	 * @param event_request - The associates that requested the conference (up to 3)
	 * @param event_organizers - The associates that requested the conference (up to 3) and the ones who will help organize
	 * @param date - The date of the conference
	 * @param local - The local of the conference
	 * @param theme - The theme of the conference
	 * @param phase - The phase of the conference
	 * @param association - The Association that promotes the conference
	 * @param estimative - The number of people estimated to go to the conference
	 */
	Conference(std::vector<Associate *> event_request,
			std::vector<Associate *> event_organizers, std::string date,
			std::string local, std::string theme, int phase, Association * association,
			int estimative);


	/**
	 * @brief Full Conference Constructor
	 *
	 * @param event_request - The associates that requested the conference (up to 3)
	 * @param event_organizers - The associates that requested the conference (up to 3) and the ones who will help organize
	 * @param date - The date of the conference
	 * @param local - The local of the conference
	 * @param theme - The theme of the conference
	 * @param phase - The phase of the conference
	 * @param association - The Association that promotes the conference
	 * @param estimative - The number of people estimated to go to the conference
	 * @param money - The amount the Association gives to promote de event
	 */
	Conference(std::vector<Associate *> event_request,
				std::vector<Associate *> event_organizers, std::string date,
				std::string local, std::string theme, int phase, Association * association,
				int estimative, long double money);

	//=========================DESTRUCTORS================================

	//====================================================================

	/**
	 * @brief Default Conference Destructor
	 */
	virtual ~Conference();

	//=========================GET METHODS================================

	//====================================================================

	/**
	 * @brief returns the number of people estimated to go to the conference
	 */
	int getEstimative() const;

	/**
	 * @brief returns the type of the event (Conference)
	 */
	std::string getType() const;

	/**
	 * @brief returns the value of the monetary support given by the association
	 */
	long double getSupport() const;

	/**
	 * @brief returns the trainers who will attend the conference
	 */
	std::list<Trainer *> getTrainers() const;



	//=========================GENERAL METHODS================================

	//========================================================================

	/**
	 * @brief returns all the information about the conference
	 */
	std::string showInfo() const;



private:
	std::string type = "Conference";///< The type of the event
	int estimative;///< The number of people estimated to go to the conference
	long double given_support; ///< The value of the monetary support given by the association
};

#endif /* CONFERENCE_H_ */
