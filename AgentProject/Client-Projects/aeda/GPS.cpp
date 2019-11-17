#include "GPS.h"
#include <cmath>


#define pi atan(1)*4

using namespace std;

/**
 * @brief      Constructs the object.
 */
GPS::GPS(){
	
}

/**
 * @brief      Constructs the object.
 *
 * @param[in]  latitude   The latitude
 * @param[in]  longitude  The longitude
 */
GPS::GPS(double latitude, double longitude): latitude(latitude), longitude(longitude)
{	
	if (latitude > 90 || latitude < -90 || longitude > 180 || longitude < -180)
		throw WrongCoordinates(*this);
}

/**
 * @brief      Converts degrees to radians
 *
 * @param      input  Input in degrees
 *
 * @return     input in radians
 */
double GPS::degreesToRadians(const double & input) const {

	return (input*pi/180);
}
/**
 * @brief      Calculates de distance between two GPS coordiantes
 *
 * @param      gps2  The second set of GPS coordinates
 *
 * @return     Distance between *this and gps2
 */
double GPS::distance(GPS gps2) {

	double lat1 = degreesToRadians(latitude);
	double lon1 = degreesToRadians(longitude);

	double lat2 = degreesToRadians(gps2.getLatitude());
	double lon2 = degreesToRadians(gps2.getLongitude());

	double a = sin((lat2 - lat1)/2)*sin((lat2 - lat1)/2) + cos(lat1)*cos(lat2)*sin((lon2-lon1)/2)*sin((lon2-lon1)/2);
	double c = 2*atan2(sqrt(a), sqrt(1-a));

	return c*6371000;
}


/**
 * @brief      Gets the latitude.
 *
 * @return     The latitude.
 */
double GPS::getLatitude() const {
	return latitude;
}
/**
 * @brief      Gets the longitude.
 *
 * @return     The longitude.
 */
double GPS::getLongitude() const {
	return longitude;
}


/**
 * @brief      Returns if two GPS coordinates are equal to one another
 *
 * @param[in]  gps2  gps 2
 *
 * @return     *this == gps2
 */
bool GPS::operator==(const GPS & gps2) const {

	return ((this->latitude == gps2.getLatitude() ) && (this->longitude == gps2.getLongitude()));
}

/**
 * @brief      Streams a GPS type variable
 *
 * @param      os     output stream
 * @param[in]  input  input GPS
 *
 * @return     os with GPS streamed to it
 */
ostream & operator<< (ostream & os,const GPS & input) {

	return (os << input.getLatitude() << " , " << input.getLongitude());
}
