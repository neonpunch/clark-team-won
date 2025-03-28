#include <iostream>
#include "Ishan.h"
#include "Milo.h"
#include "Parker.h"
#include "Nevan.h"
#include "System.h"
#include "/public/read.h"
using namespace std;

int main () {
    System Sys;
    srand(time(0)); // Initialize random seed


	// Debugger to check what the val of scrnWidth and what the val of scrnHeight is
	//cout << "term columns: \n" << Sys.get_scrnWidth() << endl << "term rows: \n" << Sys.get_scrnHeight() << endl;
    // Initial particles to test physics
    //Sys.addParticle(Particle(10, 10, 1, 1, 50, 255, 0, 0, Particle::STREAMER));
    //Sys.addParticle(Particle(20, 20, -1, -1, 50, 0, 255, 0, Particle::BALLISTIC));
    //Sys.addParticle(Particle(30, 30, 0, 0, 10, 0, 0, 255, Particle::FIREWORK));

    while (true) {
		cout << endl;
        int choice = read("1. Run Tests\n2. Add Particle\n3. Draw Particles\n4. Run Physics\n5. Run Sim\n6. Run Parker.h\n7. Run Nevan.h\n8. Run Ishan.h\n9. Run Milo.h\n0. Quit\nChoose an option: ");
        cout << endl;

        // Run Tests
        if (choice == 1) {
            testCell();
            Particle dummy;
            dummy.testParticle();
            Sys.testSystem();
            cout << testGraphics() << endl;
        }
        // Add a particle
        else if (choice == 2) {
            double yIn = read("Enter the particle's y coordinate: "); //Had to swap the var name for this and the below variable
            double xIn = read("Enter the particle's x coordinate: "); //bc the particle wouldn't print when past halfway towards the right side of the screen.
            double dxIn = read("Enter the particle's x velocity: ");
            double dyIn = read("Enter the particle's y velocity: ");
            int lifetimeIn = read("Enter the particle's lifetime: ");
            int redIn = read("Enter the particle's red value: ");
            int greenIn = read("Enter the particle's green value: ");
            int blueIn = read("Enter the particle's blue value: ");
			cout << endl;
            cout << "Select Particle Type: \n1. STREAMER\n2. BALLISTIC\n3. FIREWORK\n4. MOSQUITO\n";
            int typeChoice = read("Enter choice: ");
            Particle::ParticleType type;
            if (typeChoice == 1) {
                type = Particle::STREAMER;
            } else if (typeChoice == 2) {
                type = Particle::BALLISTIC;
            } else if (typeChoice == 3) {
                type = Particle::FIREWORK;
            } else {
				type = Particle::MOSQUITO;
			}
            Particle temp = Particle(xIn, yIn, dxIn, dyIn, lifetimeIn, redIn, greenIn, blueIn, type);
            Sys.addParticle(temp);
			cout << endl;
            cout << "Added a particle." << endl;
        }
        // Draw Particles
        else if (choice == 3) {
            if (!(Sys.get_head())) {
                cout << "There are no particles to draw." << endl;
                continue;
            }
            clearscreen();
            for (Cell *currNode = Sys.get_head(); currNode; currNode = currNode->getNext()) {
                Sys.drawParticle(currNode->particle); // Use the new public method
            }
        }
        // Update Physics
        else if (choice == 4) {
            if (!(Sys.get_head())) {
                cout << "There are no particles to update." << endl;
                continue;
            }
            Sys.sysUpdate(); // Updated to call sysUpdate() instead of iterating manually
        }
        // Run Simulation with preset particles
        else if (choice == 5) {
            // Run the simulation for a specified number of iterations
            int iterations = read("Enter number of iterations for the simulation: ");
			show_cursor(false);
            for (int i = 0; i < iterations; ++i) {
                clearscreen();
                Sys.sysUpdate();
                for (Cell *currNode = Sys.get_head(); currNode; currNode = currNode->getNext()) {
                    Sys.drawParticle(currNode->particle); // Use the new public method
                }
                usleep(100000); // Sleep for 100 milliseconds
            }
			clearscreen();
			show_cursor(true);
         }
		else if (choice == 6) {
			clearscreen();
			GasClouds(Sys);
			clearscreen();
		}
		else if (choice == 7) {
			clearscreen();
			bane_of_Saitama(Sys);
		}
		else if (choice == 8) {
			clearscreen();
			IA project;
			project.makeFirework(Sys);
			project.sim(Sys);
			clearscreen();
		}
		else if (choice == 9) {
			clearscreen();
			BigBayBoom(Sys);
			clearscreen();
		}
        // Quit
        else if (choice == 0) {
            cout << "Quitting." << endl;
			clearscreen();
			show_cursor(true);
            break;
        }
        // Wrong input
        else {
            cout << "That was not an option. Please try again." << endl;
            continue;
        }
    }
}
