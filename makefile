FLAGS = -I./include/ -I./imgui  -lSDL2 -ldl -lGL
SRC_FILES = $(wildcard src/*.cpp src/*.c imgui/*.cpp)  


default:
	g++ -o prog $(SRC_FILES) $(FLAGS)
