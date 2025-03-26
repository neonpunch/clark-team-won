#pragma once
#include "System.h"
#include <iostream>
#include <unistd.h>


// Nevan's Elemental project
// Master of all four physics
// But when the world needed smoke
// It vanished

void bug_zapper(){
	const auto [rows, cols] = get_terminal_size();
	int zapperWidth = cols / 8;
	int zapperHeight = rows / 2;
	int x = (cols - zapperWidth) / 2;
	int y = (rows - zapperHeight) / 2;

	for (int k = 0; k < zapperWidth; k++){
		int temp_y = y;

		for (int l = 0; l < zapperHeight; l++){
			Particle zapperElectric(x, temp_y, 0, 0, INT_MAX, 125, 249, 255, Particle::STREAMER); // Makes Solid Blue Electricity for Zapper
			addParticle(zapperElectric);
			drawParticle(zapperElectric);
			temp_y += 1;
		}
		x += 1;
	}
	for (int i = 0; i < zapperWidth; i++){ // Sets X Frames
		Particle topFrame(x + i, y, 0, 0, INT_MAX, 192, 192, 192, Particle::STREAMER);
		addParticle(topFrame);
		drawParticle(topFrame);

		Particle botFrame(x + i, y + zapperHeight - 1, 0, 0, INT_MAX, 192, 192, 192, Particle::STREAMER);
		addParticle(botFrame);
		drawParticle(botFrame);
	}
	for (int j = 0; j < zapperHeight; j++){ // Sets Y Frames
		Particle leftFrame(x, y + j, 0, 0, INT_MAX, 192, 192, 192,Particle::STREAMER);
		addParticle(leftFrame);
		drawParticle(leftFrame);

		Particle rightFrame(x + zapperWidth - 1, y + j, 0, 0, INT_MAX, 192, 192, 192, Particle::STREAMER);
		addParticle(rightFrame);
		drawParticle(rightFrame);
	}

}

void createZap(Cell* currNode){
	for (int i = 0; i < 10; ++i) {
		double angle = (rand() % 360) * (numbers::pi / 180.0);
		double speed = 1.5;
		double new_dx = speed * cos(angle);
		double new_dy = speed * sin(angle);
		Particle newParticle(currNode->particle.get_x(), currNode->particle.get_y(), new_dx, new_dy, INT_MAX, currNode->particle.get_r(), currNode->particle.get_g(), currNode->particle.get_b(), Particle::STREAMER);
		addParticle(newParticle);
	}
}

void zapUpdate() { // Modified sysUpdate to avoid Merge conflicts and call conflicts
	Cell *currNode = head;
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
		if ((x >= zapper_x && x <= zapper_x + zapperWidth) && (y >= zapper_y && y <= zapper_y + zapperHeight){
				createZap(currNode);

				if (currNode == head) head = currNode->next;
				if (currNode == tail) tail = currNode->prev;
				delete currNode;
				partCount--;
				}

				// Explosion logic for FIREWORK particles
				else if (currNode->particle.get_type() == Particle::FIREWORK && currNode->particle.get_lifetime() == 0) {
				// Create explosion particles
				createZap(currNode);

				if (currNode == head) head = currNode->next;
				if (currNode == tail) tail = currNode->prev;
				delete currNode;
				partCount--;
				}

				else if ((x < 0 or x > scrnWidth) or (y < 0 or y > scrnHeight) or currNode->particle.get_lifetime() == 0) {
					if (currNode == head) head = currNode->next;
					if (currNode == tail) tail = currNode->prev;
					delete currNode;
					partCount--;
				}

				// Remove the current node from the list and delete it
		else {
			drawParticle(currNode->particle); // Draw the particle if it's not culled
		}
		currNode = nextNode; // Move to the next node
	}
}
