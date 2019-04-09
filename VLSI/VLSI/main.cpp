#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.h"

using namespace std;

int main() {

	vector<string> parsed;
	string netlist;
	bool is_run = true;
	int option;
	while (is_run) {
		cout << "[0] Read the input netlist" << endl;
		cout << "[1] Perform fault collapsing" << endl;
		cout << "[2] List fault classes" << endl;
		cout << "[3] Generate tests (D-Algorithm)" << endl;
		cout << "[4] Generate tests (boolean satisfiablity)" << endl;
		cout << "[5] Exit" << endl;
		cin >> option;
		switch (option) {
			case 0: {
				ifstream myFile;
				Parser Parse;
				myFile.open("circuit.txt");
				if (!myFile) {
					cout << "Could not open file" << endl;
				}
				while (getline(myFile, netlist)) {
					Parse.parser(netlist, parsed);
				}
				myFile.close();
				Parse.print_parsed(parsed);
			}
				break;
			case 1: cout << "Still missing" << endl;
				break;
			case 2: cout << "Still missing" << endl;
				break;
			case 3: cout << "Still missing" << endl;
				break;
			case 4: cout << "Still missing" << endl;
				break;
			case 5: is_run = false;
				break;
			default: cout << "Not a valid option" << endl;
		}
	}
	return 0;
}