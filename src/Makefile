CC = gcc
CFLAGS = -0

default: vanilla

vanilla:					#run naive program
	$(CC) -c vanilla.c
	$(CC) -o run vanilla.o
	./run
	$(RM) vanilla.o run

cached:					#run cached program
	$(CC) -c cached.c
	$(CC) -o run cached.o
	./run
	$(RM) cached.o run

strassen:					#run strassen program
	$(CC) -c strassen.c
	$(CC) -o run strassen.o
	./run
	$(RM) strassen.o run

strassen_alt:					#run strassen program
	$(CC) -c strassen_alt.c
	$(CC) -o run strassen_alt.o
	./run
	$(RM) strassen_alt.o run