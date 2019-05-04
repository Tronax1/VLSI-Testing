#pragma once
#ifndef PARSER
#define PARSER

#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <string>


class Parser {

private:
	std::vector<std::string> inputs;
	std::vector<std::string> output;

public:
	Parser();
	bool is_input(std::string input);
	bool is_output(std::string input);
	void parser(std::string input, std::vector<std::string> &result);
	void copy_input_output_data(std::vector<std::string> &input, 
								std::vector<std::string> &outputs);
};
#endif
