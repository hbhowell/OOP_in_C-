// OOP in C++ Harry Howell 05/2019
// header file declaring circuit class and user input verify functions
// properties of circuit:
// stores  - a list of all the components within the circuit
// - the source driving frequency and number of different components
// - the overall impedance and phase difference of the circuit

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<list>
#include<utility>
#include<vector>
#include<complex>
#include"components.h"
#include<iostream>
#include<string>
#include<cmath>

using namespace std;

class circuit{
protected:
	const double pi{ 3.14159265358979 };
	complex<double> imped;
	double angFreq;
	int serRes, parRes, serCap, parCap, serInd, parInd; // stores number of components added in series or parallel
	list<component*> listOfComp; // list of components in circuit
public:
	// defualt constructor
	circuit();
	// parameterised constructor #1 with base class pointer
	circuit(component* comp, double fr);

	// destructor
	~circuit();

	// function declarations
	void addComp(component* comp); // add a component either in series or parallel (str = "s" or "p")
	void addCompList(vector<string> &compList, vector<double> &valList, vector<string> &configList); // add component list
	void addCircuit(circuit &circ, string &str); // nest another circuit either in series or in parallel
	void setFreq(double &fr);
	void info();
	void graphic();


	// access functions
	complex<double> getImpedance(); // return impedance of total circuit
	double getAbsImpedance();
	double getPhaseLag(); // calculate and return the total phase shift of the voltage from the current
	double getFreq();
	int size();

};

// function to verify user input for component double value
double cinVerify(double &val);

// multiple component value input version
vector<double> cinVerify(string &val, vector<double> &valList, double val1Length);

// overload for strings and chars (single input)
template <class T> T cinVerify(T &val, vector<T> &array){ //second argument to be vector of strings/chars which are valid for user input
	// check input is valid
	while (cin.fail() || find(array.begin(), array.end(), val) == array.end()){
		cerr << "Error: make sure input is from the options stated.\nInput value: ";
		// clear fail bit and ignore input
		cin.clear(); cin.ignore(100,'\n'); cin >> val;
	}
	return val;
}

// multiple component input version
vector<string> cinVerify(string &val, vector<string> &array, vector<string> &compList);

// function to output vector components
template <class T> void vecOut(vector<T> &vec){
	vector<T>::iterator it;
	cout << "Entered list: {";
	for (it = vec.begin(); it < vec.end(); it++){
		if (it != vec.end() - 1){
			cout << *it << ",";
		}
		else{
			cout << *it << "}" << endl;
		}
	}
}

#endif