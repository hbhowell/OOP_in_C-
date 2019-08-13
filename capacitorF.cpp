// OOP in C++ Harry Howell 05/2019
// implementation source file for capacitor class

#include"capacitor.h"

// default constructor
capacitor::capacitor(){ 
	capacitance.first = 0; capacitance.second = "s"; this->type = "Capacitor"; this->angFreq = 0; 
};

// parameterised constructor #1 with base class pointer
capacitor::capacitor(double cap, string c, double fr){
	this->type = "Capacitor";
	this->angFreq = 2 * pi*fr;
	capacitance.first = cap*(pow(10,-9));
	capacitance.second = c;
}

// copy constructor
capacitor::capacitor(const capacitor& cap){
	this->type = "Capacitor";
	this->angFreq = cap.angFreq;
	capacitance = cap.capacitance;
}

// move constructor
capacitor::capacitor(capacitor&& cap){
	capacitance = cap.capacitance;
	cap.angFreq = 0;
	cap.type.clear();
	cap.capacitance.first = 0;
	cap.capacitance.second = '\0';
}

// copy assignment
capacitor & capacitor::operator=(const capacitor& cap){
	if (&cap == this) return *this;
	capacitance = cap.capacitance;
	return *this;
}

// move assignment
capacitor &capacitor::operator=(capacitor&& cap){
	swap(capacitance, cap.capacitance);
	swap(angFreq, cap.angFreq);
	cap.angFreq = 0;
	cap.type.clear();
	cap.capacitance.first = 0;
	cap.capacitance.second = "\0";
	return *this;
}

// functions **********************************

// display info about capacitor
void capacitor::info(){
	cout << "Type: " << type << "\nConfiguration: " << getConfig() << "\nCapacitance: " << capacitance.first <<
		" F\nPhase shift: " << this->getPhaseDiff() << " rad" << endl;
}

// set signal frequency through component
void capacitor::setFreq(const double &freq){
	angFreq = 2 * pi*freq;
};

// return component configuration (Series/Parallel)
string capacitor::getConfig(){
	if (capacitance.second == "s") return "Series";
	else if (capacitance.second == "p") return "Parallel";
	else return "\0";
}

// return complex Impedance of component
complex<double> capacitor::getImpedance(){
	complex<double> impedance;
	impedance.real( 0 );
	if (angFreq != 0){
		impedance.imag(-pow(angFreq*capacitance.first, -1));
	}
	else{
		impedance.imag( 0 );
	}
	return impedance;
}

// return magnitude of impedance
double capacitor::getAbsImpedance(){
	return abs(this->getImpedance());
}

// return phase difference of component
double capacitor::getPhaseDiff(){
	double phase = atan(this->getImpedance().imag() / this->getImpedance().real());
	if (phase != phase){ // return 0 for case phase = -1.#IND (i.e. when atan(0/0) which is undefined)
		return 0;
	}
	else{
		return phase;
	}
}

