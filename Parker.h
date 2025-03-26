#include "System.h"

//Parker's gas project

static void GasClouds(System &Controller) {
	int verticalThird = Controller.get_scrnHeight() / 3;
	int horizontalFifth = Controller.get_scrnWidth() / 5;
	//make all the particles at random parts near the bottom, maybe make smokestacks another day 
	for (int i = 0; i < 120; i++) {
		Controller.addParticle(Particle( ( horizontalFifth + (rand() % (3 * horizontalFifth))  ), ( (2 * verticalThird) + (rand() % verticalThird)  ) , 0 , (((rand() % 5) + 1) / 5), 500, 50 + (rand() % 15) - 7, 200 + (rand() % 56), 20, Particle::GAS));
		Controller.sysUpdate();	
	}
}



