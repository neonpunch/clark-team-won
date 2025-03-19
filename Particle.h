#pragma once
#include "/public/colors.h"
#include <iostream>
#include <numbers>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
using namespace std;

class Particle{
	public:
		double x, y;	// Particle Initial Position
		// Color color;
		double dx, dy;	// Particle Velocity
		int lifetime;	// Particle Lifespan
		enum ParticleType {
			STREAMER, BALLISTIC, FIREWORK, RESIDUALAURA
		};
		Particle(double new_x = 0, double new_y = 0, double new_dx = 0, double new_dy = 0, int newLifetime = 0): x(new_x), y(new_y), dx(new_dx), dy(new_dy), lifetime(newLifetime){}

		double get_x() const{return x;}
		double get_y() const{return y;}
		double get_dx() const{return dx;}
		double get_dy() const{return dy;}
		int get_lifetime() const{return lifetime;}
		void set_x(double new_x) {x = new_x;}
		void set_y(double new_y) {y = new_y;}
		void set_dx(double new_dx) {dx = new_dx;}
		void set_dy(double new_dy) {dy = new_dy;}
		void set_lifetime(int newLifetime) {lifetime = newLifetime;}

		void testParticle(){

			Particle p;

			bool testsPassed = true;

			if (p.get_x() != 0) testsPassed = false;
			if (p.get_y() != 0) testsPassed = false;
			if (p.get_dx() != 0) testsPassed = false;
			if (p.get_dy() != 0) testsPassed = false;
			if (p.get_lifetime() != 0) testsPassed = false;

			//  cout << "Initializing.\n";
			//  cout << "x: " << p.get_x() << ", y: " << p.get_y() << ", dx: " << p.get_dx() << ", dy: " << p.get_dy() << ", Lifetime: " << p.get_lifetime() << "\n";

			p.set_x(14.0);
			p.set_y(24.6);
			p.set_dx(2.0);
			p.set_dy(-1.0);
			p.set_lifetime(90);

			//  cout << "\nSetting.\n";
			//  cout << "x: " << p.get_x() << ", y: " << p.get_y() << ", dx: " << p.get_dx() << ", dy: " << p.get_dy() << ", Lifetime: " << p.get_lifetime() << "\n";

			if (p.get_x() != 14.0) testsPassed = false;
			if (p.get_y() != 24.6) testsPassed = false;
			if (p.get_dx() != 2.0) testsPassed = false;
			if (p.get_dy() != -1.0) testsPassed = false;
			if (p.get_lifetime() != 90) testsPassed = false;

			if (testsPassed){
				cout << "Particle.h passed all tests!\n";
			} else {
				cout << "Some tests failed.\n";
			}

		}
		void Physics(){
			srand(time(0));
			auto [rows,cols] = get_terminal_size();
			rows--;
			cols--;
			p.x = rand() % cols;
			p.y = rand() % rows;
			p.dx = 1;
			p.dy = 1;
			p.lifetime = 1440;
			string pSymbol = "*";
			double FPS = 144.;

			for (int i = 0; i < lifetime; i++) {
				p.x += p.dx;
				p.y += p.dy;

				if (p.x < 0) {
					break;
				}
				if (p.y < 0) {
					break;
				}
				if (p.x >= cols) {
					break;
				}
				if (p.y >= rows) {
					break;
				}
				p.dx += (rand() % 3) - 1;
				p.dy += (rand() % 3) - 1; 
				if (p.dx > 1.5) p.dx = 1.5;
				if (p.dx < -1.5) p.dx = -1.5;
				if (p.dy > 1.5) p.dy = 1.5;
				if (p.dy < -1.5) p.dy = -1.5;
				movecursor(p.y, p.x);
				// setbgcolor(,,);
				// setcolor(,,);
				cout << pSymbol;
				cout.flush();
				//reset.color();
				usleep(1'000'000/FPS);
				p.lifetime--;
				clearscreen();
			}
			show_cursor(true);
			//resetcolor();
		}
};
