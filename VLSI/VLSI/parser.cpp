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
	//fault_universe.push_back(header);
}
bool Parser::is_input(std::string input) {
	if (input.find("input") != std::string::npos) { return true; }
	return false;
}
bool Parser::is_output(std::string input) {
	if (input.find("output") != std::string::npos) { return true; }
	return false;
}
void Parser::parser(std::string input, std::vector<std::string> &result) {
	std::string parsed_netlist;
	if (input[0] != '$') {
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == '$') { break; }
			else if (input[i] != ' ') { parsed_netlist.append(input, i, 1); }
		}
		result.push_back(parsed_netlist);
		if (is_input(input)) { inputs.push_back(parsed_netlist); }
		if (is_output(input)) { output.push_back(parsed_netlist); }
	}
}
void Parser::copy_input_output_data(std::vector<std::string> &input, std::vector<std::string> &outputs) {
	for (int i = 0; i < inputs.size(); i++)
		input.push_back(inputs[i]);
	for (int i = 0; i < output.size(); i++)
		outputs.push_back(output[i]);
}
/*void Parser::print_parsed(std::vector<std::string> result) {
	for (int i = 0; i < inputs.size(); i++) { std::cout << inputs[i] << std::endl; }
	for (int i = 0; i < output.size(); i++) { std::cout << output[i] << std::endl; }

	std::cout << "The gates are the following: " << std::endl;
	std::cout << "Gate inputs";
	std::cout << std::setw(10);
	std::cout << "Type";
	std::cout << std::setw(20);
	std::cout << "Gate output"<<std::endl;

	for (int i = 0; i < gates.size(); i++) {
		std::cout << gates[i].inputs[0]<<std::setw(5)<<gates[i].inputs[1]<< std::setw(10) 
			<<gates[i].type<< std::setw(20) <<gates[i].output<< std:: endl;
	}
	std::cout << std::endl;
}*/
