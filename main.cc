#include <iostream>
#include "System.h"
#include "/public/read.h"
using namespace std;

int main () {
	System s;
	
	while (true) {
		int choice = read("1. Run Tests\n2. Add a particle\n3. Draw particles\n4. Run Physics\n0. Quit\nChoose an option: ");
		cout << endl;

		//Run Tests
		if (choice == 1) {
			testCell();
			testParticle();
			testSystem();
			cout << testGraphics();
		}

		else if (choice == 2) {
			int xIn = read("Enter the particle's x coordinate: ";
			int yIn = read("\nEnter the particle's y coordinate: ";
			int dxIn = read("\nEnter the particle's x velocity: ";
			int dyIn = read("\nEnter the particle's y velocity: ";
			int lifetimeIn = read("\nEnter the particle's lifetime: ";


		}

		else if (choice == 3) {


		}

		else if (choice == 4) {


		}
		//Quit
		else if (choice == 0) {
			break;
		}
		//Wrong input
		else {
			cout << "That was not an option. Please try again." << endl;
			continue;
		}
	}
	
	
}
