# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -O2

# Executable name
EXEC = memory_management_system

# Source files
SRCS = Task.cpp Test.cpp IOManager.cpp MemoryManager.cpp Performance.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Include directories
INCLUDES = -I.

# Header files
HEADERS = config.h IO_Module.h IOManager.h MemoryManager.h Performance.h PerformanceModule.h Task.h

# Trace files
TRACEFILES = tracefile_1KB_8GB_16GB.txt tracefile_2KB_4GB_8GB.txt tracefile_4KB_4GB_4GB.txt

# Build executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Compile object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run the program with the trace files
run: $(EXEC)
	./$(EXEC)

# Clean object files and executable
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: clean run
