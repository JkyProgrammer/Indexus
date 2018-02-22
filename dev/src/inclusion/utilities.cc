#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>
#include<string>
#include<iostream>
#include<pthread.h>
#include <chrono>
#include <thread>
#include<vector>
#include<sstream>

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

void delay (int x) {
	std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

int toInt (string in) {
	int val = 0;
	stringstream converter(in);
	converter >> val;
	return val;
}
