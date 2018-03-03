#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<string>

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
