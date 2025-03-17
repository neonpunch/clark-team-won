#include "Particle.h"
#include "Cell.h"
#include "Graphics.h"
#include "/public/colors.h"
using namespace std;

class System {
	Cell *head = nullptr;
	Cell *tail = nullptr;
	int scrnWidth = 0;
	int scrnHeight = 0;
	int partCount = 0;

	public: 
	System(Cell *new_head = nullptr, Cell *new_tail = nullptr, int new_partCount = 0) {
		head = new_head;
		tail = new_tail;
		partCount = new_partCount;
		const auto [ROWS, COLS] = get_terminal_size();
		scrnWidth = COLS;
		scrnHeight = ROWS;
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

	void add(Particle p) {

		return;
	}

	int numParticles() {

		return 0;
	}

	void drawParticles(gc g) {

		return;
	}

	void moveParticles() {

		return;
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
			cout << "Set or Get PartCount Bad Dumb Bitch" << endl;
			passed = false;
		}

		Cell *a = new Cell("a");
		s.set_head(a);
		s.set_tail(a);
		if (s.get_head()->particle != "a" or s.get_tail()->particle != "a") {
		 	cout << "Set Head or Set Tail or Get Head or Get Tail is Bad" << endl;
			passed = false;
		}

		delete a;

		if (passed) {
			cout << "System.h passed all tests!" << endl;
		} else {
			cout << "Gappy student, huh?" << endl;
		}
	}
		
};

