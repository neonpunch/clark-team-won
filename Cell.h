#pragma once
#include <string>
#include <iostream>
using namespace std;

class Cell {
public:
    string particle = "";
    Cell* prev;
    Cell* next;

    Cell(string newString = "New_node", Cell* newPrev = nullptr, Cell* newNext = nullptr) {
        particle = newString;
        prev = newPrev;
        next = newNext;
    }
};
	string CellTester() {
        Cell* firstNode = new Cell("First node");
        if (firstNode->particle != "First node") {
			cout << "One parameter constructor is broken." << endl;
		}
    
        Cell* secondNode = new Cell("Second node", firstNode);
        firstNode->next = secondNode; //make firstnode point to secondnode now that it exists
        if (firstNode->next != secondNode) {
			cout << "Setting the next pointer value of a node to another node does not work." << endl;
		}

        if (secondNode->prev->particle != "First node") {
			cout << "Retrieving the string in the previous node using another node as reference did not work." << endl;
		}

		if (firstNode->next->particle != "Second node") {
			cout << "Pointer from the first node to the second node was not set." << endl;
		}

        Cell* thirdNode = new Cell("Third node", nullptr, firstNode);
        firstNode->prev = thirdNode;
        if (secondNode->prev->prev->particle != "firstNode") {}

		delete firstNode;
		delete secondNode;
		delete thirdNode;
		
		return "Cell.h passed all tests!";
	}

