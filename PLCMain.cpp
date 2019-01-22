
#include <iostream>
#include <string>

#include "PointTester.h"
#include "LineTester.h"
#include "PLContainerTester.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;


int main(int argc, char* argv[]) {


	while (argc > 1) {
		switch (argv[--argc][0]) {
		case 'a':
		{
			PLContainerTester t;
			t.testDefCtor();
		}
		break;
		case 'b':
		{
			PLContainerTester t;
			t.testAddPoint();
		}
		break;
		case 'c':
		{
			PLContainerTester t;
			t.testNumberOfPoints();
		}
		break;
		case 'd':
		{
			PLContainerTester t;
			t.testAddLine();
		}
		break;
		case 'e':
		{
			PLContainerTester t;
			t.testEquals();
		}
		break;
		default:
		{
			cout<<"Options are a -- e."<<endl;
		}
		break;
       	}				
	}

	return 0;
}

