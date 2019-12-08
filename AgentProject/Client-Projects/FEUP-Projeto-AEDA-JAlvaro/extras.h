#ifndef EXTRAS_H_
#define EXTRAS_H_
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>




                      /////                                          /////
                     /////               EXTRAS . H                 /////
                    /////                                          /////

/**
 * @brief      Turns all the characters of the string in upper case
 *
 * @param[in]  input  The input string
 *
 * @return     A string with all chars in upper case
 */
std::string toUpperCase(std::string input);

// Class: Time

/**
 * @brief      Class for time.
 */
class Time{
public:
	Time();
	Time(const Time &t1);

	/**
	 * @brief      Constructs Time Object
	 *
	 * @param[in]  d     day
	 * @param[in]  m     month
	 * @param[in]  y     year
	 */
	Time(unsigned int min,  unsigned int h, unsigned int d, unsigned int m, unsigned int y);

	/**
	 * @brief      Constructs Time Object
	 *
	 * @param[in]  time  The time in string format
	 */
	Time(std::string time);

	/**
	 * @brief      Gets the minutes.
	 *
	 * @return     The minutes.
	 */
	unsigned int getMinutes();

	/**
	 * @brief      Gets the hours.
	 *
	 * @return     The hours.
	 */
	unsigned int getHours();

	/**
	 * @brief      Gets the day.
	 *
	 * @return     The day.
	 */
	unsigned int getDay();

	/**
	 * @brief      Gets the month.
	 *
	 * @return     The month.
	 */
	unsigned int getMonth();

	/**
	 * @brief      Gets the year.
	 *
	 * @return     The year.
	 */
	unsigned int getYear();

	/**
	 * @brief      prints the time
	 *
	 * @param      os    ostream where the time will be printed
	 */
	void printTime(std::ostream & os);

	/**
	 * @brief      calculates the difference of days between this date and the actual date
	 *
	 * @return     the difference between the real date and the offer date
	 */
	int diferencaDias();

	/**
	 * @brief      Checks if one time is more recent than the other
	 *
	 * @param      t2    The time 2
	 *
	 * @return     if this time is more recent than time 2 return true otherwise
	 *             return false.
	 */
	bool operator<( Time  t2);

	/**
	 * @brief      Checks is two times are equal
	 *
	 * @param[in]  t2    The time 2
	 *
	 * @return     if this time is equal to time 2 returns true, otherwise false
	 */
	bool operator==(Time t2);

protected:
	unsigned int minutes, hours, day, month, year;

};


/**
 * @brief      Class for real time.
 */
class  RealTime: public Time{
public:
	RealTime();

};

/**
 * @brief      Checks if two times are equal
 *
 * @param      t1    The time 1
 * @param      t2    The time 2
 *
 * @return     if both times are equal return true otherwise return false.
 */
bool operator==(Time & t1, Time & t2);


/**
 * @brief      prints the time in a ostream in string format
 *
 * @param      os    The oostream
 * @param      t     The time
 *
 * @return     The ostream where the time will be printed
 */
std::ostream & operator<<(std::ostream & os, Time & t);




/**
 * @brief      Implementation of a template Selection Sort Algorithm
 *
 * @param      arr   The vector
 *
 * @tparam     T     The element of the array
 */
template<class T>
void selectionSort(std::vector<T*>& arr){
	int index;

	for(unsigned int i = 0; i < arr.size();i++){
		index = i;

		for(unsigned int j = i+1; j < arr.size();j++){
			if (toUpperCase(arr[j]->getNome()) < toUpperCase(arr[index]->getNome())){
				index = j;
				std::swap(arr[i], arr[index]);
			}

			
		}
	}
}

/**
 * @brief      implementation of a Binary Search Algorithm
 *
 * @param[in]  v     the vector
 * @param[in]  x     the element
 *
 * @tparam     T     type of the elements of the vector
 *
 * @return     the index of the element if found, otherwise -1
 */
template <class T,class P>
int BinarySearch(const std::vector<T> &v, P x){
	int left = 0, right = v.size() - 1;
	while (left <= right){
		int middle = (left + right) / 2;
		if (v[middle]->getNome() < x){
			left = middle + 1;
		}else if (x < v[middle]->getNome()){
			right = middle - 1;
		}else{
			return middle; // encontrou
		}
	}
	return -1; // nao encontrou
}


/**
 * @brief      Gets the real day.
 *
 * @return     The real day.
 */
int getRealDay();

#endif /* SRC_EXTRAS_H_ */
