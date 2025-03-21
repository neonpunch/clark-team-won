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
    public:
        double x, y;    // Particle Initial Position
        double dx, dy;  // Particle Velocity
        int lifetime;   // Particle Lifespan
        int r, g, b;    // Particle Color
        enum ParticleType {
            STREAMER, BALLISTIC, FIREWORK
        };
        ParticleType type;

        Particle(double new_x = 0, double new_y = 0, double new_dx = 0, double new_dy = 0, int newLifetime = 0, int newR = 5, int newG = 5, int newB = 5, ParticleType newType = FIREWORK)
            : x(new_x), y(new_y), dx(new_dx), dy(new_dy), lifetime(newLifetime), r(newR), g(newG), b(newB), type(newType) {
            if (newR < 0 || newR > 255){
                r = 5;
            }
            if (newG < 0 || newG > 255){
                g = 5;
            }
            if (newB < 0 || newB > 255){
                b = 5;
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
                    dx *= 0.98;
                    dy *= 0.98;
                    break;
                case BALLISTIC:
                    dy += 0.1;
                    break;
                case FIREWORK:
                    double angle = (rand() % 360) * (numbers::pi / 180.0);
                    double speed = 1.5;

                    dx = speed * cos(angle);
                    dy = speed * sin(angle);
                    break;
                /*case RESIDUALAURA: // Smoke effect (small)
                    dx *= 0.90;
                    dy *= 0.90;
                    x += ((rand() % 3) - 1) * 0.1;
                    y += dy;
                    lifetime -= 2;
                    break;*/
            }
            x += dx;
            y += dy;
            lifetime--;
        }
};
