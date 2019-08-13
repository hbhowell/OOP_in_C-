// OOP in C++ Harry Howell 05/2019
// implementation source file for resistor class

#include"resistor.h"

// default constructor
resistor::resistor(){
	resistance.first = 0; resistance.second = "s"; this->type = "Resistor"; angFreq = 0;
}

// parameterised constructor with base class pointer
resistor::resistor(double res, string c, double fr){
	this->type = "Resistor";
	this->angFreq = 2 * pi*fr;
	resistance.first = res;
	resistance.second = c;
}

// copy constructor
resistor::resistor(const resistor& res){
	resistance = res.resistance;
}

// move constructor
resistor::resistor(resistor&& res){
	resistance = res.resistance;
	res.angFreq = 0;
	res.type.clear();
	res.resistance.first = 0;
	res.resistance.second = '\0';
}

// copy assignment
resistor & resistor::operator=(const resistor& res){
	if (&res == this) return *this;
	resistance = res.resistance;
	return *this;
}

// move assignment
resistor &resistor::operator=(resistor&& res){
	swap(resistance, res.resistance);
	swap(angFreq, res.angFreq);
	res.angFreq = 0;
	res.type.clear();
	res.resistance.first = 0;
	res.resistance.second = "\0";
	return *this;
}

// functions **********************************

// display info about resistor
void resistor::info(){
	cout << "Type: " << type << "\nConfiguration: " << getConfig() << "\nResistance: " << resistance.first <<
		" Ohms\nPhase shift: " << getPhaseDiff() << " rad" << endl;
}

// set signal frequency through component
void resistor::setFreq(const double &freq){
	angFreq = 2*pi*freq;
};

// return component configuration (Series/Parallel)
string resistor::getConfig(){
	if (resistance.second == "s") return "Series";
	else if (resistance.second == "p") return "Parallel";
	else return "\0";
}

// return complex Impedance of component
complex<double> resistor::getImpedance(){
	complex<double> c(resistance.first, 0);
	return c;
}

// return magnitude of impedance
double resistor::getAbsImpedance(){
	return abs(this->getImpedance());
}

// return phase difference of component
double resistor::getPhaseDiff(){
	return 0;
}