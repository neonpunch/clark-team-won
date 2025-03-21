#include "Particle.h"
#include "Cell.h"
#include "Graphics.h"
#include "/public/colors.h"
using namespace std;

class System {
    Cell *head = nullptr;
    Cell *tail = nullptr;
    Graphics g;
    int scrnWidth = 0;
    int scrnHeight = 0;
    int partCount = 0;
    // srand(time(0)); // Removed from here and added to main()
    string pSymbol = "*";
    double FPS = 60.;

public: 
    System(Cell *new_head = nullptr, Cell *new_tail = nullptr, int new_partCount = 0) {
        head = new_head;
        tail = new_tail;
        partCount = new_partCount;
        const auto [ROWS, COLS] = get_terminal_size();
        scrnWidth = COLS;
        scrnHeight = ROWS;
        scrnHeight--;
        scrnWidth--;
    }

    ~System() {
        for (Cell *temp = head; temp; ) {
            Cell *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
    }

    void set_head(Cell *new_head) {
        head = new_head;
    }

    Cell *get_head() const {
        return head;
    }

    void set_tail(Cell *new_tail) {
        tail = new_tail;
    }

    Cell *get_tail() const {
        return tail;
    }

    void set_partCount(int new_partCount) {
        partCount = new_partCount;
    }

    int get_partCount() const {
        return partCount;
    }

    void addParticle(Particle p) {
        Cell* temp = new Cell(p, tail, nullptr);
        if (tail) tail->next = temp;
        tail = temp;
        if (partCount == 0) head = tail;
        partCount++;
    }

    int numParticles() {
        return partCount; // Updated to return actual particle count
    }

void sysUpdate() {
    Cell *currNode = head;
    while (currNode) {
        Cell *nextNode = currNode->getNext(); // Save the next node before potentially deleting the current node
        currNode->particle.Physics();
        double x = currNode->particle.get_x();
        double y = currNode->particle.get_y();
        if ((x < 0 or x > scrnWidth) or (y < 0 or y > scrnHeight) or currNode->particle.get_lifetime() == 0) {
            if (currNode->prev) currNode->prev->next = currNode->next;
            if (currNode->next) currNode->next->prev = currNode->prev;
            if (currNode == head) head = currNode->next;
            if (currNode == tail) tail = currNode->prev;
            delete currNode;
            partCount--;
        } else {
            drawParticle(currNode->particle);
        }
        currNode = nextNode; // Move to the next node
    }
}

    void drawParticle(const Particle &p) {
        g.drawPoint(p.get_y(), p.get_x(), p.get_r(), p.get_g(), p.get_b());
    }

  void testSystem() {
    System s;
    bool passed = true;

    if (s.get_head() != nullptr) {
        cout << "Head bad" << endl;
        passed = false;
    } 

    if (s.get_tail() != nullptr) {
        cout << "Tail bad" << endl;
        passed = false;
    }

    if (s.get_partCount() != 0) {
        cout << "PartCount bad" << endl;
        passed = false;
    } 

    s.set_partCount(666);
    if (s.get_partCount() != 666) {
        cout << "Setting or getting partCount is bad" << endl;
        passed = false;
    }

    if (passed) {
        cout << "System.h passed all tests!" << endl;
    } else {
        cout << "System.h did not pass all tests." << endl;
    }
  }  
};
