all: structures loader
	gcc main.c -o main -lopengl32 -lglu32 -lfreeglut structures.o loader.o

structures:
	gcc -g -c structures.c

loader:
	gcc -g -c loader.c