# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17

# Source files
SOURCES = main.cpp Sorting.cpp Statistics.cpp Car.cpp

# Executable name
EXECUTABLE = program

# Build rule
all: $(EXECUTABLE)

# Linking
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean rule
clean:
	rm -f $(EXECUTABLE)

# Phony targets
.PHONY: all clean
