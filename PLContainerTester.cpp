#include <stdlib.h>
#include <iostream>
#include <utility>


#include "PLContainerTester.h"

#include "PLContainer.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

PLContainerTester::PLContainerTester() : TesterBase()  {

}

PLContainerTester::~PLContainerTester() {
}

void PLContainerTester::testDefCtor() {
	funcname_ = "testDefCtor";

	PLContainer plc;
	if (plc.numberOfPoints() != 0) {
		errorOut_("Number of points set to non zero value.",1);
	}
	if (plc.numberOfLines() != 0) {
		errorOut_("Number of lines set to non zero value.",2);
	}

	passOut_("Tested the default constructor.");
}


void PLContainerTester::testAddPoint() {
	funcname_ = "testAddPoint";
	
	std::vector<std::vector<double> > points;
	createPoints_(points);

	int number = rand() % SMALL_ARRAY +1;

	PLContainer plc;

	// adding new points
	bool fail1=false, fail2=false, fail3=false;
	for(int i=0; i < number; ++i){
		Point* point = nullptr;
		bool flag = plc.addPoint(points[i][0],points[i][1],point);
		if(!flag){
			fail1=true;
		}
		if(point==nullptr){
			fail2=true;
		}
		if(point!=nullptr && !(approxEqual(point->getX(),points[i][0]) && approxEqual(point->getY(),points[i][1]))){
			fail3=true;
		}
	}
	if(fail1)
		errorOut_("Returned false for new point.",1);
	if(fail2)
		errorOut_("Did not update pointer reference for new point.",2);
	if(fail3)
		errorOut_("Wrong value for new point.",3);

	// trying to add repeated points
	bool fail4=false, fail5=false, fail6=false;
	for(int i=0; i < number; ++i){
		Point* point = nullptr;
		bool flag = plc.addPoint(points[i][0],points[i][1],point);
		if(flag){
			fail4=true;
		}
		if(point==nullptr){
			fail5=true;
		}
		if(point!=nullptr && !(approxEqual(point->getX(),points[i][0]) && approxEqual(point->getY(),points[i][1]))){
			fail6=true;

		}
	}
	if(fail4)
		errorOut_("Returned true for existing point.",4);
	if(fail5)
		errorOut_("Did not update pointer reference for existing point.",5);
	if(fail6)
		errorOut_("Wrong value for existing point.",6);

	passOut_("Tested addPoint.");
	
}

void PLContainerTester::testAddLine() {
	funcname_ = "testAddLine";
	
	
	std::vector<std::vector<double> > points;
	createPoints_(points);

	PLContainer plc;
	Line* line = nullptr;

	bool flag = plc.addLine(points[0][0],points[0][1],points[1][0],points[1][1],line);
	if(flag){
		errorOut_("Returned true when adding line to empty container.",1);
	}
	if(line!=nullptr){
		errorOut_("Modified pointer when adding line to empty container.",1);
	}

	int numPoints = rand() % SMALL_ARRAY +1;

	// adding points
	for(int i=0; i < numPoints; ++i){
		Point* point = nullptr;
		plc.addPoint(points[i][0],points[i][1],point);
	}

	unsigned int i1 = rand() % numPoints;
	unsigned int i2 = rand() % numPoints;

	while(i1 == i2){
		i2 = rand() % numPoints;
	}

	flag = plc.addLine(points[i1][0],points[i1][1],points[i2][0],points[i2][1],line);

	if(!flag){
		errorOut_("Returned false for new line.",1);
	}
	if(line==nullptr){
		errorOut_("Did not update pointer reference for new line.",2);
	}

	Line* line_repeated = nullptr;
	flag = plc.addLine(points[i1][0],points[i1][1],points[i2][0],points[i2][1],line_repeated);

	if(flag){
		errorOut_("Returned true for existing line.",3);
	}
	if(line_repeated==nullptr){
		errorOut_("Did not update pointer reference for existing line.",4);
	}
	if(line_repeated!=nullptr && line!=nullptr && line_repeated!=line){
		errorOut_("Wrong pointer for existing line.",5);
	}

	//swap order of points
	line_repeated =nullptr;
	flag = plc.addLine(points[i2][0],points[i2][1],points[i1][0],points[i1][1],line_repeated);

	if(flag){
		errorOut_("Returned true for existing line.",6);
	}
	if(line_repeated==nullptr){
		errorOut_("Did not update pointer reference for existing line.",7);
	}
	if(line_repeated!=nullptr && line!=nullptr && line_repeated!=line){
		errorOut_("Wrong pointer for existing line.",8);
	}

	passOut_("Tested addLine.");
}

void PLContainerTester::testNumberOfPoints() {
	funcname_ = "testNumberOfPoints";

	std::vector<std::vector<double> > points;
	createPoints_(points);

	int number = rand() % SMALL_ARRAY +1;

	PLContainer plc;

	// adding new points
	for(int i=0; i < number; ++i){
		Point* point = nullptr;
		plc.addPoint(points[i][0],points[i][1],point);
		if(plc.numberOfPoints() != i+1){
			errorOut_("Wrong number of points.",1);
			break;
		}
	}

	passOut_("Tested numberOfPoints.");
}

void PLContainerTester::testEquals() {
	funcname_ = "testEquals";
	
	const unsigned int NUM_SETS = 2;

	std::vector<std::vector<double> > points [NUM_SETS];
	createPoints_(points[0]);
	unsigned int n0 =points[0].size();
	points[1] = std::vector<std::vector<double> >(points[0].begin(),points[0].begin()+(n0/2));
	unsigned int n1 =points[1].size();
	// points[1] strict subset of points[0] 

	std::vector<std::vector<double> > lines [NUM_SETS];
	createLines_(points[1],lines[0],rand() % n0 + n0);
	lines[1] = std::vector<std::vector<double> >();
	// lines[0] is non-empty, lines[1] is empty
	PLContainer plc [NUM_SETS][NUM_SETS];

	Point* point = nullptr;
	Line* line = nullptr;
	for (int ci = 0; ci < NUM_SETS; ci++){
		for (int cj = 0; cj < NUM_SETS; cj++){
			for(int i=0; i < points[ci].size(); ++i){
				plc[ci][cj].addPoint(points[ci][i][0],points[ci][i][1],point);
				point = nullptr;
			}
			for(int i=0; i < lines[cj].size(); ++i){
				plc[ci][cj].addLine(lines[cj][i][0],lines[cj][i][1],lines[cj][i][2],lines[cj][i][3],line);
				line = nullptr;
			}
		}
	}

	PLContainer plc1;
	if(plc1 == plc[0][0] || plc[0][0] == plc1)
		errorOut_("Empty and non-empty containers determined equal.",1);

	for(int i=0; i < points[0].size(); ++i){
		plc1.addPoint(points[0][i][0],points[0][i][1],point);
		point = nullptr;
	}
	for(int i=0; i < lines[0].size(); ++i){
		plc1.addLine(lines[0][i][0],lines[0][i][1],lines[0][i][2],lines[0][i][3],line);
		line=nullptr;
	}
	if(!(plc1 == plc[0][0]) || !(plc[0][0] ==plc1))
		errorOut_("Equal containers determined different.",3);

	
	for (int ci = 0; ci < NUM_SETS; ci++){
		for (int cj = 0; cj < NUM_SETS; cj++){
			for (int di = 0; di < NUM_SETS; di++){
				for (int dj = 0; dj < NUM_SETS; dj++){
					if(di==ci && dj==cj)
						continue;
					if(plc[ci][cj] == plc[di][dj]){
						errorOut_("Different containers determined equal.",4);
						cout<<ci<<" "<<cj<<" "<<di<<" "<<dj<<endl; 
						break;
					}
				}
			}
		}
	}
	

	passOut_("Tested equality operator.");
}

// creates a vector of size SMALL_ARRAY containing distinct pairs of coordinates
void PLContainerTester::createPoints_(std::vector<std::vector<double> >& points){
	
	unsigned int size = SMALL_ARRAY;

	points = std::vector<std::vector<double> >(size);

  	for (int i=0 ; i < size ; ++i) {
		std::vector<double> coordinates(2);
		bool new_point = false;
		while(!new_point){
			coordinates[0] = randomDouble_();
			coordinates[1] = randomDouble_();
			bool exists = false;
			for(int j=0;j< i;++j){
				if(approxEqual(points[j][0],coordinates[0]) && approxEqual(points[j][1],coordinates[1])){
					exists=true;
					break;
				}
			}
			if(!exists)
				new_point=true;
		}
		points[i] = coordinates;
     }
 }

// creates a vector of a given size of (not necessarily distinct) tuples of coordinates for lines
void PLContainerTester::createLines_(const std::vector<std::vector<double> >& points, std::vector<std::vector<double> >& lines, unsigned int numLines){
	
	unsigned int numPoints = points.size();

	lines = std::vector<std::vector<double> >(numLines);

	unsigned int i1 = 0, i2 = 0;
  	for (int i=0 ; i < numLines ; ++i) {
  		i1 = rand() % numPoints;
		i2 = rand() % numPoints;

		while(i1 == i2){
			i2 = rand() % numPoints;
		}

		std::vector<double> coordinates(4);
		coordinates[0] = points[i1][0];
		coordinates[1] = points[i1][1];
		coordinates[2] = points[i2][0];
		coordinates[3] = points[i2][1];
		
		lines[i] = coordinates;
    }
 }
