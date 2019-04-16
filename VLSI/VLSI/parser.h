#pragma once
#ifndef PARSER
#define PARSER

#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <string>

struct GATE {
	std::string inputs[2];
	std::string output;
	std::string type;
};
class Parser {

private:
	std::vector<std::string> inputs;
	std::vector<std::string> output;
	std::vector<GATE> gates;

public:
	Parser();
	bool is_input(std::string input);
	bool is_output(std::string input);
	void fine_tune(GATE &gate, std::string gate_information);
	void create_gates(std::vector<std::string> result);
	void parser(std::string input, std::vector<std::string> &result);
	void print_parsed(std::vector<std::string> result);
};



#endif
