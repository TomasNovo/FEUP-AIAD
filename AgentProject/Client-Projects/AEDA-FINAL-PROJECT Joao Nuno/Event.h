/*
 * Event.h
 *
 *  Created on: Nov 14, 2017
 */

#ifndef EVENT_H_
#define EVENT_H_
#include <vector>
#include <string>
#include <list>

class Associate;
class Association;
class Trainer;

//! The InvalidRequest
/*!
 * InvalidRequest is a class which instances are called when
 * the main Association decides to not support financially an event.
 * Its useful in throwing exceptions, outside of that it has no real use implementation.
 */
class InvalidRequest {

private:
	int late; ///< The number of associates whose payments where not up to date, thus creating the decision to not give support
	int total; ///< The total number of associates involved in the event
public:

	/**
	 * @brief Default Construction
	 */
	InvalidRequest(int late, int total) :

			late(late), total(total) {
	}
	;

	/**
	 * @brief Returns the number of associates whose payments where not up to date.
	 *
	 */

	int getLate() const {
		return this->late;
	}
	/**
	 * @brief Returns the total number of associates involved in the event
	 *
	 */
	int getTotal() const {

		return this->total;
	}
};

//!  The Super Event Class
/*!
 An Event must be requested by at least 3 Associates.
 The given monetary support given by the association is determined randomly,
 taking in consideration the association main fund.
 In this case, we chose to give it a value between 5-15% of the total Fund;
 This given monetary support will be later used to calculate the total number
 of organizers (then selected randomly between all the associates) and trainers.
 */
class Event {
public:

	//=========================CONSTRUCTORS===============================
	//====================================================================

	/**
	 * @brief Default Constructor
	 *
	 */
	Event();

	/**
	 * @brief Full Event Constructor
	 * The given support by the association will be any value between 5-15% of the association main fund.
	 *
	 * @param event_request - The associates that requested the event (up to 3)
	 * @param event_organizers - The associates that requested the event (up to 3) and the ones who will help organize
	 * @param date - The date of the event
	 * @param local - The local of the event
	 * @param theme - The theme of the event
	 * @param association - The Association that promotes the event
	 * @param phase - the phase request
	 */
	Event(std::vector<Associate *> event_request,
			std::vector<Associate *> event_organizers, std::string date,
			std::string local, std::string theme, int phase, Association * association);


	//=========================DESTRUCTORS===============================
	//====================================================================
	/**
	 * @brief Default Event Destructor
	 */
	virtual ~Event();

	//=========================SET METHODS===============================
	//====================================================================

	/**
	 * @brief Sets/Changes the event's date
	 *
	 * @param date - The new event's date
	 */
	void setDate(std::string date);

	/**
	 * @brief Sets/Changes the event's local
	 *
	 * @param local - The new event's local
	 */
	void setLocal(std::string local);

	/**
	 * @brief Sets/Changes the event's theme
	 *
	 * @param theme - The new event's theme
	 */
	void setTheme(std::string theme);

	/**
	 * @brief Sets/Changes the event's phase
	 *
	 * @param phase - The new event's phase
	 */
	void setPhase(int phase);


	//=========================GET METHODS===============================
	//====================================================================

	/**
	 * @brief Returns the associates that gave the initial request to the event
	 */
	std::vector<Associate *> getRequest() const;

	/**
	 * @brief Returns all the associates that are involved in the event
	 */
	std::vector<Associate *> getOrganizers() const;

	/**
	 * @brief Returns the Date of the event
	 */
	std::string getDate() const;

	/**
	 * @brief Returns the Local of the event
	 */
	std::string getLocal() const;

	/**
	 * @brief Returns the Theme of the event
	 */
	std::string getTheme() const;

	/**
	 * @brief Returns the Phase of the event
	 */
	int getPhase() const;

	/**
	 * @brief Returns the value of the monetary support given by the association to the e event
	 */
	virtual long double getSupport() const = 0;

	/**
	 * @brief Returns the Type of the event
	 */
	virtual std::string getType() const = 0;

	/**
	 * @brief Returns the trainers that will attend the event
	 */
	virtual std::list<Trainer *> getTrainers() const = 0;

	/**
	 * @brief Returns the estimative of the people who will attend the event
	 */
	virtual int getEstimative() const = 0;

	/**
	 * @brief Returns all the information of the event
	 */
	virtual std::string showInfo() const = 0;

	/**
	 * @brief Returns the name of the event
	 */
	std::string getName() const {return "";};

	/**
	 * @brief operator for both priority queues
	 *
	 * @param ev1 - Event to be compared
	 *
	 */
	bool operator < (Event* ev1) const;


protected:
	std::vector<Associate *> event_request; ///< The Associates that gave the initial request
	std::vector<Associate *> event_organizers; ///< All the associates involved with the event
	std::string date; ///< The event's date
	std::string local; ///< The event's local
	std::string theme; ///< The event's theme
	int phase; ///< The event's phase
	Association * association; ///< The connection to the Association

};

#endif /* EVENT_H_ */
