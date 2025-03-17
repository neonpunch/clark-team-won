#include <ostream>
#include "System.h"
#include "Cell.h"
#include "Particle.h"
#include "Graphics.h"
using namespace std;

int main () {
	System s;

	s.testSystem();

	gc Graphics;

	Graphics.testinggc();

	Particle p;

	p.testParticle();

	Cell c;

	c.CellTester();

}
