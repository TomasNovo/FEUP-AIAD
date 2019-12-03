/*
 * SubArea.h
 *
 */

#ifndef SUBAREA_H_
#define SUBAREA_H_

#include <string>

//!  The SubArea Class
/*!
 * An Association consists in a group of associates. Each associate has interest in a variety of areas.
 * Each area has some subareas.
 * A SubArea is distinguished by either its name or initials
 */
class SubArea{
public:

	//Constructors
	/**
	 * @brief Default SubArea Constructor
	 */
	SubArea();

	/**
	 * @brief Full SubArea Constructor
	 *
	 * @param name - The name of the SubArea
	 * @param initials - The initials of the SubArea
	 */
	SubArea(std::string name, std::string initials);

	//Destructors
	/**
	 * @brief Default SubArea Destructor
	 */
	virtual ~SubArea();

	//Get Methods

	/**
	 * @brief Returns the name of the SubArea
	 *
	 */
	std::string getName() const;

	/**
	 * @brief Returns the initials of the SubArea
	 *
	 */
	std::string getInitials() const;

private:
	std::string name; ///< The SubArea's name
	std::string initials; ///< The SubArea's initials
};

#endif /* SUBAREA_H_ */
