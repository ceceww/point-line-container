
#include <iostream>
#include <string>

#include "PointTester.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;


int main(int argc, char* argv[]) {


	while (argc > 1) {
		switch (argv[--argc][0]) {			
		case 'a':
		{
			PointTester t;
			t.testDefCtor();
		}
		break;
		case 'b':
		{
			PointTester t;
			t.testValueCtor();
		}
		break;
		case 'c':
		{
			PointTester t;
			t.testCopyCtor();
		}
		break;
		case 'd':
		{
			PointTester t;
			t.testGet();
		}
		break;
		case 'e':
		{
			PointTester t;
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

