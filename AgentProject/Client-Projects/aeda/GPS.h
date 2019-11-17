#ifndef GPS_H
#define GPS_H

#include <iostream>
#include <exception>


/**
 * @brief      Class for working with GPS coordinates
 */
class GPS {

	double latitude;
	double longitude;
public:

	/**
	 * @brief      Contructor
	 */
	GPS();

	/**
	 * @brief      Contructor with coordinates input
	 *
	 * @param[in]  latitude   The latitude
	 * @param[in]  longitude  The longitude
	 */
	GPS(double latitude, double longitude);

	/**
	 * @brief      Calculates the distance between two sets of GPS coordinates
	 *
	 * @param[in]  gps2  The second set of GPS coordinates
	 *
	 * @return     The distance between the coordinates
	 */
	double distance(GPS gps2);
	
	/**
	 * @brief      Gets the latitude coordinate of the GPS.
	 *
	 * @return     The latitude.
	 */
	double getLatitude() const;
	
	/**
	 * @brief      Gets the longitude coordinate of the GPS.
	 *
	 * @return     The longitude.
	 */
	double getLongitude() const;
	
	/**
	 * @brief      Converts an angle in degrees to radians
	 *
	 * @param[in]  input  The angle in degrees
	 *
	 * @return     The same angle in radians
	 */
	double degreesToRadians(const double & input) const;
	
	/**
	 * @brief      The equality operator for objects of class GPS
	 *
	 * @param[in]  gps2  The second set of GPS coordinates
	 *
	 * @return     True if they are equal and False otherwise
	 */
	bool operator==(const GPS & gps2) const;
	

};

/**
 * @brief      Defines the << operator for objects of the GPS class to enable the simple print of the object to the standard output
 *
 * @param      os     The output stream
 * @param[in]  input  The GPS object
 *
 * @return     The os stream with the object added
 */
std::ostream& operator <<(std::ostream & os,const GPS & input);


/**
 * @brief      Class for throwing exceptions when the coordinates aren't valid
 */
class WrongCoordinates {
	GPS gps;
public:

	/**
	 * @brief      Contructor
	 *
	 * @param[in]  gps   The GPS
	 */
	WrongCoordinates(GPS gps): gps(gps) {}

	/**
	 * @brief      Gets the GPS from the object.
	 *
	 * @return     The GPS.
	 */
	GPS getGPS() const {return gps;}
	
};


#endif