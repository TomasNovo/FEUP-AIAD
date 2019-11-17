#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <vector>


/**
 * @brief      Class for managing time dates
 */
class data
{
	unsigned int dia, mes, ano;

public:

	/**
	 * @brief      Contructor of the data object.
	 */
	data();

	/**
	 * @brief      Contructor of the data object with specification of the date.
	 *
	 * @param[in]  dia   The day
	 * @param[in]  mes   The month
	 * @param[in]  ano   The year
	 */
	data(unsigned int dia, unsigned int mes, unsigned int ano);
	
	/**
	 * @brief      Destroys the date object.
	 */
	~data();

	/**
	 * @brief      Gets the day of the date.
	 *
	 * @return     The day.
	 */
	unsigned int getDia() const;
	
	/**
	 * @brief      Gets the month of the date.
	 *
	 * @return     The month.
	 */
	unsigned int getMes() const;
	
	/**
	 * @brief      Gets the year of the date.
	 *
	 * @return     The year.
	 */
	unsigned int getAno() const;
	
	/**
	 * @brief      Gets the date in form of string.
	 *
	 * @return     The date.
	 */
	std::string getInfo() const;

	/**
	 * @brief      Sets the day of the date object.
	 *
	 * @param[in]  dia   The day
	 */
	void setDia(unsigned int dia);
	
	/**
	 * @brief      Sets the month of the date object.
	 *
	 * @param[in]  dia   The month
	 */
	void setMes(unsigned int mes);
	
	/**
	 * @brief      Sets the year of the date object.
	 *
	 * @param[in]  dia   The year
	 */
	void setAno(unsigned int ano);

	/**
	 * @brief      The equality operator for objects of class data
	 *
	 * @param[in]  data1  The second date
	 *
	 * @return     True if they are equal and False otherwise
	 */
	bool operator==(const data& data1) const;
	
	/**
	 * @brief      The less operator for objects of class data
	 *
	 * @param[in]  data1  The second date
	 *
	 * @return     True if the first date is older than the second and false otherwise
	 */
	bool operator<(const data& data1) const;

	

};

/**
 * @brief      Defines the << operator for objects of the data class to enable the simple print of the object to the standard output
 *
 * @param      os     The output stream
 * @param[in]  data1  The data object
 *
 * @return     The os stream with the object added
 */
std::ostream& operator<<(std::ostream& os, const data& data1);




#endif
