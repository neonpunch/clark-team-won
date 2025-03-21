#include <iostream>
#include "System.h"
#include "/public/read.h"
using namespace std;

int main () {
	System Sys;
	
	while (true) {
		int choice = read("1. Run Tests\n2. Add a particle\n3. Draw particles\n4. Run Physics\n0. Quit\nChoose an option: ");
		cout << endl;

		//Run Tests
		if (choice == 1) {
			testCell();
			Particle dummy;
			dummy.testParticle();

			Sys.testSystem();
			cout << testGraphics();
		}

		else if (choice == 2) {
			int xIn = read("Enter the particle's x coordinate: ");
			int yIn = read("\nEnter the particle's y coordinate: ");
			int dxIn = read("\nEnter the particle's x velocity: ");
			int dyIn = read("\nEnter the particle's y velocity: ");
			int lifetimeIn = read("\nEnter the particle's lifetime: ");

			int redIn = read("\nEnter the particle's red value: ");
			int greenIn = read("\nEnter the particle's green value: ");
			int blueIn = read("\nEnter the particle's blue value: ");

			Particle temp = Particle(xIn,yIn,dxIn,dyIn,lifetimeIn,redIn,greenIn,blueIn);
			Sys.addParticle(temp);
			cout << "Added a particle." << endl;
		}
		//Draw Particles
		else if (choice == 3) {
			if (!(Sys.get_head())) {
				cout << "There are no particles to draw." << endl;
				continue;
			}
		 	for (Cell *currNode = Sys.get_head(); currNode; currNode = currNode->getNext()) {
				Sys.g.drawpoint(currNode->particle.y,currNode->particle.x,currNode->particle.r, currNode->particle.g, currNode->particle.b)
			}

		}
		//Update Physics
		else if (choice == 4) {
			if (!(Sys.get_head())) {
				cout << "There are no particles to update." << endl;
				continue;
			}
			for (Cell *currNode = Sys.get_head(); currNode; currNode = currNode->getNext()) {
				currNode->particle.Physics();
			}
		}
		//Quit
		else if (choice == 0) {
			cout << "Quitting." << endl;
			break;
		}
		//Wrong input
		else {
			cout << "That was not an option. Please try again." << endl;
			continue;
		}
	}
	
	
}
