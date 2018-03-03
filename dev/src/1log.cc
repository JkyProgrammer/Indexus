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
#include <streambuf>
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

int getRunCount () {
	std::ifstream t("logs/runcounter");
	std::stringstream buffer;
	buffer << t.rdbuf();
	string oldContent = buffer.str();
	int val = toInt(oldContent);
	return val;
}

void incrementRunCount () {
	int oldRC = getRunCount ();
	ofstream rcf;
	rcf.open ("logs/runcounter");
	string newVal = to_string(oldRC + 1);
	rcf << newVal;
	rcf.close ();
}

void log (string tx) {
	ofstream logfile;

	//std::ifstream oldContentF("indexus.log");
	//std::string oldContent((std::istreambuf_iterator<char>(oldContentF)), std::istreambuf_iterator<char>());
	string rc = std::to_string(getRunCount());
	std::ifstream t("logs/indexus-" + rc +".log");
	std::stringstream buffer;
	buffer << t.rdbuf();
	string oldContent = buffer.str();
	logfile.open ("logs/indexus-" + rc +".log");
	string ftx = formatForLogFile (tx);
	logfile << (oldContent + ftx + "\n");
	logfile.close ();
}
