#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<string>
#include<iostream>
#include<pthread.h>
#include<vector>

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

vector<Node> narray;

int main () {
 std::cout << "Hi there, User\n";
 std::cout << "I’m Indexus.\n";
 // Start process
 //
 narray.push_back(Node(1, "0", 0));
 return 0;
}

