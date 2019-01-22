
#include <iostream>
#include <string>


#include "LineTester.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;


int main(int argc, char* argv[]) {

	while (argc > 1) {
		switch (argv[--argc][0]) {			
		case 'a':
		{
			LineTester t;
			t.testDefCtor();
		}
		break;
		case 'b':
		{
			LineTester t;
			t.testValueCtor();
		}
		break;
		case 'c':
		{
			LineTester t;
			t.testCopyCtor();
		}
		break;
		case 'd':
		{	
			LineTester t;
			t.testEquals();
		}
		break;
		case 'e':
		{
			LineTester t;
			t.testDtor();
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

