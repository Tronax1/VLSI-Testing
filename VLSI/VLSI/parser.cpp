#include "parser.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


Parser::Parser() {
	inputs.push_back("Input");
	output.push_back("Output");
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
	std::cout << "Beginning of test" << std::endl;
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
	for (int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
	std::cout << "The primary inputs are:" << std::endl;
	for (int i = 0; i < inputs.size(); i++) {
		std::cout << inputs[i] << std::endl;
	}
	std::cout << "The primary output is:" << std::endl;
	for (int i = 0; i < output.size(); i++) {
		std::cout << output[i] << std::endl;
	}
	std::cout << "The gates are the following: " << std::endl;
	for (int i = 0; i < gates.size(); i++) {
		std::cout << gates[i].output<<" output "<<gates[i].type <<" type "<<gates[i].inputs[0]<<" input1 "<<gates[i].inputs[1]<<" Input2"<< std:: endl;
	}
}