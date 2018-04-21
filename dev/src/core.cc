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

vector<Node*> narray;
int startPointer = 0;
std::vector<std::string> memory;

void run (int startNode, vector<Node*>* nodes);

void convertAndRun (string in, vector<Node*>* nodes) {
	run (toInt (in), nodes);
}

void loadInstructionNodesFrom (string file, vector<Node*>* to) {
  string cont = readContentsOfFile (file);
  std::vector<string> lines = split (cont, '\n');
  for (string line : lines) {
    std::vector<string> parts = split (line, '*');
    string instruction = parts[0];
    int pointer = toInt (parts[1]);
    (*to).push_back (new Node(instruction, pointer));
  }
}

int interpret (string instruction, vector<Node*>* nodeArray) {
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
		vector<Node*> arr;
		loadInstructionNodesFrom(splitInstr[1], &arr);
		run (0, &arr);
	} else if (instr.compare ("sttch") == 0) {
		// Start chain on other thread
		std::thread newThread(convertAndRun, splitInstr.at(1), nodeArray);
	} else if (instr.compare ("runsh") == 0) {
		// Run a shell command at an index
		string toExecute = memory[toInt(splitInstr[1])];
		string result = exec (toExecute);
		memory.push_back (result);
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
		// Compare two values and jump to a node if the same
		int memRef1 = toInt (splitInstr[1]);
		int memRef2 = toInt (splitInstr[2]);

		string atMem1 = memory[memRef1];
		string atMem2 = memory[memRef2];

		if (atMem1.compare (atMem2) == 0) {
			//interpret ("runsc~" + splitInstr[3]);
			return toInt(splitInstr[3]);
		}
	} else if (instr.compare ("iffal") == 0) {
		// Compare two values and jump to a node if different
		int memRef1 = toInt (splitInstr[1]);
		int memRef2 = toInt (splitInstr[2]);

		string atMem1 = memory[memRef1];
		string atMem2 = memory[memRef2];

		if (atMem1.compare (atMem2) == 1) {
			//interpret ("runsc~" + splitInstr[3]);
			return toInt(splitInstr[3]);
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
	} else if (instr.compare ("getin") == 0) {
		// Get a line of input from the user
		string inputResult;
		cin >> inputResult;
		memory.push_back (inputResult);
	} else if (instr.compare ("biand") == 0) {
		// Add the result of a binary AND to memory
		int bi1 = toInt (splitInstr[1]);
		int bi2 = toInt (splitInstr[2]);
		int atMem1 = toInt(memory[bi1]);
		int atMem2 = toInt(memory[bi2]);

		bool bo1 = atMem1;
		bool bo2 = atMem2;

		if (bo1 && bo2) {
			interpret ("apmem~1", NULL);
		} else {
			interpret ("apmem~0", NULL);
		}
	} else if (instr.compare ("binot") == 0) {
		// Add the result of a binary NOT to memory
		int bi1 = toInt (splitInstr[1]);
		int atMem1 = toInt(memory[bi1]);

		bool bo1 = atMem1;
		if (bo1) {
			interpret ("apmem~0", NULL);
		} else {
			interpret ("apmem~1", NULL);
		}
	} else if (instr.compare ("bi-or") == 0) {
		// Add the result of a binary OR to memory
		int bi1 = toInt (splitInstr[1]);
		int bi2 = toInt (splitInstr[2]);
		int atMem1 = toInt(memory[bi1]);
		int atMem2 = toInt(memory[bi2]);

		bool bo1 = atMem1;
		bool bo2 = atMem2;

		if (bo1 || bo2) {
			interpret ("apmem~1", NULL);
		} else {
			interpret ("apmem~0", NULL);
		}
	} else if (instr.compare ("bixor") == 0) {
		// Add the result of a binary XOR to memory
		int bi1 = toInt (splitInstr[1]);
		int bi2 = toInt (splitInstr[2]);
		int atMem1 = toInt(memory[bi1]);
		int atMem2 = toInt(memory[bi2]);

		bool bo1 = atMem1;
		bool bo2 = atMem2;

		if ((bo1 || bo2) && !(bo1 && bo2)) {
			interpret ("apmem~1", NULL);
		} else {
			interpret ("apmem~0", NULL);
		}
	}
	return -1;
}

void run (int startNode, vector<Node*>* nodes) {
	int ptr = startNode;
	bool shldContinue = true;
	while (shldContinue) {
		// Get by name
		if (ptr != -1) {
			int index = ptr;
			Node* n = (*nodes) [index];
			ptr = (n -> pointer);
			int i = interpret (n -> data, nodes);
			if (i >= 0) {
				ptr = i;
			}
		} else {
			shldContinue = false;
		}
	}
}

int main (int argc, char** argv) {
  // Increment the run counter, so we generate a new log file
	incrementRunCount();

  // Indicate we started successfully
	std::cout << "Here we go.\n";

  // Read nodes from control file
  string controlPath = "controlCode/core.ind";
  loadInstructionNodesFrom (controlPath, &narray);
	if (narray.size() > 0) {
		std::cout << "Started Indexus with " << narray.size() << " nodes.\n";
	  // Run the program we prepared
		run (startPointer, &narray);
	} else {
		std::cout << "Zero nodes found. Leaving.\n";
	}
	return 0;
}
