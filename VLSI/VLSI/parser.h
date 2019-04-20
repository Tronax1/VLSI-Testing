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
	std::string single_stuck_at_0 = "X";
	std::string single_stuck_at_1 = "X";
};
class Parser {

private:
	std::vector<std::string> inputs;
	std::vector<std::string> output;
	std::vector<GATE> gates;
	std::vector<std::vector<std::string>> fault_universe;

public:
	Parser();
	bool is_input(std::string input);
	bool is_output(std::string input);
	bool is_wire_present(std::string wire, std::vector<std::vector<std::string>> fault_universe);
	void fine_tune(GATE &gate, std::string gate_information);
	void create_gates(std::vector<std::string> result);
	void parser(std::string input, std::vector<std::string> &result);
	void print_parsed(std::vector<std::string> result);
	void generate_fault_classes();
	void fault_collapsing();
	void print_fault_classes();
};
#endif
