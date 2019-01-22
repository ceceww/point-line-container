#ifndef PLCONTAINERTESTER_H_
#define PLCONTAINERTESTER_H_

#include <string>
#include <vector>

#include "TesterBase.h"

class PLContainerTester : public TesterBase {
public:
	PLContainerTester();
	~PLContainerTester();

	void testDefCtor();
	void testAddPoint();
	void testNumberOfPoints();
	void testAddLine();
	void testEquals();
		
	
private:

	void createPoints_(std::vector<std::vector<double> >& points);
	void createLines_(const std::vector<std::vector<double> >& points, 
		              std::vector<std::vector<double> >& lines, unsigned int numLines);

	static const unsigned int SMALL_ARRAY = 100;
};

#endif /* PLCONTAINERTESTER_H_ */
