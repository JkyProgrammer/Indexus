#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <vector>
#include <sstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <iomanip>
#include <fstream>
using namespace std;

string readContentsOfFile (string path) {
		std::ifstream ifs(path);
  	std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
    return (content);
}

void writeContentToFile (string content, string path) {
	ofstream ofile;
	ofile.open (path);
	ofile << content << "\n";
	ofile.close ();
}

std::string exec(string in) {
	const char* cmd = in.c_str();
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
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

void delay (int x) {
	std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

int toInt (string in) {
	int val = 0;
	stringstream converter(in);
	converter >> val;
	return val;
}
