#include "Particle.h"
#include "Cell.h"
#include "Graphics.h"
#include "/public/colors.h"
#include <climits>
using namespace std;

class System {
    Cell *head = nullptr;
    Cell *tail = nullptr;
    Graphics g;
    int scrnWidth = 0;
    int scrnHeight = 0;
    int partCount = 0;
    double FPS = 90.;

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

	int get_scrnWidth() const {
		return scrnWidth;
	}
	int get_scrnHeight() const {
		return scrnHeight;
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
        currNode->particle.Physics(); // Physics update

        double x = currNode->particle.get_x();
        double y = currNode->particle.get_y();

        // Check for culling conditions
        if ((x < 0 or x > scrnWidth) or (y < 0 or y > scrnHeight) or currNode->particle.get_lifetime() == 0) {
            // Explosion logic for FIREWORK particles
            if (currNode->particle.get_type() == Particle::FIREWORK && currNode->particle.get_lifetime() == 0) {
                // Create explosion particles
                for (int i = 0; i < 10; ++i) {
                    double angle = (rand() % 360) * (numbers::pi / 180.0);
                    double speed = 1.5;
                    double new_dx = speed * cos(angle);
                    double new_dy = speed * sin(angle);
                    Particle newParticle(currNode->particle.get_x(), currNode->particle.get_y(), new_dx, new_dy, INT_MAX, currNode->particle.get_r(), currNode->particle.get_g(), currNode->particle.get_b(), Particle::STREAMER);
                    addParticle(newParticle);
                }
            }
            // Remove the current node from the list and delete it
            if (currNode->prev) currNode->prev->next = currNode->next;
            if (currNode->next) currNode->next->prev = currNode->prev;
            if (currNode == head) head = currNode->next;
            if (currNode == tail) tail = currNode->prev;
            delete currNode;
            partCount--;
        } else {
            drawParticle(currNode->particle); // Draw the particle if it's not culled
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
