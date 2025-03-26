#include "System.h"

//Parker's gas project

static void GasClouds(System &Controller) {
	Controller.set_FPS(10.);
	show_cursor(false);
	int verticalThird = Controller.get_scrnHeight() / 3;
	int horizontalFifth = Controller.get_scrnWidth() / 5;
	//make all the particles at random parts near the bottom, maybe make smokestacks another day 
	for (int i = 0; i < 120; i++) {
		Controller.addParticle(
			Particle( 
			horizontalFifth + (rand() % (3 * horizontalFifth)), //x
			(2 * verticalThird) + (rand() % verticalThird), //y
			0, //dx
			(((rand() % 5) + 3) / 5.), //dy
			120, //lifetime
			170 + (rand() % 56) - 28, //red
			200 + (rand() % 56) - 28, //green
			200 + (rand() % 56) - 28, //blue
			Particle::GAS)); //type
		clearscreen();
		Controller.sysUpdate();
		usleep(1000000/(Controller.get_FPS()));
	}

	while (Controller.get_head()) Controller.sysUpdate();

	Controller.set_FPS(60.);
	clearscreen();
	show_cursor(true);
}



