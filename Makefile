CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic -ggdb $(shell pkg-config --cflags sdl2 freetype2)
LIBS = $(shell pkg-config --libs sdl2 freetype2)

all: output
output: src/main.o src/application.o
	$(CXX) src/main.o src/application.o -o output $(LIBS)

main.o: src/main.cpp src/application.h
	$(CXX) -c src/main.cpp $(CXXFLAGS)

application.o: src/application.cpp src/application.h
	$(CXX) -c src/application.cpp $(CXXFLAGS)

clean:
	rm -f src/*.o output