#include <iostream>
#include "System.h"
#include "/public/read.h"
using namespace std;

int main () {
    System Sys;
    srand(time(0)); // Initialize random seed

    // Add some initial particles to the system
    Sys.addParticle(Particle(10, 10, 1, 1, 50, 255, 0, 0, Particle::STREAMER));
    Sys.addParticle(Particle(20, 20, -1, -1, 50, 0, 255, 0, Particle::BALLISTIC));
    Sys.addParticle(Particle(30, 30, 0, 0, 10, 0, 0, 255, Particle::FIREWORK));

    while (true) {
        int choice = read("1. Run Tests\n2. Add a particle\n3. Draw particles\n4. Run Physics\n5. Run Simulation\n0. Quit\nChoose an option: ");
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
            cout << "Physics updated." << endl;
        }
        // Run Simulation with preset particles
        else if (choice == 5) {
            // Run the simulation for a specified number of iterations
            int iterations = read("Enter number of iterations for the simulation: ");
            for (int i = 0; i < iterations; ++i) {
                clearscreen();
                Sys.sysUpdate();
                for (Cell *currNode = Sys.get_head(); currNode; currNode = currNode->getNext()) {
                    Sys.drawParticle(currNode->particle); // Use the new public method
                }
                usleep(100000); // Sleep for 100 milliseconds
            }
        }
        // Quit
        else if (choice == 0) {
            cout << "Quitting." << endl;
            break;
        }
        // Wrong input
        else {
            cout << "That was not an option. Please try again." << endl;
            continue;
        }
    }
}
