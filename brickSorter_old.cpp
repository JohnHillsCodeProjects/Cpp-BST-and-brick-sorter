/*
#include "brickSorter.h"
#include <fstream>
#include <iostream>
#include <map>
#include <list>

using std::cout;
using std::endl;
using std::string;

bool readFiles(string filePath, std::map<string, string>* left, std::map<string, string>* right)
{
    //left is a dictionary that uses the left side of the brick as a key and the right side as a element
    //right is a dictionary that uses the right side of the brick as a key and the left side as a element

    std::ifstream inputs(filePath);
    if (!inputs) {
        //If no file to load
        return false;
    }
    string brick;
    int len = NULL;
    int i; for (i = 0; !inputs.eof(); i++) {
        getline(inputs, brick);
        if (len == NULL) len = (brick.size() - 1) / 2;
        if (brick.size() != 0) {
            (*left)[brick.substr(0, len)] = brick.substr(len + 1, len);
            (*right)[brick.substr(len + 1, len)] = brick.substr(0, len);
        }
    }
    return true;
}

void sortBricks(std::map<string, string> left, std::map<string, string> right, std::list<string>* sorted)
{
    sorted->push_back(left.begin()->first);
    sorted->push_back(left.begin()->second);
    string leftFind, rightFind;
    //keepLooking determines if the leftmost or right most brick has been found.
    //When the leftmost or rightmost brick locater
    bool keepLooking[2] = { true,true };
    while (keepLooking[0] || keepLooking[1])
    {
        if (keepLooking[0]) {
            leftFind = left[sorted->back()]; //The item at the back of the sorted list will be the key of the next item in left to add
            if (leftFind.size() == 0) {
                keepLooking[0] = false;  //If there are no bricks left to add to the end, don't look for it anymore
            } else {
                sorted->push_back(leftFind); //Otherwise, add the item to the list
            }
        }
        if (keepLooking[1]) {
            rightFind = right[sorted->front()]; //The item at the front of the sorted list will be the key of the next item in right to add
            if (rightFind.size() == 0) {
                keepLooking[1] = false;  //If there are no bricks left to add to the front, don't look for it anymore
            } else {
                sorted->push_front(rightFind); //Otherwise, add the item to the front of the lift to the list
            }
        }
    }
}

void run_old(string filePath, bool withOutput)
{
    //This version is bad to use because it crashes with an error message about "std::bad allocation of memory" and I don't understand it
    std::map <string, string> left, right;
    std::list <string> sorted;
    bool validFilePath = readFiles(filePath, &left, &right);
    if (!validFilePath) {
        cout << "ERROR:\n" << filePath << " is not a valid file path\n";
        return;
    }
    sortBricks(left, right, &sorted);
    if (withOutput) {
        std::list<string>::iterator it = sorted.begin();
        while (it != sorted.end()) { cout << *it << endl; it++; }
    }
}
*/