#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.h"

using namespace std;

int main() {

	vector<string> parsed;
	string netlist;
	Parser Parse;
	bool is_run = true, file_read = false;
	int option;
	while (is_run) {
		cout << "[0] Read the input netlist" << endl;
		cout << "[1] List fault classes" << endl;
		cout << "[2] Perform fault collapsing" << endl;
		cout << "[3] Generate tests (D-Algorithm)" << endl;
		cout << "[4] Generate tests (boolean satisfiablity)" << endl;
		cout << "[5] Exit" << endl;
		cin >> option;
		switch (option) {
			case 0: {
				ifstream myFile;
				myFile.open("circuit.txt");
				if (!myFile) { cout << "Could not open file" << endl; }
				
				while (getline(myFile, netlist)) { Parse.parser(netlist, parsed); }
				myFile.close();
				Parse.create_gates(parsed);
				//Parse.print_parsed(parsed);
				cout << "---------------------------------------" << endl;
				cout << "File read successfully" << endl;
				cout << "---------------------------------------" << endl<<endl;
				file_read = true;
			}
				break;
			case 1: {
				if (!file_read) { cout << "You have not read in the netlist" << endl << endl; }
				else {
					Parse.generate_fault_classes();
					Parse.print_fault_classes();
				}
			}
				break;
			case 2: {
				if (!file_read) { cout << "You have not read in the netlist" << endl << endl; }
				else {
					Parse.fault_collapsing();
					cout << "---------------------------------------" << endl;
					cout << "Fault collapsing perfomed successfully" << endl<<endl<<"Press 1 to view updated classes\n";
					cout << "---------------------------------------" << endl << endl;
				}
			}
				break;
			case 3: {
				if (!file_read) { cout << "You have not read in the netlist" << endl << endl; }
			}
				break;
			case 4: {
				if (!file_read) { cout << "You have not read in the netlist" << endl << endl; }
			}
				break;
			case 5: is_run = false;
				break;
			default: cout << "Not a valid option" << endl;
		}
	}
	return 0;
}