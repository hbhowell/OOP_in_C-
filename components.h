// OOP in C++ Harry Howell 05/2019
// header file for the abstract components class
// get impedence, get magnitude of impedance and get phase difference

#ifndef COMPONENTS_H
#define COMPONENTS_H

// include libraries
#include<list>
#include<utility>
#include<vector>
#include<complex>
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>

using namespace std;

class component
{
protected:
	const double pi{ 3.14159265358979 };
	string type;
public:
	// destructor
	virtual ~component(){};

	// funtion declarations
	virtual void info() = 0; // pure virtual function to return information about the component
	virtual string getConfig() = 0; // return whether component is in series or parallel
	virtual complex<double> getImpedance() = 0; // calculate impedance for particular component
	virtual double getAbsImpedance() = 0; // calculate the magnitude of the impedance
	virtual double getPhaseDiff() = 0; // return the Phase lag between Voltage and current due to the component
	virtual void setFreq(const double &freq) = 0; // function to set the electrical signal frequency passing through the component

	// access functions
	virtual string getType() = 0;
	virtual double getFreq() = 0;

};

#endif
