// OOP in C++ Harry Howell 05/2019

#ifndef CAPACITOR_H
#define CAPACITOR_H

#include<list>
#include<utility>
#include<complex>
#include<iostream>
#include<cmath>
#include"components.h"

class capacitor : public component{
protected:
	pair<double,string> capacitance;
	double angFreq;
public:
	// default constructor
	capacitor();
	// parameterised constructor #1 ('cap' being the capacitance magnitude)
	capacitor(double cap, string c, double fr);
	// destructor
	~capacitor(){};
	// copy constructor
	capacitor(const capacitor& cap);
	// move constructor
	capacitor(capacitor&& cap);
	// copy assignment
	capacitor& operator=(const capacitor& cap);
	// move assignment
	capacitor& operator=(capacitor&& cap);
	
	// function declarations
	void info();
	string getConfig();
	complex<double> getImpedance();
	double getAbsImpedance();
	double getPhaseDiff();
	void setFreq(const double &freq);

	// access functions
	double getCapacitance(){ return capacitance.first; };
	string getType(){ return type; }
	double getFreq(){ return angFreq / (2 * pi); }

};


#endif