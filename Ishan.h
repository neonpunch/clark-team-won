#include "Particle.h"
#include "System.h"
#include "Graphics.h"
#include "Cell.h"
#include <ctime>
#include <cstdlib>
//Ishan's firework project
using namespace std;
class IA {
public:
IA () {
}	
void makeFirework(System& sys) {
	srand(time(0));
	double xIn = 0;
	double yIn = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	cout << "enter the x position" << endl;
	cin >> xIn;
	cout << "enter the y position" << endl;
	cin >> yIn;
	cout << "enter the red color (r,g,b)" << endl;
	cin >> red;
	cout << "enter the green color (r,g,b)" << endl;
	cin >> green;
	cout << "enter the blue color (r,g,b)" << endl;
	cin >> blue;
	int lifetimeIn = 100;
	cout << "Enter the lifetime" << endl;
	cin >> lifetimeIn;
	for (int i = 0; i < 100; ++i) {
	  double dxIn = (rand() % 200 - 100) / static_cast<double>(50);
	  double dyIn = (rand() % 200 - 100) / static_cast<double>(50);
	 	red = rand() % 256; // randomizes the color, for a nice cool effect
		blue = rand() % 256;
		green = rand() % 256;
	  Particle fire(xIn,yIn,dxIn,dyIn,lifetimeIn,red,green,blue,Particle::FIREWORK);
 	  sys.addParticle(fire);	
	}
}
void sim(System& sys) {
	show_cursor(false);
	for (int i = 0; i < 60; ++i) {
	  clearscreen();
sys.sysUpdate();
	for (Cell* curr = sys.get_head(); curr; curr = curr->getNext()) {
	  sys.drawParticle(curr->particle);
	  }
		usleep(100000);
		}
	clearscreen();
	show_cursor(true);
	}
};

	
