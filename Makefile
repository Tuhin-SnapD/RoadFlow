# Makefile for Road Construction Scheduling System
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Iinclude
SOURCES = src/main.cpp src/Graph.cpp src/Queue.cpp src/RoadScheduler.cpp src/BankersAlgorithm.cpp src/Config.cpp src/Logger.cpp src/Benchmark.cpp
DEMO_SOURCES = src/demo.cpp src/Graph.cpp src/Queue.cpp src/RoadScheduler.cpp src/BankersAlgorithm.cpp src/Config.cpp src/Logger.cpp src/Benchmark.cpp
TEST_SOURCES = tests/test_main.cpp tests/test_graph.cpp tests/test_scheduler.cpp tests/test_bankers.cpp src/Graph.cpp src/Queue.cpp src/RoadScheduler.cpp src/BankersAlgorithm.cpp src/Config.cpp src/Logger.cpp src/Benchmark.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Default target
all: bin/RoadConstruction bin/RoadConstructionDemo

# Create bin directory
bin:
	mkdir -p bin

# Main executable
bin/RoadConstruction: $(OBJECTS) | bin
	$(CXX) $(OBJECTS) -o $@

# Demo executable
bin/RoadConstructionDemo: $(DEMO_OBJECTS) | bin
	$(CXX) $(DEMO_OBJECTS) -o $@

# Test executable (if Google Test is available)
test: bin/RoadConstructionTests
	./bin/RoadConstructionTests

bin/RoadConstructionTests: $(TEST_OBJECTS) | bin
	$(CXX) $(TEST_OBJECTS) -lgtest -lgtest_main -lpthread -o $@

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(DEMO_OBJECTS) $(TEST_OBJECTS)
	rm -f bin/RoadConstruction bin/RoadConstructionDemo bin/RoadConstructionTests

# Install (requires sudo)
install: all
	sudo cp bin/RoadConstruction /usr/local/bin/
	sudo cp bin/RoadConstructionDemo /usr/local/bin/
	sudo mkdir -p /usr/local/include/RoadConstruction
	sudo cp include/*.h /usr/local/include/RoadConstruction/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/RoadConstruction
	sudo rm -f /usr/local/bin/RoadConstructionDemo
	sudo rm -rf /usr/local/include/RoadConstruction

# Run main program
run: bin/RoadConstruction
	./bin/RoadConstruction

# Run demo
demo: bin/RoadConstructionDemo
	./bin/RoadConstructionDemo

# Check if Google Test is available
check-gtest:
	@echo "Checking for Google Test..."
	@if pkg-config --exists gtest; then \
		echo "Google Test found via pkg-config"; \
	elif [ -f /usr/include/gtest/gtest.h ]; then \
		echo "Google Test found in system headers"; \
	else \
		echo "Google Test not found. Install with: sudo apt-get install libgtest-dev"; \
		exit 1; \
	fi

# Help
help:
	@echo "Available targets:"
	@echo "  all              - Build main and demo executables"
	@echo "  test             - Build and run tests (requires Google Test)"
	@echo "  clean            - Remove build artifacts"
	@echo "  install          - Install to system (requires sudo)"
	@echo "  uninstall        - Remove from system (requires sudo)"
	@echo "  run              - Run main program"
	@echo "  demo             - Run demo program"
	@echo "  check-gtest      - Check if Google Test is available"
	@echo "  help             - Show this help"

.PHONY: all test clean install uninstall run demo check-gtest help 