#include <string>
#include <iostream>

void die(const std::string &s) {
    std::cout << s << std::endl;
    exit(1);    
}


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
};
	std::string CellTester() {
        //std::cout << "This test will check to see if the Cell objects work as intended (a node in a doubly linked list)." << std::endl;

        //std::cout << "adding the first node..." << std::endl;
        Cell* firstNode = new Cell("First node");
        if (firstNode->particle != "First node") die("One parameter constructor is broken.");
    
        //std::cout << "adding the second node..." << std::endl;
        Cell* secondNode = new Cell("Second node", firstNode);
        firstNode->next = secondNode; //make firstnode point to secondnode now that it exists
        if (firstNode->next != secondNode) die("Setting the next pointer value of a node to another node does not work.");

        //std::cout << "printing out the sequence of two nodes:" << std::endl;
        //std::cout << firstNode->particle << std::endl;
        //std::cout << "again, but from secondNode's pointer: " << secondNode->prev->particle << std::endl;
        if (secondNode->prev->particle != "First node") die("Retrieving the string in the previous node using another node as reference did not work.");
		if (firstNode->next->particle != "Second node") die("Pointer from the first node to the second node was not set.");
        //std::cout << firstNode->next->particle << std::endl;

        //std::cout << "adding the third and final node..." << std::endl;
        Cell* thirdNode = new Cell("Third node", nullptr, firstNode);
        firstNode->prev = thirdNode;
        if (secondNode->prev->prev->particle != "firstNode") die("could read the first item using the last item as reference.");
        //std::cout << "Outputting the completed list:" << std::endl;
        //for (Cell* temp = thirdNode; temp; temp = temp->next) 
            //std::cout << temp->particle << std::endl;

        //}
		return "Cell.h passed all tests!";
		}

