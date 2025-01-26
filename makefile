FLAGS = -I./include/ -lSDL2 -ldl
SRC_FILES = $(wildcard src/*.cpp src/*.c)


default:
	g++ -o prog $(SRC_FILES) $(FLAGS)
