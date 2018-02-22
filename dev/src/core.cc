#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<string>
#include<iostream>
#include<pthread.h>
#include <chrono>
#include <thread>
#include<map>
#include<vector>
#include<sstream>
#include<algorithm>
#include<iterator>
#include "inclusion/node.cc"
#include "inclusion/utilities.cc"

vector<Node*> narray;
int startPointer = 1;
std::vector<std::string> memory;

void interpret (string instruction) {
	std::vector<string> splitInstr = split (instruction, '~');
	string instr = splitInstr.at(0);
	if (instr.compare ("print") == 0) {
		std::cout << memory.at(toInt (splitInstr.at(1))) << "\n";
	} else if (instr.compare ("apmem") == 0) {
		//std::cout << splitInstr.at(1) << "\n";
		memory.push_back (splitInstr.at(1));
	} else if (instr.compare ("incre") == 0) {
		memory[toInt (splitInstr.at(1))] = std::to_string(toInt(memory[toInt (splitInstr.at(1))]) + 1);
	} else if (instr.compare ("delay") == 0) {
		delay (toInt(splitInstr.at(1)));
	} else if (instr.compare ("popla") == 0) {
		memory.pop_back();
	} else if (instr.compare ("runsc") == 0) {
		// Run script
	} else if (instr.compare ("stcho") == 0) {
		// Start chain on other node
	}
}

//bool shouldContinueExecuting = true;

int getNodeWithName (int nam) {
	int ret = 0;
	for (int index=0; index < narray.size(); index++) {
		if ((narray [index] -> name) == nam) {
			ret = index;
		}
	}
	return ret;
}

void run (int startNode) {
	int ptr = startNode;
	bool shldContinue = true;
	while (shldContinue) {
		// Get by name
		if (ptr != 0) {
			int index = getNodeWithName(ptr);
			Node* n = narray [index];
			interpret (n -> data);
			ptr = (n -> pointer);
		} else {
			shldContinue = false;
		}
	}
}

int main () {
	//std::cout << "Hi there, User.\n";
	//std::cout << "I’m Indexus.\n";
	// Start process
	//
	//Node* newNode = ;
	std::cout << "Here we go.\n";
	// narray.push_back(new Node(1, "apmem~Hi there, User.", 2));
	// narray.push_back(new Node(2, "apmem~I'm Indexus", 3));
	// narray.push_back(new Node(3, "apmem~Printing myself!", 4));
	// narray.push_back(new Node(4, "apmem~Looping...", 6));
	// narray.push_back(new Node(6, "print~0", 7));
	// narray.push_back(new Node(7, "print~1", 8));
	// narray.push_back(new Node(8, "print~2", 5));
	// narray.push_back(new Node(5, "print~3", 5));
	narray.push_back (new Node(1, "apmem~4", 2));
	narray.push_back (new Node(2, "print~0", 3));
	narray.push_back (new Node(3, "incre~0", 4));
	narray.push_back (new Node(4, "delay~100", 2));

	run (startPointer);
	return 0;
}
