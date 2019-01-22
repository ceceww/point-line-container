#include <iostream>

#include "Line.h"

using std::ostream;

// Default constructor
Line::Line(){
	// Both points null
	pp1 = nullptr;
	pp2 = nullptr;
}

// Constructor that creates a line from two points
Line::Line(Point* p1, Point* p2){
	pp1 = p1;
	pp2 = p2;
}

// Copy constructor
// Initialises a newly declared line object from an existing line object
// Shallow copy
Line::Line(const Line& other){
	pp1 = other.pp1;
	pp2 = other.pp2;	
}
  
// Move constructor
// Resources are moved from other line object to this one
Line::Line(Line&& other){
	pp1 = other.pp1;
	other.pp1 = nullptr;
	pp2 = other.pp2;
	other.pp2 = nullptr;
}

// Assignment operator (copy)
// Shallow copy 
Line& Line::operator=(const Line& other){
	pp1 = other.pp1;
	pp2 = other.pp2;
	return *this;
}

// Assigment operator (move)
Line& Line::operator=(Line&& other){
	pp1 = other.pp1;
	other.pp1 = nullptr;
	pp2 = other.pp2;
	other.pp2 = nullptr;
	return *this;
}
 
// Destructor
// Default behaviour
Line::~Line(){
}

// For a point to be incident on line, the following eq must be satisfied:
// (y-y1)(x2-x1)=(x-x1)(y2-y1)
bool Line::isIncident(const Point& point)const{
	bool isIncident=false;
	// Get co-ordinates of the point
	double x = point.getX();
	double y = point.getY();
	// Get co-ordinates of the points of this line
	const Point* p1 = this->getPoint1();
	const Point* p2 = this->getPoint2();
	// Break down the points into their component x and y values
	double x1, x2, y1, y2;
	x1 = p1->getX();
	x2 = p2->getX();
	y1 = p1->getY();
	y2 = p2->getY();
	// Break down equation into each subtraction and result
	double sub1, sub2, sub3, sub4, res1, res2;
	sub1 = y - y1;
	sub2 = x2 - x1;
	sub3 = x - x1;
	sub4 = y2 - y1;
	// Multiply subs for either side of equation
	res1 = sub1 * sub2;
	res2 = sub3 * sub4;
	// They must be equal for point to be incident on line
	if (res1 == res2) {
		isIncident = true;
	}
	// Finished using p1 and p2
	p1 = nullptr;
	p2 = nullptr;
	return isIncident;
}

// Equality operator
bool Line::operator==(const Line& other) const{
	// Initialise function pointers and variables
	const Point* p1 = nullptr;
	const Point* p2 = nullptr;
	const Point* other_p1 = nullptr;
	const Point* other_p2 = nullptr;
	bool equal = false;
	// Point p1 and p2 to the points of this line
	p1 = this->getPoint1();
	p2 = this->getPoint2();
	// Point other_p1 and other_p2 to the points of the other line
	other_p1 = other.getPoint1();
	other_p2 = other.getPoint2();
	// If all points lie on the same line then they're equal
	if (this->isIncident(*p1) && this->isIncident(*p2) && this->isIncident(*other_p1) && this->isIncident(*other_p2)){
		equal = true;
	}
	// Finished using so point to nullptr
	p1 = nullptr;
	p2 = nullptr;
	other_p1 = nullptr;
	other_p2 = nullptr;
	return equal;
}

const Point* Line::getPoint1()const{
	return pp1;
}

const Point* Line::getPoint2()const{
	return pp2;
}

// Print this line in the form ((x1,y1),(x2,y2))
void Line::print(std::ostream& stream) const{
	stream << "(" << *this->pp1 << "," << *this->pp2 << ")";
}
 
// Print the line specified in the form ((x1,y1),(x2,y2))
ostream& operator<<(std::ostream& stream, const Line& line){
	stream << "(" << *line.getPoint1() << "," << *line.getPoint2() << ")";
	return stream; 
}
