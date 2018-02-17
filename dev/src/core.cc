#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<string>
#include<iostream>
#include<pthread.h>
#include<map>
#include<vector>
#include<sstream>
#include<algorithm>
#include<iterator>

using namespace std;

class Node {
 public:
  int name;
  string data;
  int pointer;
 public:
  Node (int, string, int);
};

Node::Node (int n, string d, int p) {
 name=n;
 data=d;
 pointer=p;
}

template<typename Out>
void split (const std::string &s, char delim, Out result) {
 std::stringstream ss(s);
 std::string item;
 while (std::getline(ss,item,delim)) {
  *(result++) = item;
 }
}

std::vector<std::string> split (const std::string &s, char delim) {
 std::vector<std::string> elems;
 split(s, delim, std::back_inserter(elems));
 return elems;
}

vector<Node*> narray;

int toInt (string in) {
	int val = 0;
	stringstream converter(in);
	converter >> val;
	return val;
}

int rega = 0;
int regb = 0;
int regc = 0;
int regd = 0;
int rege = 0;
int regf = 0;
int regg = 0;
int regh = 0;

void interpret (string instruction) {
 std::vector<string> splitInstr = split (instruction, '~');
 string instr = splitInstr.at(0);
 if (instr.compare ("cout") == 0) {
   std::cout << splitInstr.at(1) << "\n";
 } else if (instr.compare ("movt") == 0) {
	 //std::cout << splitInstr.at(1) << "\n";
	 string reg = splitInstr.at(1);
	 int x = toInt (splitInstr.at(2));
	 if (reg.compare("rega")) {
		 rega = x;
	 } else if (reg.compare("regb")) {
		 regb = x;
	 } else if (reg.compare("regc")) {
		 regc = x;
	 } else if (reg.compare("regd")) {
		 regd = x;
	 } else if (reg.compare("rege")) {
		 rege = x;
	 } else if (reg.compare("regf")) {
		 regf = x;
	 } else if (reg.compare("regg")) {
		 regg = x;
	 } else if (reg.compare("regh")) {
		 regh = x;
	 }
 } else if (instr.compare ("incr") == 0) {
         string reg = splitInstr.at(1);
	 //int x = toInt (splitInstr.at(2));
	 if (reg.compare("rega")) {
		 rega++;
	 } else if (reg.compare("regb")) {
		 regb++;
	 } else if (reg.compare("regc")) {
		 regc++;
	 } else if (reg.compare("regd")) {
		 regd++;
	 } else if (reg.compare("rege")) {
		 rege++;
	 } else if (reg.compare("regf")) {
		 regf++;
	 } else if (reg.compare("regg")) {
		 regg++;
	 } else if (reg.compare("regh")) {
		 regh++;
	 }
 } else if (instr.compare ("cmpr") == 0) {
  
 }
}

int namePointer = 1;

bool shouldContinueExecuting = true;

int getNodeWithName (int nam) {
 int ret = 0;
 for (int index=0; index < narray.size(); index++) {
  if ((narray [index] -> name) == nam) {
   ret = index;
  }
 }
 return ret;
}

int main () {
 //std::cout << "Hi there, User.\n";
 //std::cout << "I’m Indexus.\n";
 // Start process
 //
 //Node* newNode = ;
 std::cout << "Here we go.\n";
 narray.push_back(new Node(1, "cout~Hi there, User.", 2));
 narray.push_back(new Node(2, "cout~I'm Indexus", 5));
 narray.push_back(new Node(5, "cout~Printing myself!", 3));
 narray.push_back(new Node(3, "cout~Looping...", 3));

 while (shouldContinueExecuting) {
  // Get by name
  if (namePointer != 0) {
   int index = getNodeWithName(namePointer);
   Node* n = narray [index];
   interpret (n -> data);
   namePointer = (n -> pointer);
  } else {
   shouldContinueExecuting = false;
  }
 }
 return 0;
}
