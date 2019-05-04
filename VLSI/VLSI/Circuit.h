#pragma once
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>
#include <iomanip>

struct GATE {
	std::string inputs[2];
	std::string output;
	std::string type;
	std::string single_stuck_at_0 = "X";
	std::string single_stuck_at_1 = "X";
	bool has_primary_inputs = false;
	GATE *next = NULL;
	GATE *prev = NULL;
};
class Circuit {
private:
	std::vector<std::string> inputs;
	std::vector<std::string> output;
	std::vector<GATE> gates;
	std::vector<std::vector<std::string>> fault_universe;
public:
	Circuit();
	bool is_wire_present(std::string wire, 
						 std::vector<std::vector<std::string>> fault_universe);

	void fine_tune(GATE &gate, std::string gate_information);

	void create_gates(std::vector<std::string> result, 
					  std::vector<std::string> input, 
				      std::vector<std::string> outputs);

	void generate_fault_classes();
	void fault_collapsing();
	void print_fault_classes();
	void print_gates();
};
#endif 

