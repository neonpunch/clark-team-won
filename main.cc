#include <ostream>
#include "System.h"
#include "Cell.h" 
#include "Particle.h"
#include "Graphics.h"
using namespace std;

int main () {
	System s;
	s.testSystem();

	cout << testinggc() << endl;

	Particle p;
	p.testParticle();
	
	cout << CellTester() << endl;

}
