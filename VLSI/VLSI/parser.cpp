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
		temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
		std::cout << temp << std::endl;
		if (temp.size() > 4) {
			GATE gate;
			gate.output = temp.substr(0, 4);
			gate.type = temp.substr(5,3);
			gates.push_back(gate);
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
		std::cout << gates[i].output<<" "<<gates[i].type << std:: endl;
	}
}