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
		remove_if(temp.begin(), temp.end(), isspace);
		temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
		//std::cout << temp << std::endl;
		if (temp.size() > 4) {
			GATE gate;
			fine_tune(gate, temp); //Function to trim down redundant characters in the gate labels
			gates.push_back(gate);
		}
	}
}
void Parser::fine_tune(GATE &gate, std::string gate_information) {
	int count_letter = 0;
	for (int i = 0; i < gate_information.size(); i++) {
		if (count_letter < 4) {
			gate.output.push_back(gate_information[i]);
			count_letter++;
		}
		if (count_letter > 3 && count_letter < 7) {
			gate.type.push_back(gate_information[i + 1]);
			count_letter++;
		}
		if (count_letter > 6 && count_letter < 12) {
			gate.inputs[0].push_back(gate_information[i + 1]);
			count_letter++;
		}
		if (count_letter > 11) {
			gate.inputs[1].push_back(gate_information[i + 1]);
			count_letter++;
		}
	}
	if (gate.type[0] == 'o')
		gate.type.pop_back();
	if (gate.inputs[0][gate.inputs[0].size() - 1] != 't')
		gate.inputs[0].pop_back();
	if (gate.inputs[0][0] == 't' | gate.inputs[0][0] == 'd')
		gate.inputs[0].erase(0, 1);
	if (gate.inputs[1][0] == 't')
		gate.inputs[1].erase(0, 1);
	if (gate.inputs[1].size() > 2 && gate.inputs[1].size() > 4)
		gate.inputs[1].erase(4, 3);
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
		std::cout << gates[i].output<<" "<<gates[i].type <<" "<<gates[i].inputs[0]<<" "<<gates[i].inputs[1]<< std:: endl;
	}
}