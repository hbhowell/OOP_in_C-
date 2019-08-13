// OOP in C++ Harry Howell 05/2019
// implementation source file for inductor class

#include"inductor.h"

// Constructors ******************************

// default constructor
inductor::inductor(){ 
	inductance.first = 0; inductance.second = 's'; type = "Inductor"; angFreq = 0; 
};

// parameterised constructor with base class pointer
inductor::inductor(double ind, string c, double fr){
	type = "Inductor";
	angFreq = fr;
	inductance.first = ind*(pow(10,-3));
	inductance.second = c;
}

// copy constructor
inductor::inductor(const inductor& ind){
	this->type = "Inductor";
	this->angFreq = ind.angFreq;
	// copy inductance and configuration type
	inductance = ind.inductance;
}

// move constructor
inductor::inductor(inductor&& ind){
	inductance = ind.inductance;
	ind.angFreq = 0;
	ind.type.clear();
	ind.inductance.first = 0;
	ind.inductance.second = '\0';
}

// copy assignment
inductor & inductor::operator=(const inductor& ind){
	// no self assignment
	if (&ind == this) return *this; 
	// copy pair from ind to this
	inductance = ind.inductance;
	return *this;
}

// move assignment
inductor &inductor::operator=(inductor&& ind){
	swap(inductance,ind.inductance);
	swap(angFreq, ind.angFreq);
	ind.angFreq = 0;
	ind.type.clear();
	ind.inductance.first = 0;
	ind.inductance.second = "\0";
	return *this;
}

// functions **********************************

// display info about inductor
void inductor::info(){
	cout << "Type: " << type << "\nConfiguration: " << getConfig() << "\nInductance: " << inductance.first <<
		" H\nPhase shift: " << getPhaseDiff() << " rad" << endl;
}

// set signal frequency through component
void inductor::setFreq(const double &freq){
	angFreq = 2 * pi*freq;
};

// return component configuration (Series/Parallel)
string inductor::getConfig(){
	if (inductance.second == "s") return "Series";
	else if (inductance.second == "p") return "Parallel";
	else return "\0";
}

// return complex Impedance of component
complex<double> inductor::getImpedance(){
	complex<double> impedance;
	impedance.real( 0 );
	impedance.imag( angFreq*inductance.first);
	return impedance;
}

// return magnitude of impedance
double inductor::getAbsImpedance(){
	return abs(this->getImpedance());
}

// return phase difference of component
double inductor::getPhaseDiff(){
	double phase = atan(this->getImpedance().imag() / this->getImpedance().real());
	return phase;
}



