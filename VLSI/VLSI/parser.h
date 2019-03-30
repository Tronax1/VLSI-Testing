#pragma once
#ifndef PARSER
#define PARSER

#include <iostream>
#include <string>
#include <fstream> 
#include <vector>


void parser(std::string input, std::vector<std::string> &result);
void print_parsed(std::vector<std::string> result);

#endif
