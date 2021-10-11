exec:shell.o
	gcc -Wall -g -o exec shell.o -lm

shell.o: shell.c shell.h
	gcc -Wall -g -c shell.c

clean:
	rm -rf *.o
	rm -f exec
