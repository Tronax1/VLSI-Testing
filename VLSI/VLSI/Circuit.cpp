#include "Parser.h"
#include "Circuit.h"

Circuit::Circuit() {
	std::vector<std::string> header{ "Wire   ", "s-a-0 ", " s-a-1" };
	fault_universe.push_back(header);
}

bool Circuit::is_wire_present(std::string wire,
							  std::vector<std::vector<std::string>> fault_universe) {

	for (int i = 0; i < fault_universe.size(); i++) {
		if (fault_universe[i][0] == wire) { return true; }
	}
	return false;
}
void Circuit::create_gates(std::vector<std::string> result, 
						   std::vector<std::string> input, 
						   std::vector<std::string> outputs) {

	std::string temp;
	for (int i = 0; i < input.size(); i++) { inputs.push_back(input[i]); }
	for (int i = 0; i < outputs.size(); i++) { output.push_back(outputs[i]); }

	for (int i = 0; i < result.size(); i++) {
		temp = result[i];
		if (temp.size() > inputs.size()) {
			GATE gate;
			fine_tune(gate, temp); //Function to trim down redundant characters in the gate labels
			gates.push_back(gate);
		}
	}
}
void Circuit::fine_tune(GATE &gate, std::string gate_information) {
	int count_letter = 0;
	bool first = true, second = false, third = false, fourth = false;
	for (int i = 0; i < gate_information.size(); i++) {
		if (first) {
			if (gate_information[i] != '\t' && gate_information[i] != ' ') 
				{ gate.output.push_back(gate_information[i]); }
			else {
				first = false;
				second = true;
				i++;
			}
		}
		if (second) {
			if (gate_information[i] != '\t' && gate_information[i] != ' ') 
				{ gate.type.push_back(gate_information[i]); }
			else {
				second = false;
				third = true;
				i++;
			}
		}
		if (third) {
			if (gate_information[i] != '\t' && gate_information[i] != ' ') 
				{ gate.inputs[0].push_back(gate_information[i]); }
			else {
				third = false;
				fourth = true;
				i++;
			}
		}
		if (fourth) { gate.inputs[1].push_back(gate_information[i]); }
	}
}
void Circuit::generate_fault_classes() {
	std::vector<std::string> temp{ gates[0].inputs[0], 
									gates[0].single_stuck_at_0, 
									gates[0].single_stuck_at_1 };

	fault_universe.push_back(temp);
	temp.clear();
	for (int i = 1; i < gates.size(); i++) {
		if (!is_wire_present(gates[i].inputs[0], fault_universe)) {
			temp.push_back(gates[i].inputs[0]);
			temp.push_back(gates[i].single_stuck_at_0);
			temp.push_back(gates[i].single_stuck_at_1);
			fault_universe.push_back(temp);
			temp.clear();
		}
	}
	for (int i = 0; i < gates.size(); i++) {
		if (!is_wire_present(gates[i].inputs[1], fault_universe)) {
			temp.push_back(gates[i].inputs[1]);
			temp.push_back(gates[i].single_stuck_at_0);
			temp.push_back(gates[i].single_stuck_at_1);
			fault_universe.push_back(temp);
			temp.clear();
		}
	}
	for (int i = 0; i < gates.size(); i++) {
		if (!is_wire_present(gates[i].output, fault_universe)) {
			if (gates[i].output == output[1]) {
				temp.push_back(gates[i].output);
				temp.push_back("X");
				temp.push_back("X");
				fault_universe.push_back(temp);
				temp.clear();
			}
			else {
				temp.push_back(gates[i].output);
				temp.push_back(gates[i].single_stuck_at_0);
				temp.push_back(gates[i].single_stuck_at_1);
				fault_universe.push_back(temp);
				temp.clear();
			}
		}
	}
}
void Circuit::fault_collapsing() {
	fault_universe.clear();
	std::vector<std::string> header{ "Wire   ", "s-a-0 ", " s-a-1" };
	fault_universe.push_back(header);
	for (int i = 0; i < gates.size(); i++) {
		if (gates[i].type == "and") { gates[i].single_stuck_at_0 = " "; }
		if (gates[i].type == "or") { gates[i].single_stuck_at_1 = " "; }
		if (gates[i].type == "nand") { gates[i].single_stuck_at_0 = " "; }
		if (gates[i].type == "nor") { gates[i].single_stuck_at_1 = " "; }
	}
}
void Circuit::print_fault_classes() {
	std::cout << "---------------------------------------" << std::endl;
	for (int i = 0; i < fault_universe.size(); i++) {
		for (int j = 0; j < fault_universe[i].size(); j++) 
			{ std::cout << fault_universe[i][j] << std::setw(5); }
		std::cout << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}
void Circuit::print_gates() {
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
}