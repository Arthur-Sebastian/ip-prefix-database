CC = gcc
FLAGS = -Wall -Wextra -pedantic

ODIR = obj
 
default: prefix_db

main.o: main.c
	$(CC) $(FLAGS) -o $@ -c main.c
prefix.o: lib/prefix.c
	$(CC) $(FLAGS) -o $@ -c lib/prefix.c
clean:
	$(RM) *.o
	$(RM) prefix_db
prefix_db: clean main.o prefix.o
	$(CC) $(FLAGS) -o $@ main.o prefix.o
	$(RM) *.o
run: prefix_db
	./prefix_db

