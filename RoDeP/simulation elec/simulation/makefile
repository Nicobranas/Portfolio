exec: simulation.o
	gcc -Wall -o exec simulation.o -lm

simulation.o: simulation.c simulation.h
	gcc -Wall -c simulation.c

clean:
	rm -rf *.o
	rm -f exec