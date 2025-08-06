# Road Construction Scheduling System

A comprehensive C++ application that implements advanced scheduling algorithms for road construction projects. This system combines Dijkstra's shortest path algorithm with priority scheduling and resource allocation using Banker's Algorithm.

## Features

### 🛣️ Priority Scheduling Algorithm
- **Dijkstra's Algorithm**: Finds optimal routes between cities in the road network
- **Multi-factor Priority Calculation**: Considers distance, utility, traffic impact, and deadlines
- **Optimal Construction Sequence**: Determines the best order for road construction
- **Deadline Analysis**: Checks if all project deadlines can be met
- **Performance Metrics**: Calculates average turnaround and waiting times

### 🔒 Banker's Algorithm (Resource Allocation)
- **Deadlock Prevention**: Ensures safe resource allocation
- **Safe Sequence Detection**: Finds safe execution order for multiple projects
- **Resource Management**: Handles multiple resource types efficiently
- **Matrix Visualization**: Displays allocation, maximum, and need matrices

## Project Structure

```
RoadConstruction/
├── CMakeLists.txt          # CMake build configuration
├── README.md              # Project documentation
├── include/               # Header files
│   ├── Graph.h           # Graph and Dijkstra's algorithm
│   ├── Queue.h           # Queue implementation
│   ├── RoadScheduler.h   # Priority scheduling logic
│   └── BankersAlgorithm.h # Resource allocation
├── src/                  # Source files
│   ├── main.cpp          # Main application
│   ├── Graph.cpp         # Graph implementation
│   ├── Queue.cpp         # Queue implementation
│   ├── RoadScheduler.cpp # Scheduling implementation
│   └── BankersAlgorithm.cpp # Banker's algorithm
└── test.cpp              # Original test file (legacy)
```

## Building the Project

### Prerequisites
- CMake 3.16 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)

### Build Instructions

#### Option 1: Using CMake (Recommended)
1. **Clone or download the project**
   ```bash
   git clone <repository-url>
   cd RoadConstruction
   ```

2. **Create build directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure and build**
   ```bash
   cmake ..
   cmake --build .
   ```

4. **Run the application**
   ```bash
   ./bin/RoadConstruction  # On Unix-like systems
   # or
   .\bin\RoadConstruction.exe  # On Windows
   ```

#### Option 2: Using Make (Unix/Linux/macOS)
```bash
make
# or
make all
```

#### Option 3: Using Windows Batch File
```cmd
build.bat
```

#### Option 4: Using PowerShell Script
```powershell
.\build.ps1
```

#### Option 5: Manual Compilation
```bash
# Create directories
mkdir -p obj bin

# Compile source files
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude -c src/*.cpp -o obj/

# Link executable
g++ obj/*.o -o bin/RoadConstruction
```

## Usage

### Priority Scheduling Algorithm

1. Select option 1 from the main menu
2. Enter the number of roads to schedule
3. For each road:
   - Define the road network (cities and routes)
   - Specify start and destination cities
   - Enter road parameters (utility, traffic, construction time, deadline)
4. View the optimal construction sequence and performance metrics

### Banker's Algorithm

1. Select option 2 from the main menu
2. Enter the number of roads and resource types
3. Input the allocation matrix (currently allocated resources)
4. Input the maximum need matrix (maximum resource requirements)
5. Input available resources
6. View the safe sequence (if it exists)

## Example Usage

### Priority Scheduling Example
```
Enter the number of roads: 2

For Road 1:
- Cities: 4, Routes: 3
- Routes: (0,1,10), (1,2,15), (2,3,20)
- Start: 0, Destination: 3
- Utility: 5, Traffic: 3, Time: 30, Deadline: 40

For Road 2:
- Cities: 3, Routes: 2
- Routes: (0,1,8), (1,2,12)
- Start: 0, Destination: 2
- Utility: 8, Traffic: 2, Time: 25, Deadline: 35
```

### Banker's Algorithm Example
```
Roads: 3, Resources: 3

Allocation Matrix:
R0: 0 1 0
R1: 2 0 0
R2: 3 0 2

Maximum Matrix:
R0: 7 5 3
R1: 3 2 2
R2: 9 0 2

Available: 3 3 2
```

## Technical Details

### Algorithms Implemented

1. **Dijkstra's Algorithm**: O(V²) time complexity for finding shortest paths
2. **Priority Scheduling**: O(n²) time complexity for n roads
3. **Banker's Algorithm**: O(n² × m) time complexity for n roads and m resource types

### Data Structures Used

- **Graph**: Adjacency matrix representation
- **Queue**: Circular array implementation
- **Vectors**: Dynamic arrays for matrices and sequences
- **Priority-based sorting**: For optimal sequence determination

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

This project is open source and available under the MIT License.

## Acknowledgments

- Original algorithm implementations from the test.cpp file
- Modern C++ practices and CMake build system
- Comprehensive documentation and user interface improvements 