a.out: main.o Cell.h Particle.h Graphics.h System.h
	g++ -fsanitize=address main.o

main.o: main.cc Cell.h Particle.h Graphics.h System.h
	g++ -c -fsanitize=address main.cc

clean:
	rm -f a.out *.o core
