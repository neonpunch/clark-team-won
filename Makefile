a.out: main.o Cell.h Particle.h Graphics.h System.h Nevan.h Parker.h Ishan.h Milo.h
	g++ -g -fsanitize=address -std=c++23 main.o

main.o: main.cc Cell.h Particle.h Graphics.h System.h Nevan.h Parker.h Ishan.h Milo.h
	g++ -c -g -fsanitize=address -std=c++23 main.cc

clean:
	rm -f a.out *.o core
