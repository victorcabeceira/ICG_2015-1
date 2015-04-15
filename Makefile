all:

	g++ -o prog main.cpp ogldev_util.cpp -W -Wall -pedantic -ansi -lGL -lGLU -lSDL2 -lGLEW
