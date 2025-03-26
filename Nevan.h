#pragma once
#include "Particle.h"
#include "System.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <numbers>
#include <climits>
#include <vector>
#include <unistd.h>
using namespace std;


// Nevan's Elemental project
// Master of all four physics
// But when the world needed smoke
// It vanished

/*void createZap(System& slurp, Cell* currNode){
	for (int i = 0; i < 10; ++i) {
		double angle = (rand() % 360) * (numbers::pi / 180.0);
		double speed = 1.5;
		double new_dx = speed * cos(angle);
		double new_dy = speed * sin(angle);
		Particle newParticle(currNode->particle.get_x(), currNode->particle.get_y(), new_dx, new_dy, INT_MAX, currNode->particle.get_r(), currNode->particle.get_g(), currNode->particle.get_b(), Particle::STREAMER);
		slurp.addParticle(newParticle);
	}
}*/

void zapUpdate(System& slurp) { // Modified sysUpdate to avoid Merge conflicts and call conflicts
	Cell *currNode = slurp.get_head();
	while (currNode) {
		Cell *nextNode = currNode->getNext(); // Save the next node before potentially deleting the current node
		currNode->particle.Physics(); // Physics update

		double x = currNode->particle.get_x();
		double y = currNode->particle.get_y();

		const auto [rows, cols] = get_terminal_size();
		int zapperWidth = cols / 8;
		int zapperHeight = rows / 2;
		int zapper_x = (cols - zapperWidth) / 2;
		int zapper_y = (rows - zapperHeight) / 2;

        // Use the correct screen width and height references
        int scrnWidth = slurp.get_scrnWidth();
        int scrnHeight = slurp.get_scrnHeight();

        // Check for culling conditions
        if ((x < 0 || x > scrnWidth) || (y < 0 || y > scrnHeight) || currNode->particle.get_lifetime() == 0) {
            // Explosion logic for FIREWORK particles
            if (currNode->particle.get_type() == Particle::MOSQUITO || currNode->particle.get_lifetime() == 0) {
                // Create explosion particles
                for (int i = 0; i < 10; ++i) {
                    double angle = (rand() % 360) * (numbers::pi / 180.0);
                    double speed = 1.5;
                    double new_dx = speed * cos(angle);
                    double new_dy = speed * sin(angle);
                    Particle newParticle(currNode->particle.get_x(), currNode->particle.get_y(),
                                         new_dx, new_dy, INT_MAX,
                                         currNode->particle.get_r(), currNode->particle.get_g(), currNode->particle.get_b(),
                                         Particle::STREAMER);
                    slurp.addParticle(newParticle);
                }
            }
            // Remove the current node from the list and delete it
            if (currNode->prev) currNode->prev->next = currNode->next;
            if (currNode->next) currNode->next->prev = currNode->prev;
            if (currNode == slurp.get_head()) slurp.set_head(currNode->next);
            if (currNode == slurp.get_tail()) slurp.set_tail(currNode->prev);
            delete currNode;
            slurp.set_partCount(slurp.get_partCount() - 1);
        } else {
            slurp.drawParticle(currNode->particle); // Draw the particle if it's not culled
        }
        currNode = nextNode; // Move to the next node
    }
}

void bane_of_Saitama(System& slurp) {
	for (int m = 0; m < 10; ++m){
		int startX = (slurp.get_scrnWidth() / 2) + m;
		int startY = (slurp.get_scrnHeight() / 2) + m;
    Particle Bzzzt(startX, startY, 1, 1, rand() % 255, rand() % 255, rand() % 255, 0, Particle::MOSQUITO);
    slurp.addParticle(Bzzzt);
	}

    show_cursor(false);
    
    for (int i = 0; i < 300; ++i) {
        clearscreen();

        zapUpdate(slurp);
        for (Cell* currNode = slurp.get_head(); currNode; currNode = currNode->getNext()) {
            slurp.drawParticle(currNode->particle);
        }

        usleep(30000); // Sleep for 30 milliseconds
    }

    clearscreen();
    show_cursor(true);
}

/*void bug_zapper(System& slurp, std::vector<Particle>& zapperParticles){
    const auto [rows, cols] = get_terminal_size();
    int zapperWidth = cols / 8;
    int zapperHeight = rows / 2;
    int x = (cols - zapperWidth) / 2;
    int y = (rows - zapperHeight) / 2;

    show_cursor(false);
    clearscreen();

	zapperParticles.clear();

    int temp_x = x;
    for (int k = 0; k < zapperWidth; ++k){
        int temp_y = y;

        for (int l = 0; l < zapperHeight; ++l){
            Particle zapperElectric(temp_x, temp_y, 0, 0, 500, 125, 249, 255, Particle::STREAMER); // Makes Solid Blue Electricity for Zapper
            slurp.addParticle(zapperElectric);
			zapperParticles.push_back(zapperElectric);
            temp_y += 1;
        }
        temp_x += 1;
    }
	for (const auto& particle : zapperParticles){
		slurp.drawParticle(particle);
	}

}
*/
