#include <stdlib.h>
#include <iostream>
#include <utility>

#include "LineTester.h"

#include "Line.h"

LineTester::LineTester() : TesterBase() {
}

LineTester::~LineTester() {
}

void LineTester::testDefCtor() {
	funcname_ = "testDefCtor";

	Line line;
	if (line.getPoint1()!=nullptr || line.getPoint2()!=nullptr) {
		errorOut_("Points are not null.",1);
	}

	passOut_("Tested the default constructor.");
}

void LineTester::testValueCtor() {
	funcname_ = "testValueCtor";

	double x1 = randomDouble_();
	double y1 = randomDouble_();
	Point point1(x1,y1);

	double x2 = randomDouble_();
	double y2 = randomDouble_();
	Point point2(x2,y2);

	Line line(&point1,&point2);

	if (!(&point1==line.getPoint1() && &point2==line.getPoint2()) &&
		!(&point2==line.getPoint1() && &point1==line.getPoint2())) {
		errorOut_("Point pointers are not set correctly.",1);
	}

	passOut_("Tested the value constructor.");
}


void LineTester::testCopyCtor() {
	funcname_ = "testCopyCtor";
	
	double x1 = randomDouble_();
	double y1 = randomDouble_();
	Point point1(x1,y1);

	double x2 = randomDouble_();
	double y2 = randomDouble_();
	Point point2(x2,y2);

	Line line(&point1,&point2);

	Line copy(line);

	if (copy.getPoint1()== nullptr || copy.getPoint2()==nullptr){
		errorOut_("Null pointer in copy.",1);
	}
	if (!(copy.getPoint1()==line.getPoint1() && copy.getPoint2()==line.getPoint2()) &&
		!(copy.getPoint2()==line.getPoint1() && copy.getPoint1()==line.getPoint2())){
		errorOut_("Different values in copy.",2);
	}
	
	passOut_("Tested the copy constructor.");
}

void LineTester::testEquals() {
	funcname_ = "testEquals";
	
	double x1 = randomDouble_();
	double y1 = randomDouble_();

	double x2 = randomDouble_();
	while(approxEqual(x2,x1)){
		x2 = randomDouble_();		
	}
	double y2 = randomDouble_();
	while(approxEqual(y2,y1)){
		y2 = randomDouble_();		
	}	

	Point point1(x1,y1);
	Point point2(x2,y2);

	// line1 and line2 have the same Point pointers
	Line line1(&point1,&point2);
	Line line2(&point1,&point2);

	if(!(line1 == line2) || !(line2 == line1)){
		errorOut_("Equal lines determined different.",1);
	}	


	double x1inc = randomDouble_();
	while(approxEqual(x1inc,x1)){
		x1inc = randomDouble_();
	}
	double y1inc = y1+ ((y2 - y1) * (x1inc - x1))/(x2 - x1);

	double x2inc = randomDouble_();
	while(approxEqual(x2inc,x2)){
		x2inc = randomDouble_();
	}
	double y2inc = y1+ ((y2 - y1) * (x2inc - x1))/(x2 - x1);


	Point point1inc(x1inc,y1inc);
	Point point2inc(x2inc,y2inc);

	Line line3(&point1inc,&point2inc);

	//line1 and line3 are equivalent 
	if(!(line1 == line3)){
		errorOut_("Equal lines determined different.",2);
	}	

	passOut_("Tested equality operator.");
}

void LineTester::testDtor () {
	funcname_ = "testDtor";
	
	double x1 = randomDouble_();
	double y1 = randomDouble_();
	Point* ppoint1 = new Point(x1,y1);
	Point point1(*ppoint1);
	double x2 = randomDouble_();
	double y2 = randomDouble_();
	Point* ppoint2 = new Point(x2,y2);
	Point point2(*ppoint2);

	Line* line = new Line(ppoint1,ppoint2);
	delete line;

	if(!(*ppoint1 == point1) || !(*ppoint2 == point2)){
		errorOut_("Deleted a Point object.",1);
	}

	delete ppoint1;
	delete ppoint2;

	passOut_("Tested destructor.");	
}

