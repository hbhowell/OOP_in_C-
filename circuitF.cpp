// OOP in C++ Harry Howell 05/2019
// implementation source file for circuit class

#include"circuit.h"
#include"resistor.h"
#include"capacitor.h"
#include"inductor.h"

// default constructor
circuit::circuit() : imped{ 0 }, angFreq{ 0 } {
	serRes = parRes = serCap = parCap = serInd = parInd = 0;
}

// destructor
circuit::~circuit(){
	listOfComp.clear();
}

// parameterised constructor with base class pointer
circuit::circuit(component* comp, double fr){
	this->setFreq(fr);
	this->addComp(comp);
}

// functions **********************************

// add a component either in series or parallel (str = "s" or "p")
void circuit::addComp(component* comp){
	listOfComp.push_back(comp);
	// adjust static data of circuit class
	if (comp->getType() == "Capacitor"){
		if (comp->getConfig() == "Series"){
			serCap++;
			// adjust circuit impedance accordingly
			imped += comp->getImpedance();
		}
		else{
			parCap++;
			imped = pow((pow(comp->getImpedance(),-1) + pow(imped,-1)),-1);
		}
	}
	else if (comp->getType() == "Inductor"){
		if (comp->getConfig() == "Series"){
			serInd++;
			imped += comp->getImpedance();
		}
		else{
			parInd++;
			imped = pow((pow(comp->getImpedance(), -1) + pow(imped, -1)), -1);
		}
	}
	else{
		if (comp->getConfig() == "Series"){
			serRes++;
			imped += comp->getImpedance();
		}
		else{
			parRes++;
			imped = pow((pow(comp->getImpedance(), -1) + pow(imped, -1)), -1);
		}
	}
}

void circuit::addCompList(vector<string> &compList, vector<double> &valList, vector<string> &configList){
	component * cmp;
	for (int i = 0; i < compList.size(); i++){
		if (compList[i] == "r"){
			resistor r(valList[i], configList[i], this->getFreq());
			cmp = &r;
			this->addComp(cmp);
		}
		else if (compList[i] == "c"){
			capacitor c(valList[i], configList[i], this->getFreq());
			cmp = &c;
			this->addComp(cmp);
		}
		else{
			inductor i(valList[i], configList[i], this->getFreq());
			cmp = &i;
			this->addComp(cmp);
		}
	}
}

// display circuit information
void circuit::info(){
	cout << "\nCircuit info:\nTotal Impedance: " << imped << " Ohms\nMagnitude of impedance: " <<
		getAbsImpedance() << " Ohms\nVoltage Phase Lag: " << this->getPhaseLag() << " rad\nNo. of Components: " << this->size() <<  endl;
}

// access functions
// return complex impedance of circuit
complex<double> circuit::getImpedance(){ return imped; };

// return magnitude for impedance of circuit
double circuit::getAbsImpedance(){
	return abs(imped);
}

// return phase lag for entire circuit
double circuit::getPhaseLag(){
	double phase = atan(imped.imag()/imped.real());
	return phase;
}

// return number of components in circuit
int circuit::size(){ return listOfComp.size(); }

// set circuit frequency in Hz
void circuit::setFreq(double &fr){ angFreq = 2 * pi*fr; }

// return circuit frequency in Hz
double circuit::getFreq(){ return angFreq / (2 * pi); }

// print circuit graphics
void circuit::graphic(){
	if (serRes > 9){
		cout << endl << "      +----------------+----------------+" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |             Series:         Parallel:" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |               +-+              +-+" << endl;
		cout << "      |               | | x" << serRes << "          | | x" << parRes << endl;
		cout << "      |               | |              | |" << endl;
		cout << "      |               +-+              +-+" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                |                |" << endl;
		cout << "     ---             ----- x" << serCap << "         ----- x" << parCap << endl;
		cout << "   -------           -----            -----" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                \\                \\" << endl;
		cout << "      |                / x" << serInd << "             / x" << parInd << endl;
		cout << "      |                \\                \\" << endl;
		cout << "      |                /                /" << endl;
		cout << "      |                |                |" << endl;
		cout << "      +----------------+----------------+" << endl;
	}
	else if(serCap>9){
		cout << endl << "      +----------------+----------------+" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |             Series:         Parallel:" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |               +-+              +-+" << endl;
		cout << "      |               | | x" << serRes << "           | | x" << parRes << endl;
		cout << "      |               | |              | |" << endl;
		cout << "      |               +-+              +-+" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                |                |" << endl;
		cout << "     ---             ----- x" << serCap << "        ----- x" << parCap << endl;
		cout << "   -------           -----            -----" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                \\                \\" << endl;
		cout << "      |                / x" << serInd << "             / x" << parInd << endl;
		cout << "      |                \\                \\" << endl;
		cout << "      |                /                /" << endl;
		cout << "      |                |                |" << endl;
		cout << "      +----------------+----------------+" << endl;
	}
	else if (serInd > 9){
		cout << endl << "      +----------------+----------------+" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |             Series:         Parallel:" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |               +-+              +-+" << endl;
		cout << "      |               | | x" << serRes << "           | | x" << parRes << endl;
		cout << "      |               | |              | |" << endl;
		cout << "      |               +-+              +-+" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                |                |" << endl;
		cout << "     ---             ----- x" << serCap << "         ----- x" << parCap << endl;
		cout << "   -------           -----            -----" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                \\                \\" << endl;
		cout << "      |                / x" << serInd << "            / x" << parInd << endl;
		cout << "      |                \\                \\" << endl;
		cout << "      |                /                /" << endl;
		cout << "      |                |                |" << endl;
		cout << "      +----------------+----------------+" << endl;
	}
	else{
		cout << endl << "      +----------------+----------------+" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |             Series:         Parallel:" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |               +-+              +-+" << endl;
		cout << "      |               | | x" << serRes << "           | | x" << parRes << endl;
		cout << "      |               | |              | |" << endl;
		cout << "      |               +-+              +-+" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                |                |" << endl;
		cout << "     ---             ----- x" << serCap << "         ----- x" << parCap << endl;
		cout << "   -------           -----            -----" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                |                |" << endl;
		cout << "      |                \\                \\" << endl;
		cout << "      |                / x" << serInd << "             / x" << parInd << endl;
		cout << "      |                \\                \\" << endl;
		cout << "      |                /                /" << endl;
		cout << "      |                |                |" << endl;
		cout << "      +----------------+----------------+" << endl;
	}
}

// Functions to verify user inputs
// function to verify user input for component value (double)
double cinVerify(double &val){
	// check input is valid
	while (cin.fail() || val <= 0){
		cerr << "Error: make sure input is of type double and is greater than 0.\nInput value: ";
		// clear fail bit and ignore input
		cin.clear(); cin.ignore(100,'\n'); cin >> val;
	}
	return val;
}

// multiple component value input version
vector<double> cinVerify(string &val, vector<double> &valList, double val1Length){
	int cont{ 0 };
	while (cont == 0){
		stringstream ss(val); // put val into stringstream
		string str; // declare string to save numbers in
		while (!ss.eof()){
			getline(ss, str, ','); //read inbetween commas
			double dbl; // try to convert string to double, if dosen't work, throw error
			try{
				dbl = stod(str);
			}
			catch (...){
				cerr << "Error: make sure input has the stated format and the same number of inputs as component list.";
				valList.clear();
				cout << "\nRe-input list: ";
				cin >> val;
				break;
			}
			valList.push_back(dbl); // if valid double, push_back onto valList
		}
		if (valList.size() == val1Length){
			cont++; // exit while loop
		}
		else if (valList.size() == 0); // do not execute else statement
		else{
			cerr << "Error: make sure input has the stated format and the same number of inputs as component list.";
			valList.clear();
			cout << "\nRe-input list: ";
			cin >> val;
		}
	}
	return valList;
}

// multiple component input version
vector<string> cinVerify(string &val, vector<string> &array, vector<string> &compList){
	int cont{ 0 };
	while (cont == 0){
		//iterate through characters in input string
		string::iterator si;
		int cnt = 1;
		for (si = val.begin(); si < val.end(); si++){
			string st{ *si };
			// check to see if character is in the desired list
			if (find(array.begin(), array.end(), st) != array.end() && cnt % 2 != 0){ // and that count is odd 
				compList.push_back(st); // append to compList
				if (si == val.end() - 1){
					cont = 1;
					break;
				}
			}
			else if (*si == ','){
				if (si == val.end() - 1){
					cin.ignore();
					cont++;
					break;
				}
			}
			else{
				cerr << "Error: make sure input has the stated format.";
				compList.clear();
				cout << "\nRe-input list: ";
				cin >> val;
				break; // exit for loop and repeat while loop
			}
			cnt++;
		}
	}
	return compList;
}
