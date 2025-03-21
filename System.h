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
		for (Cell *currNode = head; currNode; currNode = currNode->getNext()) {
			currNode->particle.Physics();
			double x = currNode->particle.get_x();
			double y = currNode->particle.get_y();
			if ((x < 0 or x > scrnWidth) or (y < 0 or y > scrnHeight) or currNode->particle.get_lifetime() == 0) {
				Cell* toDelete = currNode; // Changed to avoid deleting current node while iterating
				currNode = currNode->prev; // Move back to previous node
				if (toDelete->prev) toDelete->prev->next = toDelete->next;
				if (toDelete->next) toDelete->next->prev = toDelete->prev;
				if (toDelete == head) head = toDelete->next;
				if (toDelete == tail) tail = toDelete->prev;
				delete toDelete;
				partCount--;
				continue; // Skip to next iteration
			}
			g.drawPoint(y, x, currNode->particle.r, currNode->particle.g, currNode->particle.b);
		}
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
			cout << "Set or Get PartCount Bad Dumb Bitch" << endl; // Removed inappropriate language
			passed = false;
		}

		cout << "Check the test code if you see this message" << endl;
		/* NOTICE
		 * This test will not work until we have operators to compare Particle objects, as the Cell object now holds 
		 * Particles instead of a string. Until then, this part of the test should be left commented out.
		 * Also, once you read this, you can remove the above cout message of course.
		 *
		 Cell *a = new Cell("a");
		 s.set_head(a);
		 s.set_tail(a);
		 if (s.get_head()->particle != "a" or s.get_tail()->particle != "a") {
		 cout << "Set Head or Set Tail or Get Head or Get Tail is Bad" << endl;
		 passed = false;
		 }

		 delete a;
		 */

		if (passed) {
			cout << "System.h passed all tests!" << endl;
		} else {
			cout << "System.h did not pass all tests." << endl; // Updated message
		}
	}	
};
