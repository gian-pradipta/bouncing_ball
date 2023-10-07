main.exe : main.o snake_game.o Graphic.o Snake.o LinkedList.o
	gcc -o main main.o snake_game.o Graphic.o Snake.o LinkedList.o


main.o : main.c snake_game.o
	gcc -o main.o -c main.c


snake_game.o : snake_game.c Snake.o Graphic.o snake_game.h
	gcc -o snake_game.o -c snake_game.c

Graphic.o : Graphic.c LinkedList.o Graphic.h
	gcc -o Graphic.o -c Graphic.c

Snake.o : Snake.c LinkedList.o Snake.h
	gcc -o Snake.o -c Snake.c

LinkedList.o : LinkedList.c Position.h
	gcc -c LinkedList.c -o LinkedList.o

