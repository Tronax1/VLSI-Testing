#include "parser.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>


Parser::Parser() {
	std::vector<std::string> header {"Wire   ", "s-a-0 ", " s-a-1"};
	inputs.push_back("Primary inputs");
	output.push_back("Primary output");
	fault_universe.push_back(header);
}
bool Parser::is_input(std::string input) {
	if (input.find("input") != std::string::npos)
		return true;
	return false;
}
bool Parser::is_output(std::string input) {
	if (input.find("output") != std::string::npos)
		return true;
	return false;
}
bool Parser::is_wire_present(std::string wire, std::vector<std::vector<std::string>> fault_universe) {
	for (int i = 0; i < fault_universe.size(); i++) {
		if (fault_universe[i][0] == wire)
			return true;
	}
	return false;
}
void Parser::create_gates(std::vector<std::string> result) {
	std::string temp;
	for (int i = 0; i < result.size(); i++) {
		temp = result[i];
		if (temp.size() > inputs.size()) {
			GATE gate;
			fine_tune(gate, temp); //Function to trim down redundant characters in the gate labels
			gates.push_back(gate);
		}
	}
}
void Parser::fine_tune(GATE &gate, std::string gate_information) {
	int count_letter = 0;
	bool first = true, second = false, third = false, fourth = false;
	for (int i = 0; i < gate_information.size(); i++) {
		if (first) {
			if (gate_information[i] != '\t' && gate_information[i] != ' ') {
				
				gate.output.push_back(gate_information[i]);
			}
			else {
				first = false;
				second = true;
				i++;
			}
		}
		if (second) {
			if (gate_information[i] != '\t' && gate_information[i] != ' ') {
				
				gate.type.push_back(gate_information[i]);
			}
			else {
				second = false;
				third = true;
				i++;
			}	
		}
		if (third) {
			if (gate_information[i] != '\t' && gate_information[i] != ' ') {
				gate.inputs[0].push_back(gate_information[i]);
			}
			else {
				third = false;
				fourth = true;
				i++;
			}
		}
		if (fourth) {
			gate.inputs[1].push_back(gate_information[i]);
		}
	}
}
void Parser::parser(std::string input, std::vector<std::string> &result) {
	std::string parsed_netlist;
	if (input[0] != '$') {
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == '$') {
				break;
			}
			else if (input[i] != ' ') {
				parsed_netlist.append(input, i, 1);
			}
		}
		result.push_back(parsed_netlist);
		if (is_input(input))
			inputs.push_back(parsed_netlist);
		if (is_output(input)) {
			output.push_back(parsed_netlist);
		}	
	}
}
void Parser::print_parsed(std::vector<std::string> result) {
	for (int i = 0; i < inputs.size(); i++) {
		std::cout << inputs[i] << std::endl;
	}
	for (int i = 0; i < output.size(); i++) {
		std::cout << output[i] << std::endl;
	}
	std::cout << "The gates are the following: " << std::endl;
	std::cout << "Gate inputs";
	std::cout << std::setw(10);
	std::cout << "Type";
	std::cout << std::setw(20);
	std::cout << "Gate output"<<std::endl;


	for (int i = 0; i < gates.size(); i++) {
		std::cout << gates[i].inputs[0]<<std::setw(5)<<gates[i].inputs[1]<< std::setw(10) <<gates[i].type<< std::setw(20) <<gates[i].output<< std:: endl;
	}
	std::cout << std::endl;
}
void Parser::generate_fault_classes() {
	std::vector<std::string> temp{ gates[0].inputs[0], "X", "X" };
	fault_universe.push_back(temp);
	temp.clear();
	for (int i = 1; i < gates.size(); i++) {
		if (!is_wire_present(gates[i].inputs[0], fault_universe)) {
			temp.push_back(gates[i].inputs[0]);
			temp.push_back("X");
			temp.push_back("X");
			fault_universe.push_back(temp);
			temp.clear();
		}
	}
	for (int i = 0; i < gates.size(); i++) {
		if (!is_wire_present(gates[i].inputs[1], fault_universe)) {
			temp.push_back(gates[i].inputs[1]);
			temp.push_back("X");
			temp.push_back("X");
			fault_universe.push_back(temp);
			temp.clear();
		}
	}
	for (int i = 0; i < gates.size(); i++) {
		if (!is_wire_present(gates[i].output, fault_universe)) {
			temp.push_back(gates[i].output);
			temp.push_back("X");
			temp.push_back("X");
			fault_universe.push_back(temp);
			temp.clear();
		}
	}
}
void Parser::print_fault_classes() {
	std::cout << "---------------------------------------" << std::endl;
	for (int i = 0; i < fault_universe.size(); i++) {
		for (int j = 0; j < fault_universe[i].size(); j++) {
			std::cout << fault_universe[i][j] << std::setw(5);
		}
		std::cout<<std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}