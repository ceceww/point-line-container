#ifndef POINTTESTER_H_
#define POINTTESTER_H_

#include "TesterBase.h"

class PointTester : public TesterBase {
public:
	PointTester();
	~PointTester();

	void testDefCtor();
	void testValueCtor();
	void testCopyCtor();
	void testGet();
	void testEquals();
	
};

#endif /* POINTTESTER_H_ */
