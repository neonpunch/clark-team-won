#include <ostream>
#include "System.h"
#include "Cell.h" 
#include "Particle.h"
#include "Graphics.h"
using namespace std;

int main () {
	Particle p;	
	System s;
	s.addParticle(p);

	s.sysUpdate();
	
	return 1;	
}
