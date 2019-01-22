#include <stdlib.h>
#include <iostream>
#include <utility>

#include "PointTester.h"

#include "Point.h"


PointTester::PointTester() : TesterBase() {
}

PointTester::~PointTester() {
}

void PointTester::testDefCtor() {
	funcname_ = "testDefCtor";

	Point point;
	if (!approxEqual(point.getX(),0) || !approxEqual(point.getY(),0)) {
		errorOut_("Coordinates are not (0,0).",1);
	}

	passOut_("Tested the default constructor.");
}

void PointTester::testValueCtor() {
	funcname_ = "testValueCtor";

	double x = randomDouble_();
	double y = randomDouble_();
	Point point(x,y);

	if (!approxEqual(x,point.getX()) || !approxEqual(y,point.getY())) {
		errorOut_("Coordinates are not set correctly.",1);
	}

	passOut_("Tested the value constructor.");
}


void PointTester::testCopyCtor() {
	funcname_ = "testCopyCtor";
	
	Point p;
	Point pcopy(p);

	if (!approxEqual(pcopy.getX(),0) || !approxEqual(pcopy.getY(),0)) {
		errorOut_("Different values in copy.",1);
	}

	double x = randomDouble_();
	double y = randomDouble_();
	Point p1(x,y);
	Point p2(p1);

	if (!approxEqual(p1.getX(),p2.getX()) || !approxEqual(p1.getY(),p2.getY())) {
		errorOut_("Different values in copy.",2);
	}
	
	passOut_("Tested the copy constructor.");
}

void PointTester::testGet() {
	funcname_ = "testGet";
	
	double x = randomDouble_();;
	double y = randomDouble_();;
	Point point(x,y);

	if (!approxEqual(point.getX(),x)) {
		errorOut_("GetX returned wrong value.",1);
	}
	if (!approxEqual(point.getX(),x) || !approxEqual(point.getY(),y)) {
		errorOut_("GetY returned wrong value.",2);
	}

	passOut_("Tested getX and getY.");
}

void PointTester::testEquals() {
	funcname_ = "testEquals";
	
	double x = randomDouble_();;
	double y = randomDouble_();;
	Point point(x,y);
	Point pointeq(x,y);
	if(!(point == pointeq) || !(pointeq == point)){
		errorOut_("Equal points determined different.",1);
	}	

	double x1 = randomDouble_();
	while(approxEqual(x1,x))
		x1 = randomDouble_();

	double y1 = randomDouble_();;
	while(approxEqual(y1,y))
		y1 = randomDouble_();

	Point point1(x1,y1);
	Point point2(x1,y);
	Point point3(x,y1);

	if(point == point1 || point1 == point ||
	   point == point2 || point2 == point ||
	   point == point3 || point3 == point){
		errorOut_("Different points determined equal.",2);
	}	

	passOut_("Tested the equality operator.");
}


