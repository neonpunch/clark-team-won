#include <ostream>
#include "System.h"
using namespace std;

int main () {
	Particle p;	
	System s;
	
	s.addParticle(p);

	s.sysUpdate();
	
}
