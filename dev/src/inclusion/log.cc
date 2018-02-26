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
#include <ctime>
using namespace std;

string timing () {
	auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H.%M.%S");
  return oss.str();
}

string formatForLogFile (string tx) {
	string timingPoint = "[" + timing() + "]";
	string middleSect = " Indexus -> ";
	string content = tx;
	string finall = timingPoint + middleSect + content;
	return finall;
}

void log (string tx) {
	ofstream logfile;
	logfile.open ("indexus.log");
	string ftx = formatForLogFile (tx);
	logfile << ftx << "\n";
	logfile.close ();
}
