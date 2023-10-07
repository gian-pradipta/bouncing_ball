./bin/main.exe : ./bin/main.o ./bin/snake_game.o ./bin/Graphic.o ./bin/Snake.o ./bin/LinkedList.o
	gcc -o ./bin/main ./bin/main.o ./bin/snake_game.o ./bin/Graphic.o ./bin/Snake.o ./bin/LinkedList.o


./bin/main.o : ./src/main.c ./bin/snake_game.o
	gcc -o ./bin/main.o -c ./src/main.c


./bin/snake_game.o : ./src/snake_game.c ./bin/Snake.o ./bin/Graphic.o ./include/snake_game.h
	gcc -o ./bin/snake_game.o -c ./src/snake_game.c

./bin/Graphic.o : ./src/Graphic.c ./bin/LinkedList.o ./include/Graphic.h
	gcc -o ./bin/Graphic.o -c ./src/Graphic.c

./bin/Snake.o : ./src/Snake.c ./bin/LinkedList.o ./include/Snake.h
	gcc -o ./bin/Snake.o -c ./src/Snake.c

./bin/LinkedList.o : ./src/LinkedList.c ./include/Position.h
	gcc -c ./src/LinkedList.c -o ./bin/LinkedList.o

