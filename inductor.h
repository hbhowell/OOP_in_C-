// OOP in C++ Harry Howell 05/2019

#ifndef INDUCTOR_H
#define INDUCTOR_H

#include<list>
#include<utility>
#include<complex>
#include<iostream>
#include<cmath>
#include"components.h"

class inductor : public component{
protected:
	pair<double,string> inductance;
	double angFreq;
public:
	// default constructor
	inductor();
	// parameterised constructor
	inductor(double ind, string c, double fr);
	// destructor
	~inductor(){};
	// copy constructor
	inductor(const inductor& ind);
	// move constructor
	inductor(inductor&& ind);
	// copy assignment
	inductor& operator=(const inductor& ind);
	// move assignment
	inductor& operator=(inductor&& ind);
	
	// function declarations
	void info();
	string getConfig();
	complex<double> getImpedance();
	double getAbsImpedance();
	double getPhaseDiff();
	void setFreq(const double &freq);

	// access functions
	double getInductance(){ return inductance.first; }
	string getType(){ return type; }
	double getFreq(){ return angFreq / (2 * pi); }

};

#endif