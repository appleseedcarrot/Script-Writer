CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic -ggdb -Iinclude $(shell pkg-config --cflags glfw3 sdl2 freetype2) 
CFLAGS = -Iinclude
LIBS = $(shell pkg-config --libs glfw3 sdl2 freetype2)

TARGET = output
OBJECTS = src/main.o src/glad.o src/Shader.o src/Character.o src/Text.o 

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)
	
.PHONY: clean
clean:
	rm -f src/*.o output

run:
	./output