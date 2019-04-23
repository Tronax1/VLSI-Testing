#pragma once
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>

/*struct GATE {
	std::string inputs[2];
	std::string output;
	std::string type;
	std::string single_stuck_at_0 = "X";
	std::string single_stuck_at_1 = "X";
};*/
class Circuit {
private:
	std::vector<GATE> gates;
	std::vector<std::vector<std::string>> fault_universe;
public:
	Circuit();
};
#endif 

