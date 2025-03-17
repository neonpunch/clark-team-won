#include <string>
#include <iostream>
using namespace std;

class Cell {
public:
    std::string particle = "";
    Cell* prev;
    Cell* next;

    Cell(std::string newString = "New_node", Cell* newPrev = nullptr, Cell* newNext = nullptr) {
        particle = newString;
        prev = newPrev;
        next = newNext;
    }

    void CellTester() {
        cout << "This test will check to see if the Cell objects work as intended (a node in a doubly linked list)." << endl;

        cout << "adding the first node..." << endl;
        Cell* firstNode = new Cell("First node");
    
        cout << "adding the second node..." << endl;
        Cell* secondNode = new Cell("Second node", firstNode);
        firstNode->next = secondNode; //make firstnode point to secondnode now that it exists

        cout << "printing out the sequence of two nodes:" << endl;
        cout << firstNode->particle << endl;
        cout << "again, but from secondNode's pointer: " << secondNode->prev->particle << endl;
        cout << firstNode->next->particle << endl;

        cout << "adding the third and final node..." << endl;
        Cell* thirdNode = new Cell("Third node", nullptr, firstNode);
        firstNode->prev = thirdNode;

        cout << "Outputting the completed list:" << endl;
        for (Cell* temp = thirdNode; temp; temp = temp->next) 
            cout << temp->particle << endl;

        }
};
