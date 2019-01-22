/*
 * TesterBase.cpp
 *
 *  Created on: 31 Oct 2015
 *      Author: np183
 *
 *  Extended by rd307 
 */

#include <stdlib.h>
#include <iostream>
#include <utility>

#include "TesterBase.h"


using std::cout;
using std::cerr;
using std::endl;
using std::string;

TesterBase::TesterBase() : error_(false), funcname_("") {
	unsigned int val(time(0)*rand());
	srand(val);
}

TesterBase::~TesterBase() {
}

void TesterBase::errorOut_(const string& errMsg, unsigned int errBit) {
        cerr << funcname_ << " " << "(fail";
        if (errBit)
                cerr << errBit;
        cerr << "): " << errMsg << endl;
        error_|=(1<<errBit);
}

void TesterBase::passOut_(const string& passMsg) {
        if (!error_) {
                cerr << funcname_ << " " << "(pass): " << passMsg << endl;
        }
}

double TesterBase::randomDouble_(unsigned int max){
	
	double v = 0;
	if(max==0)
		v = rand() % MAX_COORDINATE + rand() / (static_cast<double>(RAND_MAX) + 1.0);
	else
		v = rand() % max + rand() / (static_cast<double>(RAND_MAX) + 1.0);
	
	bool sign(rand() % 2);

	if(sign)
		v *=-1;

	return v;
}