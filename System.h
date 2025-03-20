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
	/* This should be in system.h
	   srand(time(0));
	   auto [rows,cols] = get_terminal_size();
	   rows--;
	   cols--;
	   x = rand() % cols;
	   y = rand() % rows;
	   dx = 1;
	   dy = 1;
	   lifetime = 1440;
	   string pSymbol = "*";
	   double FPS = 144.;
	   for (int i = 0; i < lifetime; i++) {
	   }
	   */

	public: 
	System(Cell *new_head = nullptr, Cell *new_tail = nullptr, int new_partCount = 0) {
		head = new_head;
		tail = new_tail;
		partCount = new_partCount;
		const auto [ROWS, COLS] = get_terminal_size();
		scrnWidth = COLS;
		scrnHeight = ROWS;
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

		return 0;
	}

	void sysUpdate() {
		for (Cell *currNode = head; currNode; currNode = currNode->getNext()) {
			currNode->particle.Physics();
			//Add culling
			g.drawPoint(currNode->particle.y,currNode->particle.x,100,100,100);
			//g.drawPoint(20, 20, 49, 23, 92);
		}
	}

	/*
	   void drawParticles(gc g) {

	   return;
	   }

	   void moveParticles() {

	   return;
	   }
	   */
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
			cout << "Set or Get PartCount Bad Dumb Bitch" << endl;
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
			cout << "Gappy student, huh?" << endl;
		}
	}	
};

