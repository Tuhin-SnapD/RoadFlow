cmake_minimum_required(VERSION 3.16)
project(RoadConstruction VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# Add executable
add_executable(RoadConstruction 
    src/main.cpp
    src/Graph.cpp
    src/Queue.cpp
    src/RoadScheduler.cpp
    src/BankersAlgorithm.cpp
)

# Include directories
target_include_directories(RoadConstruction PRIVATE include)

# Set output directory
set_target_properties(RoadConstruction PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install target
install(TARGETS RoadConstruction
    RUNTIME DESTINATION bin
) 