// OOP in C++ Harry Howell 05/2019

#ifndef RESISTOR_H
#define RESISTOR_H

#include<list>
#include<utility>
#include<complex>
#include<iostream>
#include<cmath>
#include"components.h"

class resistor : public component{
protected:
	pair <double,string> resistance;
	double angFreq;
public:
	// default constructor
	resistor();
	// parameterised constructor
	resistor(double res, string c, double fr);
	// destructor
	~resistor(){};
	// copy constructor
	resistor(const resistor& res);
	// move constructor
	resistor(resistor&& res);
	// copy assignment
	resistor& operator=(const resistor& res);
	// move assignment
	resistor& operator=(resistor&& res);

	// function declarations
	void info();
	string getConfig();
	complex<double> getImpedance();
	double getAbsImpedance();
	double getPhaseDiff();
	void setFreq(const double &freq);


	// access functions
	double getResistance(){ return resistance.first; };
	string getType(){ return type; }
	double getFreq(){ return angFreq/(2*pi); }

};

#endif