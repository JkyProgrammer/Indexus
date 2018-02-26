#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "inclusion/node.cc"
#include "inclusion/utilities.cc"
#include "inclusion/log.cc"

vector<Node*> narray;
int startPointer = 1;
std::vector<std::string> memory;

int getNodeWithName (int nam) {
	int ret = 0;
	for (int index=0; index < narray.size(); index++) {
		if ((narray [index] -> name) == nam) {
			ret = index;
		}
	}
	return ret;
}

void run (int startNode);

void convertAndRun (string in) {
	run (toInt (in));
}

void interpret (string instruction) {
	std::vector<string> splitInstr = split (instruction, '~');
	string instr = splitInstr.at(0);
	if (instr.compare ("print") == 0) {
		// Output whatever is at a specified point in memory
		std::cout << memory.at(toInt (splitInstr.at(1))) << "\n";
	} else if (instr.compare ("apmem") == 0) {
		// Append something to the memory array
		memory.push_back (splitInstr.at(1));
	} else if (instr.compare ("incre") == 0) {
		// Increment a specified point in memory
		memory[toInt (splitInstr.at(1))] = std::to_string(toInt(memory[toInt (splitInstr.at(1))]) + 1);
	} else if (instr.compare ("delay") == 0) {
		// Wait a number of milliseconds
		delay (toInt(splitInstr.at(1)));
	} else if (instr.compare ("popla") == 0) {
		// Remove the last item from memory
		memory.pop_back();
	} else if (instr.compare ("runsc") == 0) {
		// Run script from file
		string contents = readContentsOfFile (splitInstr[1]);
		std::vector<string> contentLines = split (contents, '\n');
		for (string line : contentLines) {
			interpret (line);
		}
	} else if (instr.compare ("sttch") == 0) {
		// Start chain on other thread
		std::thread newThread(convertAndRun, splitInstr.at(1));
	} else if (instr.compare ("runsh") == 0) {
		// Run a shell command at an index
		string toExecute = memory[toInt(splitInstr[1])];
		string result = exec (toExecute);
		memory.push_back (result);
	} else if (instr.compare ("compr") == 0) {
		// Compare two values and append the result to memory
	} else if (instr.compare ("readf") == 0) {
		// Read the contents of a file into memory
		string cont = readContentsOfFile (splitInstr[1]);
		memory.push_back (cont);
	} else if (instr.compare ("writf") == 0) {
		// Write the contents of a point in memory into a file
		string path = splitInstr[1];
		int contentLoc = toInt(splitInstr[2]);
		string content = memory [contentLoc];
		writeContentToFile (content, path);
	} else if (instr.compare ("logtx") == 0) {
		// Automatically format and write a debug to the log file
		string tx = memory[toInt(splitInstr[1])];
		log (tx);
	} else if (instr.compare ("iftru") == 0) {
		// Compare two values and run a script if the same
		int memRef1 = toInt (splitInstr[1]);
		int memRef2 = toInt (splitInstr[2]);
		
		string atMem1 = memory[memRef1];
		string atMem2 = memory[memRef2];
		
		if (atMem1.compare (atMem2) == 0) {
			interpret ("runsc~" + splitInstr[3]);
		}
	} else if (instr.compare ("iffal") == 0) {
		// Compare two values and run a script if different
		int memRef1 = toInt (splitInstr[1]);
		int memRef2 = toInt (splitInstr[2]);
		
		string atMem1 = memory[memRef1];
		string atMem2 = memory[memRef2];
		
		if (atMem1.compare (atMem2) == 1) {
			interpret ("runsc~" + splitInstr[3]);
		}
	} else if (instr.compare ("cocat") == 0) {
		// Concatenate strings
		int memRef1 = toInt (splitInstr[1]);
		int memRef2 = toInt (splitInstr[2]);
		
		string atMem1 = memory[memRef1];
		string atMem2 = memory[memRef2];
		
		string output = atMem1 + atMem2;
		memory.push_back (output);
	} else if (instr.compare ("adnum") == 0) {
		// Add two numbers
		int memRef1 = toInt (splitInstr[1]);
		int memRef2 = toInt (splitInstr[2]);
		
		int atMem1 = toInt(memory[memRef1]);
		int atMem2 = toInt(memory[memRef2]);
		
		int output = atMem1 + atMem2;
		memory.push_back (to_string(output));
	}
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
//bool shouldContinueExecuting = true;

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
	//narray.push_back (new Node(1, "readf~textFile.txt", 6));
	//narray.push_back (new Node(6, "print~0", 7));
	//narray.push_back (new Node(7, "popla", 2));
	narray.push_back (new Node(1, "apmem~4", 3));
	narray.push_back (new Node(3, "print~0", 8));
	narray.push_back (new Node(8, "logtx~0", 4));
	narray.push_back (new Node(4, "incre~0", 5));
	narray.push_back (new Node(5, "delay~100", 3));

	run (startPointer);
	return 0;
}
