#include "parser.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>


Parser::Parser() {
	inputs.push_back("Primary inputs");
	output.push_back("Primary output");
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