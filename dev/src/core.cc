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

void interpret (string instruction) {
 std::vector<string> splitInstr = split (instruction, '~');
 if (splitInstr.at (0).compare ("1") == 0) {
  std::cout << splitInstr.at(1) << "\n";
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
 narray.push_back(new Node(1, "1~Hi there, User.", 2));
 narray.push_back(new Node(2, "1~I'm Indexus", 5));
 narray.push_back(new Node(5, "1~Printing myself!", 0));
 
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
