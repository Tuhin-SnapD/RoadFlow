# 🛣️ Road Construction Scheduling System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard)
[![Windows](https://img.shields.io/badge/Platform-Windows-green.svg)](https://www.microsoft.com/windows)

A comprehensive C++ application that demonstrates advanced scheduling algorithms for road construction projects. This educational project combines **Dijkstra's shortest path algorithm** with **priority scheduling** and **resource allocation using Banker's Algorithm** to solve real-world construction planning problems.

## 🎯 Educational Objectives

This project serves as an excellent learning resource for:

- **Algorithm Design**: Understanding complex scheduling algorithms
- **Data Structures**: Graph representations, priority queues, and matrix operations
- **Resource Management**: Deadlock prevention and safe resource allocation
- **Software Engineering**: Modern C++ practices, testing, and project organization
- **Problem Solving**: Real-world application of theoretical computer science concepts

## 🚀 Key Features

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

### 🛠️ Software Engineering Features
- **Comprehensive Testing**: Unit tests with Google Test framework
- **Performance Benchmarking**: Built-in performance analysis tools
- **Professional Logging**: Multi-level logging system with file output
- **Configuration Management**: Flexible configuration system
- **Cross-Platform Build**: Supports Windows with automatic compiler detection
- **Modern C++**: Uses C++17 features and best practices

## 📚 Learning Resources

### Understanding the Algorithms

#### 1. Dijkstra's Algorithm
Dijkstra's algorithm finds the shortest path between nodes in a graph. In our context:
- **Nodes** = Cities in the road network
- **Edges** = Roads connecting cities
- **Weights** = Distances between cities

**Time Complexity**: O(V²) where V is the number of vertices (cities)

#### 2. Priority Scheduling
Our priority scheduling algorithm considers multiple factors:
- **Distance**: Shorter routes get higher priority
- **Utility**: Higher utility projects get priority
- **Traffic Impact**: Lower traffic impact gets priority
- **Deadlines**: Projects with tighter deadlines get priority

**Formula**: `Priority = (Utility × Traffic_Impact) / (Distance × Deadline)`

#### 3. Banker's Algorithm
Banker's algorithm prevents deadlocks by ensuring safe resource allocation:
- **Allocation Matrix**: Currently allocated resources
- **Maximum Matrix**: Maximum resource needs
- **Need Matrix**: Remaining resource needs
- **Available Resources**: Free resources

**Safety Check**: Ensures there's always a safe sequence for resource allocation

## 📁 Project Structure

```
RoadConstruction/
├── .github/workflows/     # CI/CD pipeline configuration
├── build.bat             # Windows build script with auto-compiler detection
├── README.md             # Project documentation (this file)
├── test_plan.md          # Comprehensive test plan
├── LICENSE               # MIT License
├── .gitignore           # Git ignore patterns
├── include/              # Header files
│   ├── Graph.h          # Graph and Dijkstra's algorithm
│   ├── Queue.h          # Queue implementation
│   ├── RoadScheduler.h  # Priority scheduling logic
│   ├── BankersAlgorithm.h # Resource allocation
│   ├── Benchmark.h      # Performance benchmarking
│   ├── Config.h         # Configuration management
│   └── Logger.h         # Logging system
├── src/                 # Source files
│   ├── main.cpp         # Main application with interactive menu
│   ├── demo.cpp         # Professional features demonstration
│   ├── Graph.cpp        # Graph implementation
│   ├── Queue.cpp        # Queue implementation
│   ├── RoadScheduler.cpp # Scheduling implementation
│   ├── BankersAlgorithm.cpp # Banker's algorithm
│   ├── Benchmark.cpp    # Benchmark implementation
│   ├── Config.cpp       # Configuration implementation
│   └── Logger.cpp       # Logger implementation
├── tests/               # Unit tests
│   ├── test_main.cpp    # Test main file
│   ├── test_graph.cpp   # Graph tests
│   ├── test_scheduler.cpp # Scheduler tests
│   ├── test_bankers.cpp # Banker's algorithm tests
│   └── test_new_features.cpp # New features tests
└── bin/                 # Compiled executables (created after build)
```

## 🛠️ Building the Project

### Prerequisites
- **Windows OS** (primary support)
- **C++ Compiler**: Any of the following (auto-detected by build script):
  - MinGW-w64 (g++)
  - Microsoft Visual Studio Build Tools (cl)
  - GCC (gcc)

### Quick Start (Windows)

1. **Clone or download the project**
   ```cmd
   git clone <repository-url>
   cd RoadConstruction
   ```

2. **Run the build script**
   ```cmd
   build.bat
   ```

The build script will:
- Auto-detect available C++ compilers
- Create necessary directories
- Compile all source files
- Link executables
- Run unit tests (if Google Test is available)
- Provide helpful error messages if compilation fails

### Build Output
After successful build, you'll find:
- `bin\RoadConstruction.exe` - Main application
- `bin\RoadConstructionDemo.exe` - Demo program
- `bin\RoadConstructionTests.exe` - Test suite (if Google Test available)

## 🎮 Usage Guide

### Running the Application

```cmd
bin\RoadConstruction.exe
```

### Main Menu Options

1. **Priority Scheduling Algorithm** - Interactive road scheduling
2. **Banker's Algorithm** - Resource allocation and deadlock prevention
3. **Load from file (Priority Scheduling)** - Load data from text file
4. **Load from file (Banker's Algorithm)** - Load resource data from file
5. **Quick demo (Priority Scheduling)** - See algorithm in action
6. **Quick demo (Banker's Algorithm)** - See resource allocation demo
7. **Exit** - Close the application

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

**Expected Output**:
- Shortest path calculations for each road
- Priority calculations based on multiple factors
- Optimal construction sequence
- Performance metrics (turnaround time, waiting time)
- Deadline feasibility analysis

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

**Expected Output**:
- Need matrix calculation
- Safe sequence detection
- Resource allocation analysis
- Deadlock prevention verification

## 🧪 Testing

### Running Tests
```cmd
bin\RoadConstructionTests.exe
```

### Test Coverage
- **Graph Tests**: Dijkstra's algorithm functionality
- **Scheduler Tests**: Priority scheduling logic
- **Banker's Algorithm Tests**: Resource allocation safety
- **Integration Tests**: End-to-end functionality

### Manual Testing
Follow the test plan in `test_plan.md` for comprehensive manual testing scenarios.

## 📊 Performance Analysis

### Algorithm Complexity

| Algorithm | Time Complexity | Space Complexity | Use Case |
|-----------|----------------|------------------|----------|
| Dijkstra's | O(V²) | O(V²) | Shortest path finding |
| Priority Scheduling | O(n²) | O(n) | Construction sequence optimization |
| Banker's Algorithm | O(n² × m) | O(n × m) | Deadlock prevention |

### Benchmarking
The project includes built-in benchmarking tools to measure:
- Algorithm execution time
- Memory usage
- Scalability with different input sizes

## 🔧 Technical Implementation Details

### Data Structures

1. **Graph Representation**
   ```cpp
   class Graph {
       std::vector<std::vector<int>> adjacencyMatrix;
       int numVertices;
   };
   ```

2. **Road Structure**
   ```cpp
   struct Road {
       int id, distance, utility, traffic;
       int estimatedTime, deadline, priority;
       int waitingTime, completionTime;
   };
   ```

3. **Resource Matrices**
   ```cpp
   std::vector<std::vector<int>> allocation;  // Current allocation
   std::vector<std::vector<int>> maximum;     // Maximum needs
   std::vector<std::vector<int>> need;        // Remaining needs
   ```

### Key Algorithms

#### Dijkstra's Algorithm Implementation
```cpp
std::vector<int> dijkstra(int start, int end) {
    std::vector<int> distance(numVertices, INT_MAX);
    std::vector<bool> visited(numVertices, false);
    // ... implementation details
}
```

#### Priority Calculation
```cpp
int priority = (road.utility * road.traffic) / (road.distance * road.deadline);
```

#### Banker's Safety Check
```cpp
bool isSafe() {
    // Check if there exists a safe sequence
    // where all processes can complete
}
```

## 🎓 Educational Value

### Computer Science Concepts Demonstrated

1. **Graph Theory**
   - Adjacency matrix representation
   - Shortest path algorithms
   - Graph traversal techniques

2. **Operating Systems**
   - Process scheduling
   - Resource allocation
   - Deadlock prevention

3. **Data Structures**
   - Vectors and matrices
   - Priority queues
   - Graph representations

4. **Algorithms**
   - Dynamic programming (Dijkstra's)
   - Greedy algorithms (Priority scheduling)
   - Safety algorithms (Banker's)

### Real-World Applications

- **Construction Management**: Optimizing road construction schedules
- **Resource Planning**: Efficient allocation of construction resources
- **Project Management**: Meeting deadlines and managing priorities
- **Transportation Planning**: Finding optimal routes and sequences

## 🤝 Contributing

We welcome contributions! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch**
   ```cmd
   git checkout -b feature/your-feature-name
   ```
3. **Make your changes**
4. **Add tests** for new functionality
5. **Update documentation** if needed
6. **Submit a pull request**

### Development Guidelines

- Follow C++17 standards
- Add comprehensive comments
- Include unit tests for new features
- Update documentation for API changes
- Ensure cross-platform compatibility

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **Algorithm Implementations**: Based on classical computer science algorithms
- **Modern C++ Practices**: Following current C++ best practices
- **Educational Focus**: Designed for learning and understanding
- **Open Source Community**: Built with open source tools and libraries

## 📞 Support

If you encounter any issues or have questions:

1. Check the test plan for common scenarios
2. Review the code comments for implementation details
3. Run the demo programs to see expected behavior
4. Open an issue on the repository

---

**Happy Learning! 🎓**

This project demonstrates how theoretical computer science concepts can be applied to solve real-world problems in construction and resource management. 