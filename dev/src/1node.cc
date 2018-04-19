#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<string>

using namespace std;

class Node {
public:
	string data;
	int pointer;
public:
	Node (string, int);
};

Node::Node (string d, int p) {
	data=d;
	pointer=p;
}
