#ifndef __UTILITIES_INCLUDED__
#define __UTILITIES_INCLUDED__

#include <string>

namespace utilities{

	template <class T>


	/**
	 * @brief      Swaps two values.
	 *
	 * @param      a     First value
	 * @param      b     Second value
	 */
	void swap(T& a, T& b);

	/**
	 * @brief      Removes spaces from both the beginning and the end of the string.
	 *
	 * @param      input  The string
	 */
	void trimString(std::string &input);
	
	/**
	 * @brief      Function that gets the number digits of a base 10 number.
	 *
	 * @param[in]  input  The input
	 *
	 * @return     The numbers of digits of input
	 */
	int intSize(int input);
	
	/**
	 * @brief      Determines if a string is a number.
	 *
	 * @param[in]  input  The input string
	 *
	 * @return     True if numeric, False otherwise.
	 */
	bool isNumeric(std::string input);
	
};


#endif