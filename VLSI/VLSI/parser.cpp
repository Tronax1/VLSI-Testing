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
void Parser::copy_input_output_data(std::vector<std::string> &input, 
								    std::vector<std::string> &outputs) {

	for (int i = 0; i < inputs.size(); i++)
		input.push_back(inputs[i]);
	for (int i = 0; i < output.size(); i++)
		outputs.push_back(output[i]);
}
