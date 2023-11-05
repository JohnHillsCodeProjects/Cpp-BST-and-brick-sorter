#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include "brickSorter.h"

using std::cout;
using std::endl;
using std::string;
using std::chrono::steady_clock;
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::duration_cast;

int timingTests()
{
    cout << "Begin timing tests\n";
    long long int results[17][5];
    steady_clock::time_point startTime, finishTime;
    string names[17] = { "20","50","100","200","500","1K","2K","5K","10K","20K","50K","100K","200K","500K","1M","2M","3M" };
    int i, j;
    for (i = 0; i < 17; i++) {
        for (j = 0; j < 5; j++) {
            startTime = steady_clock::now();
            run("Great_Wall_Problem-test_data/" + names[i] + "/input-pairs-" + names[i] + ".txt", false);
            finishTime = steady_clock::now();
            results[i][j] = duration_cast<nanoseconds>(finishTime - startTime).count();
            cout << "Completed " << names[i] << endl;
        }
    }
    std::ofstream csvFile; csvFile.open("task5times.csv");
    csvFile << "Number of pairs,Test 1,Test 2,Test 3,Test 4,Test 5,Lowest time,Highest time,Average time\n";
    for (i = 0; i < 17; i++) {
        csvFile << names[i];
        for (j = 0; j < 5; j++) {
            csvFile << ',' << results[i][j];
        }
        csvFile << '\n';
    }
    cout << "Timing test completed\n";
    return 0;
}

int main() { timingTests(); return 0; }