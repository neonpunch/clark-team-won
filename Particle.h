//#include "Color.h"
#include <numbers>
#include <cmath>

class Particle{
	public:
		double x, y;	// Particle Initial Position
		// Color color;
		double dx, dy;	// Particle Velocity
		int lifetime;	// Particle Lifespan
		enum ParticleType {
			STREAMER, BALLISTIC, FIREWORK, RESIDUALAURA
		};
		Particle(double new_x, double new_y, double new_dx, double new_dy, int newLifetime): x(new_x), y(new_y), dx(new_dx), dy(new_dy), lifetime(newLifetime){}

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




};

