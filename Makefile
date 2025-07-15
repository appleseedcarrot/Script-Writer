CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic -ggdb -Iinclude $(shell pkg-config --cflags glfw3 freetype2) 
CFLAGS = -I./include
LIBS = $(shell pkg-config --libs glfw3 freetype2)

SRC_DIR = src
BUILD = build
TARGET = $(BUILD)/output

CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
SOURCES = $(CPP_SOURCES) $(C_SOURCES)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD)/%.o, $(CPP_SOURCES)) \
		  $(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(C_SOURCES))

$(BUILD):
	mkdir -p $(BUILD)

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

$(BUILD)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@
	
.PHONY: clean

clean:
	rm -rf $(BUILD)

run:
	./$(TARGET)