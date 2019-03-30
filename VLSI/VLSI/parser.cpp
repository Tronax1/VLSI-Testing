#include "parser.h"
#include <string>
#include <vector>
#include <iostream>

void parser(std::string input, std::vector<std::string> &result) {
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
	}
}
void print_parsed(std::vector<std::string> result) {
	for (int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
}