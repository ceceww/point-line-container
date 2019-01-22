#ifndef LINETESTER_H_
#define LINETESTER_H_

#include "TesterBase.h"

class LineTester : public TesterBase {
public:
	LineTester();
	~LineTester();

	void testDefCtor();
	void testValueCtor();
	void testCopyCtor();
	void testEquals();
	void testDtor();
		
};

#endif /* LINETESTER_H_ */
