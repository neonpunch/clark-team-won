#include <string>

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