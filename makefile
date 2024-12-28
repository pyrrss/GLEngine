FLAGS = -I./include/ -lSDL2 -ldl
SRC_FILES = src/main.cpp src/glad.c src/GLManager.cpp


default:
	g++ -o prog $(SRC_FILES) $(FLAGS)