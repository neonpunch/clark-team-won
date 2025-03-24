#pragma once
#include "/public/colors.h"
#include <iostream>
#include <numbers>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
using namespace std;

class Particle {
<<<<<<< HEAD
	public:
		double x, y;    // Particle Initial Position
		double dx, dy;  // Particle Velocity
		int lifetime;   // Particle Lifespan
		int r, g, b;    // Particle Color
		enum ParticleType {
			STREAMER, BALLISTIC, FIREWORK, MOSQUITO
		};
		ParticleType type;
=======
    public:
        double x, y;    // Particle Initial Position
        double dx, dy;  // Particle Velocity
        int lifetime;   // Particle Lifespan
        int r, g, b;    // Particle Color
        enum ParticleType {
            STREAMER, BALLISTIC, FIREWORK, MOSQUITO
        };
        ParticleType type;
>>>>>>> refs/remotes/origin/main

		Particle(double new_x = 0, double new_y = 0, double new_dx = 0, double new_dy = 0, int newLifetime = 0, int newR = 5, int newG = 5, int newB = 5, ParticleType newType = FIREWORK)
			: x(new_x), y(new_y), dx(new_dx), dy(new_dy), lifetime(newLifetime), r(newR), g(newG), b(newB), type(newType) {
				if (newR < 0 || newR > 255){
					r = 100;
				}
				if (newG < 0 || newG > 255){
					g = 100;
				}
				if (newB < 0 || newB > 255){
					b = 100;
				}
			}

		double get_x() const { return x; }
		double get_y() const { return y; }
		double get_dx() const { return dx; }
		double get_dy() const { return dy; }
		int get_lifetime() const { return lifetime; }
		int get_r() const { return r; }
		int get_g() const { return g; }
		int get_b() const { return b; }
		ParticleType get_type() const { return type; }

		void set_x(double new_x) { x = new_x; }
		void set_y(double new_y) { y = new_y; }
		void set_dx(double new_dx) { dx = new_dx; }
		void set_dy(double new_dy) { dy = new_dy; }
		void set_lifetime(int newLifetime) { lifetime = newLifetime; }
		void set_r(double newR) { r = newR; }
		void set_g(double newG) { g = newG; }
		void set_b(double newB) { b = newB; }
		void set_type(ParticleType newType) { type = newType; }

		bool operator==(const Particle& other) const {
			return x == other.x && y == other.y && dx == other.dx && dy == other.dy && lifetime == other.lifetime && r == other.r && g == other.g && b == other.b && type == other.type;
		}

		void testParticle() {
			Particle p;

			bool testsPassed = true;

			if (p.get_x() != 0) testsPassed = false;
			if (p.get_y() != 0) testsPassed = false;
			if (p.get_dx() != 0) testsPassed = false;
			if (p.get_dy() != 0) testsPassed = false;
			if (p.get_lifetime() != 0) testsPassed = false;

			p.set_x(14.0);
			p.set_y(24.6);
			p.set_dx(2.0);
			p.set_dy(-1.0);
			p.set_lifetime(180);

			if (p.get_x() != 14.0) testsPassed = false;
			if (p.get_y() != 24.6) testsPassed = false;
			if (p.get_dx() != 2.0) testsPassed = false;
			if (p.get_dy() != -1.0) testsPassed = false;
			if (p.get_lifetime() != 180) testsPassed = false;

			if (testsPassed){
				cout << "Particle.h passed all tests!\n";
			} else {
				cout << "Some tests failed.\n";
			}
		}

		void Physics() {
			switch (type) {
				case STREAMER:
					break;
				case BALLISTIC:
					dx *= 0.98;
					dy += 0.05;
<<<<<<< HEAD
					break;
				case FIREWORK:
					dx *= 0.98;
					dy *= 0.98;
					break;
				case MOSQUITO: // Erratic moving particle
					dx += (rand() % 3) - 1;
					dy += (rand() % 3) - 1; 
					if (dx > 5.) dx = 5.;
					if (dx < -5.) dx = -5.;
					if (dy > 5.) dy = 5.;
					if (dy < -5.) dy = -5.;
					break;
				default:
					exit(1);
			}
			x += dx;
			y += dy;
			lifetime--;
		}
=======
                    break;
                case FIREWORK:
                    dx *= 0.98;
                    dy *= 0.98;
                    break;
				case MOSQUITO:
					dx += (rand() % 3) - 1;
					dy += (rand() % 3) - 1;
					if (dx > 1.5) dx = 1.5;
					if (dx < -1.5) dx = -1.5;
					if (dy > 1.5) dy = 1.5;
					if (dy < -1.5) dy = -1.5;
					break;
				default:
					exit(1);
            }
            x += dx;
            y += dy;
            lifetime--;
        }
>>>>>>> refs/remotes/origin/main
};
