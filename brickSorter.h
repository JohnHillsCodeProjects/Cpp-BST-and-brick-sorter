#pragma once
#include <string>
#include <map>
#include <list>

using std::string;

bool readFiles(string, std::map<string, string>*, std::map<string, string>*);
void sortBricks(std::map<string, string>, std::map<string, string>, std::list<string>*);
void run(string, bool);