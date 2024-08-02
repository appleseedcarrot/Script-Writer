CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic -ggdb -Iinclude $(shell pkg-config --cflags sdl2 freetype2) 
CFLAGS = -Iinclude
LIBS = $(shell pkg-config --libs sdl2 freetype2) -ldl

TARGET = output
OBJECTS = src/main.o src/glad.o

build: $(TARGET)

$(TARGET): src/main.o src/glad.o
	$(CXX) $^ -o $@ $(LIBS)

#src/%.o: %.c
#	$(CXX) $(CXXFLAGS) -c $<

#glad.o: src/glad.c
#	$(CC) $(CXXFLAGS) -Iinclude -c $<

.PHONY: clean
clean:
	rm -f src/*.o output

run:
	./output