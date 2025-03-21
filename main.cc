#include <iostream>
#include "System.h"
#include "/public/read.h"
using namespace std;

int main () {
	System Sys;
	srand(time(0)); // Moved srand to main()

	while (true) {
		int choice = read("1. Run Tests\n2. Add a particle\n3. Draw particles\n4. Run Physics\n0. Quit\nChoose an option: ");
		cout << endl;

		//Run Tests
		if (choice == 1) {
			testCell();
			Particle dummy;
			dummy.testParticle();

			Sys.testSystem();
			cout << testGraphics() << endl;
		}

		else if (choice == 2) {
			int xIn = read("Enter the particle's x coordinate: ");
			int yIn = read("Enter the particle's y coordinate: ");
			int dxIn = read("Enter the particle's x velocity: ");
			int dyIn = read("Enter the particle's y velocity: ");
			int lifetimeIn = read("Enter the particle's lifetime: ");

			int redIn = read("Enter the particle's red value: ");
			int greenIn = read("Enter the particle's green value: ");
			int blueIn = read("Enter the particle's blue value: ");

			cout << "Select Particle Type: \n1. STREAMER\n2. BALLISTIC\n3. FIREWORK\n";
			int typeChoice = read("Enter choice: ");
			Particle::ParticleType type;
			if (typeChoice == 1) {
				type = Particle::STREAMER;
			} else if (typeChoice == 2) {
				type = Particle::BALLISTIC;
			} else {
				type = Particle::FIREWORK;
			}

			Particle temp = Particle(xIn, yIn, dxIn, dyIn, lifetimeIn, redIn, greenIn, blueIn, type);
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
				Sys.g.drawPoint(currNode->particle.get_y(), currNode->particle.get_x(), currNode->particle.get_r(), currNode->particle.get_g(), currNode->particle.get_b()); // Fixed method call
			}

		}
		//Update Physics
		else if (choice == 4) {
			if (!(Sys.get_head())) {
				cout << "There are no particles to update." << endl;
				continue;
			}
			Sys.sysUpdate(); // Updated to call sysUpdate() instead of iterating manually
			cout << "Physics updated." << endl;
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
