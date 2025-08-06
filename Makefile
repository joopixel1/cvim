# Default target
all: run

# Clean target
clean:
	rm -rf build


# variables
CXX := clang++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++20
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, build/%.o, $(SRCS))
TARGET := build/cvim


# Run the program
run: $(TARGET)
	./$(TARGET)

# Link object files into final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each .cpp file into .o in build/
build/%.o: %.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
build:
	mkdir -p build