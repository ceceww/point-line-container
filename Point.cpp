#include <iostream>
#include <cmath>
#include <cfloat>

#include "Point.h"

using std::ostream;

// Default constructor
Point::Point() {
  x = 0.0;
  y = 0.0;
}

// Constructor that creates a point with co-ordinates (x,y)
Point::Point(double x, double y){
	this->x = x;
	this->y = y;
}

// Copy constructor
// Initialises a newly declared point object from an existing point object
// Shallow copy
Point::Point(const Point& other){ 
	this->x = other.x;
	this->y = other.y;
}
  
// Move constructor
// Same as shallow copy
Point::Point(Point&& other){
	this->x = other.x;
	this->y = other.y;
}

// Assignment operator for copy
// Same as default
Point& Point::operator=(const Point& other){
	this->x = other.x;
	this->y = other.y;
	return *this;
}

// Assignment operator for move
// Same as default
Point& Point::operator=(Point&& other){
	this->x = other.x;
	this->y = other.y;
	return *this;
}
 
// Destructor
// Same as default
Point::~Point(){
}

// Returns the x co-ordinate of this point object
double Point::getX()const{
  return this->x;
}

// Returns the y co-ordinate of this point object
double Point::getY()const{
  return this->y;
}

// Test this point object with another for equality
bool Point::operator==(const Point& other) const{
  bool equal=false;
  // Both x and y must be the same for them to be equal
  if ((approxEqual(x, other.x)) && (approxEqual(y, other.y))) {
	  equal = true;
  }
  return equal; 
}

// Prints the point in the form (x,y)
void Point::print(std::ostream& stream) const{
	stream << "(" << this->x << "," << this->y << ")";
}

// Returns an output stream of the point in the form (x,y)
ostream& operator<<(std::ostream& stream, const Point& point){
	stream << "(" << point.getX() << "," << point.getY() << ")";
	return stream;
}

bool approxEqual(double a,double b){
  
  const double PRECISION=1000000;

  if(a==b)
    return true;

  double difference = fabs(a - b);
  if (difference <= DBL_EPSILON) 
    return true;

  a = fabs(a);
  b = fabs(b);
  double scaledEpsilon = DBL_EPSILON * PRECISION;
  scaledEpsilon = a > b ? a * scaledEpsilon  : b * scaledEpsilon;
  
  return difference <= scaledEpsilon;

}