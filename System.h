//#include "Particle.h"
#include "Cell.h"
//#include "Graphics.h"
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

	//void add(Particle p) {

	//	return;
	//}

	int numParticles() {

		return 0;
	}

	//void drawParticles(Graphics g) {

	//	return;
	//}

	void moveParticles() {

		return;
	}

	void testSystem() {
		System s;

		if (s.get_head() == nullptr) {
			cout << "Test Passed!" << endl;
		} else {
			cout << "Head bad" << endl;
		}

		if (s.get_tail() == nullptr) {
			cout << "Test Passed!" << endl;
		} else {
			cout << "Tail bad" << endl;
		}

		if (s.get_partCount() == 0) {
			cout << "Test Passed!" << endl;
		} else {
			cout << "PartCount bad" << endl;
		} 
		
		s.set_partCount(666);
		if (s.get_partCount() != 666) {
			cout << "Set or Get PartCount Bad Dumb Bitch" << endl;
		} else {
			cout << "Test Passed!" << endl;
		}

		Cell *a = new Cell("a");
		s.set_head(a);
		s.set_tail(a);
		if (s.get_head()->particle != "a" or s.get_tail()->particle != "a") {
		 	cout << "Set Head or Set Tail or Get Head or Get Tail is Bad" << endl;
		} else {
			cout << "Test Passed!" << endl;
		}

		delete a;
	}
		
};

