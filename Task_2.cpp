#include <iostream>
#include <string>
#include <list>
#include "brickSorter.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
    string filePath = argv[1];
    run(filePath, true);
}