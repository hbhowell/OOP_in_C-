// OOP in C++ Project - A.C. Circuits - Harry Howell April 2019
// Program to compute impedance of an A.C. circuit with an arbitrary 
// number of capacitors, resistors and inductors connected in series or parallel.
// main implementation

// Include libraries

#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<utility>
#include<cmath>
#include<sstream>
#include"capacitor.h"
#include"components.h"
#include"circuit.h"
#include"inductor.h"
#include"resistor.h"

// Namespaces

using namespace std;

int main(){
	// global variables
	vector<string> yorn{ "y", "n" }, compSelection{ "r", "c", "i" }, configuration{ "s", "p" }, singleMult{"s","m"};
	// ask user if they want demonstration of constructors etc...
	cout << "Before starting program, demonstrate use of constructors/\nassignment operators for Capacitor class (y/n)?: ";
	string str;
	cin >> str;
	str = cinVerify(str, yorn);
	if (str == "y"){
		double freq{ 10 };
		// demonstrate constructors
		capacitor c1;
		c1.setFreq(freq);
		cout << "\nDefault component c1 created: c1=\n";
		c1.info();
		capacitor c2(900, "p", 1);
		c2.setFreq(freq);
		cout << "\nParamaterised capacitor c2 created in parallel with capacitance 900nF: c2=\n";
		c2.info();
		capacitor c3(c2);
		cout << "\nCopy constructor initiated such that c3 = c2. c3=\n";
		c3.info();
		capacitor c4;
		c4 = move(c3);
		cout << "\nMove assignment initiated such that c4 = c3: c4=\n";
		c4.info();
		cout << "\nc3=\n";
		c3.info();
	}
	// ask user if they want to create a new circuit?
	cout << "\nCreate a new circuit (y/n)?: ";
	string newCirc;
	cin >> newCirc;
	newCirc = cinVerify(newCirc,yorn);

	while (newCirc == "y"){
		// ask for driving frequency of circuit e.m.f source
		cout << "\nInput circuit source driving frequency in Hz: ";
		double frequency;
		cin >> frequency;
		frequency = cinVerify(frequency);
		cin.clear();
		cin.ignore(100,'\n');
		// create circuit c1 with default constructor
		circuit ct1;
		ct1.setFreq(frequency);
		cout << "Circuit with source frequency of " << frequency <<
			"Hz created.\n";

		string createComp{"y"};
		do{
			// ask whether to add single or multiple components
			cout << "\nAdd a single component [s] or multiple components [m]?: ";
			string snglmtpl;
			cin >> snglmtpl;
			snglmtpl = cinVerify(snglmtpl, singleMult);

			if (snglmtpl == "s"){
				cout << "\nChoose a component to add : Resistor[r], Capacitor[c], Inductor[i] : "; // ask for initial component
				string compType;
				cin >> compType;
				compType = cinVerify(compType, compSelection);

				// create component accordingly
				if (compType == "r"){
					// ask for component value
					double res;
					cout << "\nInput component resistance in Ohms: ";
					cin >> res;
					res = cinVerify(res); // check of correct format using cinVerify(double &val) 
					cin.clear(); // clear fail bit
					cin.ignore(100, '\n'); // ignore input
					// ask for configuration (series/parallel)
					string configType;
					cout << "\nInput configuration type, series or parallel [s or p]: ";
					cin >> configType;
					configType = cinVerify(configType, configuration);
					// create component and add to circuit
					resistor r1(res, configType, frequency);
					cout << "\nComponent information:\n";
					r1.info();
					cout << "\nCommit component to circuit (y/n)?: ";
					cin >> str;
					str = cinVerify(str, yorn);
					if (str == "y"){
						component * cmp1;
						cmp1 = &r1;
						ct1.addComp(cmp1); // add pointer to list in circuit
						cout << "Resistor added to circuit." << endl;
					}
					// continue to end of block
				}
				else if (compType == "c"){
					double cap;
					cout << "\nInput component capacitance in nF: ";
					cin >> cap;
					cap = cinVerify(cap);
					cin.clear(); // clear fail bit
					cin.ignore(100, '\n'); // ignore input
					string configType;
					cout << "\nInput configuration type, series or parallel [s or p]: ";
					cin >> configType;
					configType = cinVerify(configType, configuration);
					capacitor c1(cap, configType, frequency); 
					// create component and add to circuit
					cout << "\nComponent information:\n";
					c1.info();
					cout << "\nCommit component to circuit (y/n)?: ";
					cin >> str;
					str = cinVerify(str, yorn);
					if (str == "y"){
						component * cmp1;
						cmp1 = &c1;
						ct1.addComp(cmp1);
						cout << "Capacitor added to circuit." << endl;
					}
				}
				else if (compType == "i"){
					double ind;
					cout << "\nInput component inductance in mH: ";
					cin >> ind;
					ind = cinVerify(ind);
					cin.clear(); // clear fail bit
					cin.ignore(100, '\n'); // ignore input
					string configType;
					cout << "\nInput configuration type, series or parallel [s or p]: ";
					cin >> configType;
					configType = cinVerify(configType, configuration);
					inductor i1(ind, configType, frequency); 
					// create component and add to circuit
					cout << "\nComponent information:\n";
					i1.info();
					cout << "\nCommit component to circuit (y/n)?: ";
					cin >> str;
					str = cinVerify(str, yorn);
					if (str == "y"){
						component * cmp1;
						cmp1 = &i1;
						ct1.addComp(cmp1);
						cout << "Inductor added to circuit." << endl;
					}
				}
				cout << "\nContinue adding components to circuit (y/n)?: ";
				cin >> str;
				str = cinVerify(str, yorn);
				if (str == "n"){
					// print circuit information and set createComp to "n"
					ct1.info();
					ct1.graphic();
					createComp = str;
				}
			}
			else{
				// Ask user for input of multiple component list, run validity checks and append to vector of strings compList 
				cout << "\nAdd list using components chosen from resistor [r], capacitor [c] or inductor [i].\n" <<
					"Example: inputting {r,r,c,i,c}, will initialise 2 resistors, 2 capcitors and 1 inductor.\n\nInput list: ";
				string val1, val2, val3;
				cin >> val1;
				vector<string> compList;
				compList = cinVerify(val1, compSelection, compList);
				vecOut(compList);
				// Similarly for corresponding values; add to vector of doubles valList
				cout << "\nAdd list of corresponding component values:\n" <<
					"Referencing the above example, inputting {10,10,900,5,900}, will set both resistors to 10 Ohms, \nthe capacitors "
					<< "to 900 nF and the inductor to 5mH.\n\nInput list: ";
				cin >> val2;
				vector<double> valList;
				valList = cinVerify(val2, valList, compList.size());
				vecOut(valList);
				// Finally, same for the configurations of the input compList; add to vector of strings configList
				cout << "\nAdd list of corresponding configuration types; series [s] or parallel [p]:\n" <<
					"Inputting {s,s,p,p,p}, will set both resistors in series, \nand the capacitors "
					<< "and inductor in parallel.\n\nInput list: ";
				cin >> val3;
				vector<string> configList;
				// Extra loop to check for size of input list for strings
				do{
					configList = cinVerify(val3, configuration, configList);
					if (configList.size() != compList.size()){
						cerr << "Error: make sure input has same number of inputs as component list.";
						configList.clear();
						cout << "\nRe-input list: ";
						cin >> val3;
					}
				} while (configList.size() != compList.size());
				vecOut(configList);

				// using compList, valList and configList, append components to new circuit and return circuit info
				cout << "\nCommit components to circuit (y/n)?: ";
				cin >> str;
				str = cinVerify(str, yorn);
				if (str == "y"){
					ct1.addCompList(compList, valList, configList);
					cout << "Components added to circuit." << endl;
				}
				cout << "\nContinue adding components to circuit (y/n)?: ";
				cin >> str;
				str = cinVerify(str, yorn);
				if (str == "n"){
					// print circuit information and set createComp to "n"
					ct1.info();
					ct1.graphic();
					createComp = str;
				}
			}
		} while (createComp == "y");

		cout << "\nCreate a new circuit (y/n)?: ";
		cin >> newCirc;
		newCirc = cinVerify(newCirc, yorn);
	}
	cout << "\nProgram terminated." << endl;
	return 0;
}