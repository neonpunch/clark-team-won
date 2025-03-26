#pragma once
#include "System.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <numbers>
#include <climits>
#include <unistd.h>


// Nevan's Elemental project
// Master of all four physics
// But when the world needed smoke
// It vanished

void createZap(System& slurp, Cell* currNode){
    for (int i = 0; i < 10; ++i) {
        double angle = (rand() % 360) * (numbers::pi / 180.0);
        double speed = 1.5;
        double new_dx = speed * cos(angle);
        double new_dy = speed * sin(angle);
        Particle newParticle(currNode->particle.get_x(), currNode->particle.get_y(), new_dx, new_dy, INT_MAX, currNode->particle.get_r(), currNode->particle.get_g(), currNode->particle.get_b(), Particle::STREAMER);
        slurp.addParticle(newParticle);
    }
}

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

        // Check for culling conditions
        if ((x >= zapper_x && x <= zapper_x + zapperWidth) && (y >= zapper_y && y <= zapper_y + zapperHeight)){
            createZap(slurp, currNode);

            if (currNode == slurp.get_head()) slurp.set_head(currNode->getNext());
            if (currNode == slurp.get_tail()) slurp.set_tail(currNode->getPrev());
            delete currNode;
            slurp.set_partCount(slurp.get_partCount() - 1);
        }

        // Explosion logic for FIREWORK particles
        else if (currNode->particle.get_type() == Particle::FIREWORK && currNode->particle.get_lifetime() == 0) {
            // Create explosion particles
            createZap(slurp, currNode);

            if (currNode == slurp.get_head()) slurp.set_head(currNode->getNext());
            if (currNode == slurp.get_tail()) slurp.set_tail(currNode->getPrev());
            delete currNode;
            slurp.set_partCount(slurp.get_partCount() - 1);
        }

        else if ((x < 0 || x > slurp.get_scrnWidth()) || (y < 0 || y > slurp.get_scrnHeight()) || currNode->particle.get_lifetime() == 0) {
            if (currNode == slurp.get_head()) slurp.set_head(currNode->getNext());
            if (currNode == slurp.get_tail()) slurp.set_tail(currNode->getPrev());
            delete currNode;
            slurp.set_partCount(slurp.get_partCount() - 1);
        }

        // Remove the current node from the list and delete it
        else {
            slurp.drawParticle(currNode->particle); // Draw the particle if it's not culled
        }
        currNode = nextNode; // Move to the next node
    }
}

void bug_zapper(System& slurp){
	const auto [rows, cols] = get_terminal_size();
	int zapperWidth = cols / 8;
	int zapperHeight = rows / 2;
	int x = (cols - zapperWidth) / 2;
	int y = (rows - zapperHeight) / 2;

	for (int k = 0; k < zapperWidth; k++){
		int temp_y = y;

		for (int l = 0; l < zapperHeight; l++){
			Particle zapperElectric(x, temp_y, 0, 0, INT_MAX, 125, 249, 255, Particle::STREAMER); // Makes Solid Blue Electricity for Zapper
			slurp.addParticle(zapperElectric);
			slurp.drawParticle(zapperElectric);
			temp_y += 1;
		}
		x += 1;
	}
	for (int i = 0; i < zapperWidth; i++){ // Sets X Frames
		Particle topFrame(x + i, y, 0, 0, INT_MAX, 192, 192, 192, Particle::STREAMER);
		slurp.addParticle(topFrame);
		slurp.drawParticle(topFrame);

		Particle botFrame(x + i, y + zapperHeight - 1, 0, 0, INT_MAX, 192, 192, 192, Particle::STREAMER);
		slurp.addParticle(botFrame);
		slurp.drawParticle(botFrame);
	}
	for (int j = 0; j < zapperHeight; j++){ // Sets Y Frames
		Particle leftFrame(x, y + j, 0, 0, INT_MAX, 192, 192, 192,Particle::STREAMER);
		slurp.addParticle(leftFrame);
		slurp.drawParticle(leftFrame);

		Particle rightFrame(x + zapperWidth - 1, y + j, 0, 0, INT_MAX, 192, 192, 192, Particle::STREAMER);
		slurp.addParticle(rightFrame);
		slurp.drawParticle(rightFrame);
	}
	Particle Bzzzt(rand() % cols, rand() % rows, 10000, 10000, 200, 255, 85, 0, Particle::MOSQUITO);
	slurp.addParticle(Bzzzt);
	slurp.drawParticle(Bzzzt);

	int iterations = 500;

	show_cursor(false);
	for (int i = 0; i < iterations; ++i) {
                clearscreen();
                zapUpdate(slurp);
                for (Cell *currNode = slurp.get_head(); currNode; currNode = currNode->getNext()) {
                    slurp.drawParticle(currNode->particle); // Use the new public method
                }
                usleep(100000); // Sleep for 100 milliseconds
            }
			clearscreen();
			show_cursor(true);
         }



