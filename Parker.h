#include "System.h"

//Parker's gas project

static void GasClouds(System &Controller) {
	Controller.set_FPS(12.);
	show_cursor(false);
	int verticalFourth = Controller.get_scrnHeight() / 4;
	int horizontalEighth = Controller.get_scrnWidth() / 8;
	//make all the particles at random parts near the bottom, maybe make smokestacks another day 
	for (int i = 0; i < 400; i++) {
		Controller.addParticle(
			Particle( 
			horizontalEighth + (rand() % (6 * horizontalEighth)), //x
			(3 * verticalFourth) + (rand() % verticalFourth), //y
			0, //dx
			(((rand() % 5) + 1.5) / 5.), //dy
			120, //lifetime
			110 + (rand() % 151) - 75, //red
			140 + (rand() % 101) - 55, //green
			125 + (rand() % 111) - 55, //blue
			Particle::GAS)); //type
		clearscreen();
		Controller.sysUpdate();
		usleep(1000000/(Controller.get_FPS()));
	}

	while (Controller.get_head()) {
		clearscreen();
		Controller.sysUpdate();
		usleep(1000000/(Controller.get_FPS()));
	}

	Controller.set_FPS(60.);
	clearscreen();
	show_cursor(true);
}



