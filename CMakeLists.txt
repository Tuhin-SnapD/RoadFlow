cmake_minimum_required(VERSION 3.10)
project(RoadConstruction VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Graph.cpp
    src/Queue.cpp
    src/RoadScheduler.cpp
    src/BankersAlgorithm.cpp
    src/Config.cpp
    src/Logger.cpp
    src/Benchmark.cpp
)

set(DEMO_SOURCES
    src/demo.cpp
    src/Graph.cpp
    src/Queue.cpp
    src/RoadScheduler.cpp
    src/BankersAlgorithm.cpp
    src/Config.cpp
    src/Logger.cpp
    src/Benchmark.cpp
)

# Create main executable
add_executable(RoadConstruction ${SOURCES})

# Create demo executable
add_executable(RoadConstructionDemo ${DEMO_SOURCES})

# Find Google Test
find_package(GTest QUIET)

if(GTest_FOUND)
    # Test source files
    set(TEST_SOURCES
        tests/test_main.cpp
        tests/test_graph.cpp
        tests/test_scheduler.cpp
        tests/test_bankers.cpp
        src/Graph.cpp
        src/Queue.cpp
        src/RoadScheduler.cpp
        src/BankersAlgorithm.cpp
        src/Config.cpp
        src/Logger.cpp
        src/Benchmark.cpp
    )
    
    # Create test executable
    add_executable(RoadConstructionTests ${TEST_SOURCES})
    target_link_libraries(RoadConstructionTests GTest::GTest GTest::Main)
    
    # Enable testing
    enable_testing()
    add_test(NAME RoadConstructionTests COMMAND RoadConstructionTests)
else()
    message(WARNING "Google Test not found. Tests will not be built.")
endif()

# Set output directories
set_target_properties(RoadConstruction RoadConstructionDemo
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

if(GTest_FOUND)
    set_target_properties(RoadConstructionTests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()

# Install targets
install(TARGETS RoadConstruction RoadConstructionDemo
    RUNTIME DESTINATION bin
)

if(GTest_FOUND)
    install(TARGETS RoadConstructionTests
        RUNTIME DESTINATION bin
    )
endif()

# Install headers
install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Install documentation
install(FILES README.md LICENSE
    DESTINATION share/doc/RoadConstruction
) 