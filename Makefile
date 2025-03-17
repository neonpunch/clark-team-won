a.out: main.o Cell.h Particle.h Graphics.h System.h
	g++ -o a.out main.o

main.o: main.cc Cell.h Particle.h Graphics.h System.h
	g++ -c main.cc

clean:
	rm -f a.out *.o core
