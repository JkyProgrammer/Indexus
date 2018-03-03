#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

std::map<string, string> vars;

void setValue (string key, string value) {
  vars.insert (std::pair<string,string>(key, value));
}

string getValue (string key) {
  return vars.at (key);
}

void removeKeyValPair (string key) {
  vars.erase (key);
}
