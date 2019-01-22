#include <iostream>


#include "Point.h"
#include "Line.h"
#include "PLContainer.h"

using std::cout;
using std::endl;


int main() {

	// Points and lines creation
	Point parray[] = {{2,2},{3,3},{4,4},{-1,-6.5},{5,3}};
	for (int i=0;i < 5;++i){
		cout<<"Point "<<i+1<<": "<<parray[i]<<endl;	
	}
	Line line{&parray[0],&parray[1]};
	cout<<"A line: "<<line<<endl;

	// Checking incidence
	if(line.isIncident(parray[2]))
		cout<<parray[2]<<" lies on "<<line<<endl;
	else
		cout<<parray[2]<<" does not lie on "<<line<<endl;

	if(line.isIncident(parray[3]))
		cout<<parray[3]<<" lies on "<<line<<endl;
	else
		cout<<parray[3]<<" does not lie on "<<line<<endl;

	
	// Checking line equivalence
	Line line1{&parray[0],&parray[2]};
	Line line2{&parray[0],&parray[4]};
	if(line==line1)
		cout<<line1<<" equivalent to "<<line<<endl;
	else
		cout<<line1<<" not equivalent to "<<line<<endl;
	if(line==line2)
		cout<<line2<<" equivalent to "<<line<<endl;
	else
		cout<<line2<<" not equivalent to "<<line<<endl;

	// Construction of empty container
	PLContainer plc;

	PLContainer plc_empty1(plc);
	PLContainer plc_empty2;
	if(plc_empty1 == plc_empty2)
		cout<<"Empty containers are equal."<<endl;
	else
		cout<<"Empty containers are NOT equal."<<endl;

	// Adding points
	Point *p = nullptr;
	plc.addPoint(1,2,p);
	plc.addPoint(3,4,p);
	plc.addPoint(5,6,p);
	plc.addPoint(4,2,p);
	plc.addPoint(3,4,p); // repeated point
	plc.addPoint(0.3,0,p); 
	plc.addPoint(0.2+0.1,0,p); // repeated point
	plc.addPoint(0.3,1.7,p); 


	// Adding lines
	Line *lp = nullptr;
	plc.addLine(1,2,3,4,lp);
	plc.addLine(1,2,5,6,lp); // equivalent to previous line
	plc.addLine(1,2,4,2,lp);
	plc.addLine(5,6,4,2,lp);
	plc.addLine(4,2,3,4,lp);
    plc.addLine(0.3,0,0.3,1.7,lp);

	cout<<"Container:"<<endl<<plc;

	// Extracting incident lines
	unsigned int number=0;
	unsigned int capacity=0;
	Line** ilines = plc.incidentLines(4,2,number,capacity);
	cout<<"Lines incident with (4,2): "<<endl;
	for(int i=0; i< number;++i)
		cout<<*ilines[i]<<endl;

	// Deleting points
	plc.deletePoint(4,2);
	cout<<"Deleted point (4,2). Result: "<<endl<<plc;

	// Get line
	Line* l;
	plc.getLine(1,2,5,6,l);
	if(l==nullptr)
		cout<<"Line (1,2,5,6) not found "<<endl;
	else
		cout<<"Get line (1,2,5,6) returned "<<*l<<endl;

	// Deleting lines
	plc.deleteLine(1,2,5,6);
	cout<<"Deleted line ((1,2),(5.6)). Result: "<<endl<<plc;

	l= nullptr;
	plc.getLine(1,2,3,4,l);
	if(l==nullptr)
		cout<<"Line (1,2,3,4) not found "<<endl;
	else
		cout<<"Get line (1,2,3,4) returned "<<*l<<endl;

	if(ilines!=nullptr)
		delete [] ilines;
	ilines=nullptr;

  	PLContainer plc1 = plc;

  	cout<<"Container copy:"<<endl<<plc1;

  	if(plc1==plc)
    	cout<<"is equal to old container."<<endl;
  	else
  		cout<<"is not qual to old container."<<endl;

		std::cout << "Before deleting line from plc1, plc is " << plc << std::endl;
		std::cout << "before deleting line from plc1, plc1 is " << plc1 << std::endl;


  	plc1.deleteLine(0.3,0,0.3,1.7);

		std::cout << "After deleting line from plc1, plc is " << plc << std::endl;
		std::cout << "After deleting line from plc1, plc1 is " << plc1 << std::endl;

	if(plc1==plc)
    	cout<<"Deleted a line, still equal to old container."<<endl;
 	else
  		cout<<"Deleted a line, not qual to old container."<<endl;

	
	plc1=plc;
	if(plc1==plc)
    	cout<<"After assignment, equal to old container again."<<endl;
 	else
  		cout<<"After assignment, still not qual to old container."<<endl;

	std::cout << "After ass, plc is " << plc << std::endl;
	std::cout << "After ass, plc1 is " << plc1 << std::endl;

	return 0;
}