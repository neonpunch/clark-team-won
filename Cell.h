#pragma once
#include "Particle.h"
#include <string>
#include <iostream>
using namespace std;

class Cell {
public:
    Particle particle;
    Cell* prev = nullptr;
    Cell* next = nullptr;

    Cell(Particle newParticle = Particle(), Cell* newPrev = nullptr, Cell* newNext = nullptr) {
        particle = newParticle;
        prev = newPrev;
        next = newNext;
    }

	Cell *getNext() const {
		return next;
	}
	
	void setNext(Cell *newNext) {
		next = newNext;
	}

	Cell *getPrev() const {
		return prev;
	}

	void setPrev(Cell *newPrev) {
		prev = newPrev;
	}

	Particle getParticle() const {
		return particle;
	}

	void setParticle(Particle newParticle) {
		particle = newParticle;
	}

};
void testCell() {
    bool passed = true;

    Cell* firstNode = new Cell(Particle());
    if (!(firstNode->particle == Particle(0,0,0,0,0,5,5,5))) {
        cout << "Accessing a particle is broken." << endl;
        passed = false;
    }

    Cell* secondNode = new Cell(Particle(12,15,0,0,4,7,8,9), firstNode);
    firstNode->next = secondNode; //make firstnode point to secondnode now that it exists
    if (firstNode->next != secondNode) {
        cout << "Setting the next pointer value of a node to another node does not work." << endl;
        passed = false;
    }

    if (!(secondNode->prev->particle == Particle(0,0,0,0,0))) {
        cout << "Retrieving the particle in the previous node using another node as reference did not work." << endl;
        passed = false;
    }

    if (!(firstNode->next->particle == Particle(12,15,0,0,4,7,8,9))) {
        cout << "Pointer from the first node to the second node was not set." << endl;
        passed = false;
    }

    Cell* thirdNode = new Cell(Particle(30,7,0,0,15,12,0,6), nullptr, firstNode);
    firstNode->prev = thirdNode;
    if (!(secondNode->prev->prev->particle == Particle(30,7,0,0,15,12,0,6))) {
        cout << "Accessing two particles before does not work." << endl;
        passed = false;
    }

    delete firstNode;
    delete secondNode;
    delete thirdNode;

    if (passed) cout << "Cell.h passed all tests!" << endl;
    else cout << "Cell.h did not pass all tests." << endl;
}
