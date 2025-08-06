#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "RoadScheduler.h"
#include "BankersAlgorithm.h"

/**
 * @brief Displays the main menu
 */
void displayMenu() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "           ROAD CONSTRUCTION SCHEDULING SYSTEM\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "1. Priority Scheduling Algorithm\n";
    std::cout << "2. Banker's Algorithm (Resource Allocation)\n";
    std::cout << "3. Load from file (Priority Scheduling)\n";
    std::cout << "4. Load from file (Banker's Algorithm)\n";
    std::cout << "5. Quick demo (Priority Scheduling)\n";
    std::cout << "6. Quick demo (Banker's Algorithm)\n";
    std::cout << "7. Exit\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "Enter your choice (1-7): ";
}

/**
 * @brief Reads a line of integers from input
 */
std::vector<int> readIntLine() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::vector<int> values;
    int value;
    while (iss >> value) {
        values.push_back(value);
    }
    return values;
}

/**
 * @brief Validates and reads a single integer with error handling
 */
int readInt(const std::string& prompt, int minValue = 0) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a valid number >= " << minValue << ".\n";
    }
}

/**
 * @brief Loads road data from file for Priority Scheduling
 */
bool loadPrioritySchedulingFromFile(const std::string& filename, RoadScheduler& scheduler) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << "\n";
        return false;
    }

    int numRoads;
    file >> numRoads;
    if (numRoads <= 0) {
        std::cout << "Error: Invalid number of roads in file\n";
        return false;
    }

    for (int i = 0; i < numRoads; ++i) {
        int numCities, numRoutes;
        file >> numCities >> numRoutes;
        
        if (numCities <= 0 || numRoutes <= 0) {
            std::cout << "Error: Invalid cities or routes count for road " << (i + 1) << "\n";
            return false;
        }

        Graph graph(numCities);
        
        // Read routes
        for (int j = 0; j < numRoutes; ++j) {
            int city1, city2, distance;
            file >> city1 >> city2 >> distance;
            
            if (city1 < 0 || city1 >= numCities || city2 < 0 || city2 >= numCities || distance <= 0) {
                std::cout << "Error: Invalid route data for road " << (i + 1) << ", route " << (j + 1) << "\n";
                return false;
            }
            
            graph.addEdge(city1, city2, distance);
        }
        
        // Read start and end cities
        int startCity, endCity;
        file >> startCity >> endCity;
        
        if (startCity < 0 || startCity >= numCities || endCity < 0 || endCity >= numCities) {
            std::cout << "Error: Invalid start/end cities for road " << (i + 1) << "\n";
            return false;
        }
        
        auto result = graph.findShortestPath(startCity, endCity);
        int shortestDistance = result.first;
        
        if (shortestDistance == std::numeric_limits<int>::max()) {
            std::cout << "Error: No path exists for road " << (i + 1) << "\n";
            return false;
        }
        
        // Read road parameters
        Road road;
        road.id = i + 1;
        road.distance = shortestDistance;
        file >> road.utility >> road.traffic >> road.estimatedTime >> road.deadline;
        
        if (road.utility < 0 || road.traffic < 0 || road.estimatedTime <= 0 || road.deadline <= 0) {
            std::cout << "Error: Invalid road parameters for road " << (i + 1) << "\n";
            return false;
        }
        
        scheduler.addRoad(road);
    }
    
    file.close();
    return true;
}

/**
 * @brief Loads data from file for Banker's Algorithm
 */
bool loadBankersFromFile(const std::string& filename, BankersAlgorithm& banker) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << "\n";
        return false;
    }

    int numRoads, numResources;
    file >> numRoads >> numResources;
    
    if (numRoads <= 0 || numResources <= 0) {
        std::cout << "Error: Invalid number of roads or resources\n";
        return false;
    }

    banker = BankersAlgorithm(numRoads, numResources);
    
    // Read allocation matrix
    std::vector<std::vector<int>> allocation(numRoads, std::vector<int>(numResources));
    for (int i = 0; i < numRoads; ++i) {
        for (int j = 0; j < numResources; ++j) {
            file >> allocation[i][j];
            if (allocation[i][j] < 0) {
                std::cout << "Error: Invalid allocation value\n";
                return false;
            }
        }
    }
    banker.setAllocation(allocation);
    
    // Read maximum matrix
    std::vector<std::vector<int>> maximum(numRoads, std::vector<int>(numResources));
    for (int i = 0; i < numRoads; ++i) {
        for (int j = 0; j < numResources; ++j) {
            file >> maximum[i][j];
            if (maximum[i][j] < 0) {
                std::cout << "Error: Invalid maximum value\n";
                return false;
            }
        }
    }
    banker.setMaximum(maximum);
    
    // Read available resources
    std::vector<int> available(numResources);
    for (int j = 0; j < numResources; ++j) {
        file >> available[j];
        if (available[j] < 0) {
            std::cout << "Error: Invalid available resource value\n";
            return false;
        }
    }
    banker.setAvailable(available);
    
    file.close();
    return true;
}

/**
 * @brief Handles the Priority Scheduling Algorithm
 */
void runPriorityScheduling() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "           PRIORITY SCHEDULING ALGORITHM\n";
    std::cout << std::string(60, '=') << "\n";
    
    int numRoads;
    std::cout << "Enter the number of roads: ";
    if (!(std::cin >> numRoads)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a positive number.\n";
        return;
    }
    
    if (numRoads <= 0) {
        std::cout << "Invalid number of roads!\n";
        return;
    }
    
    RoadScheduler scheduler;
    
    for (int i = 0; i < numRoads; ++i) {
        std::cout << "\n" << std::string(40, '-') << "\n";
        std::cout << "Enter details for Road " << (i + 1) << ":\n";
        std::cout << std::string(40, '-') << "\n";
        
        // Create graph for this road
        int numCities = readInt("Enter number of cities (number them from 0): ", 1);
        int numRoutes = readInt("Enter number of routes: ", 1);
        
        Graph graph(numCities);
        
        // Add routes to graph
        std::cout << "Enter all routes (one per line, format: city1 city2 distance):\n";
        std::cout << "Example: 0 1 10\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
        
        for (int j = 0; j < numRoutes; ++j) {
            std::cout << "Route " << (j + 1) << ": ";
            std::vector<int> routeData = readIntLine();
            
            if (routeData.size() != 3) {
                std::cout << "Invalid input! Please enter exactly 3 numbers (city1 city2 distance).\n";
                j--; // Retry this route
                continue;
            }
            
            int city1 = routeData[0], city2 = routeData[1], distance = routeData[2];
            
            // Validate city indices
            if (city1 < 0 || city1 >= numCities || city2 < 0 || city2 >= numCities) {
                std::cout << "Invalid city indices! Cities must be between 0 and " << (numCities - 1) << ".\n";
                j--; // Retry this route
                continue;
            }
            
            // Validate distance
            if (distance <= 0) {
                std::cout << "Invalid distance! Distance must be positive.\n";
                j--; // Retry this route
                continue;
            }
            
            graph.addEdge(city1, city2, distance);
        }
        
        // Find shortest path
        int startCity = readInt("Enter start city: ");
        if (startCity < 0 || startCity >= numCities) {
            std::cout << "Invalid start city! Must be between 0 and " << (numCities - 1) << ".\n";
            return;
        }
        
        int endCity = readInt("Enter destination city: ");
        if (endCity < 0 || endCity >= numCities) {
            std::cout << "Invalid destination city! Must be between 0 and " << (numCities - 1) << ".\n";
            return;
        }
        
        auto result = graph.findShortestPath(startCity, endCity);
        int shortestDistance = result.first;
        
        if (shortestDistance == std::numeric_limits<int>::max()) {
            std::cout << "No path exists between the specified cities!\n";
            return;
        }
        
        std::cout << "Shortest distance: " << shortestDistance << " km\n";
        
        // Get road parameters
        Road road;
        road.id = i + 1;
        road.distance = shortestDistance;
        
        std::cout << "Enter road parameters (utility traffic_impact construction_time deadline):\n";
        std::cout << "Example: 5 2 10 15\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
        
        std::vector<int> params = readIntLine();
        if (params.size() != 4) {
            std::cout << "Invalid input! Please enter exactly 4 numbers.\n";
            return;
        }
        
        road.utility = params[0];
        road.traffic = params[1];
        road.estimatedTime = params[2];
        road.deadline = params[3];
        
        if (road.utility < 0 || road.traffic < 0 || road.estimatedTime <= 0 || road.deadline <= 0) {
            std::cout << "Invalid parameters! Utility and traffic must be non-negative, construction time and deadline must be positive.\n";
            return;
        }
        
        scheduler.addRoad(road);
    }
    
    // Run scheduling algorithm
    scheduler.schedule();
    scheduler.displayResults();
}

/**
 * @brief Handles the Banker's Algorithm
 */
void runBankersAlgorithm() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "           BANKER'S ALGORITHM\n";
    std::cout << std::string(60, '=') << "\n";
    
    int numRoads = readInt("Enter number of roads: ", 1);
    int numResources = readInt("Enter number of resource types: ", 1);
    
    BankersAlgorithm banker(numRoads, numResources);
    
    // Input allocation matrix
    std::vector<std::vector<int>> allocation(numRoads, std::vector<int>(numResources));
    std::cout << "\nEnter allocation matrix (one row per line):\n";
    std::cout << "Example for 2 roads, 2 resources: 0 1\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
    
    for (int i = 0; i < numRoads; ++i) {
        std::cout << "Road R" << i << " allocation: ";
        std::vector<int> row = readIntLine();
        if (static_cast<int>(row.size()) != numResources) {
            std::cout << "Invalid input! Please enter exactly " << numResources << " numbers.\n";
            return;
        }
        for (int j = 0; j < numResources; ++j) {
            if (row[j] < 0) {
                std::cout << "Invalid allocation! Must be non-negative.\n";
                return;
            }
            allocation[i][j] = row[j];
        }
    }
    banker.setAllocation(allocation);
    
    // Input maximum matrix
    std::vector<std::vector<int>> maximum(numRoads, std::vector<int>(numResources));
    std::cout << "\nEnter maximum need matrix (one row per line):\n";
    std::cout << "Example for 2 roads, 2 resources: 1 2\n";
    
    for (int i = 0; i < numRoads; ++i) {
        std::cout << "Road R" << i << " maximum: ";
        std::vector<int> row = readIntLine();
        if (static_cast<int>(row.size()) != numResources) {
            std::cout << "Invalid input! Please enter exactly " << numResources << " numbers.\n";
            return;
        }
        for (int j = 0; j < numResources; ++j) {
            if (row[j] < 0) {
                std::cout << "Invalid maximum! Must be non-negative.\n";
                return;
            }
            maximum[i][j] = row[j];
        }
    }
    banker.setMaximum(maximum);
    
    // Input available resources
    std::vector<int> available(numResources);
    std::cout << "\nEnter available resources (space-separated): ";
    std::cout << "Example for 2 resources: 1 1\n";
    
    std::vector<int> availData = readIntLine();
    if (static_cast<int>(availData.size()) != numResources) {
        std::cout << "Invalid input! Please enter exactly " << numResources << " numbers.\n";
        return;
    }
    for (int j = 0; j < numResources; ++j) {
        if (availData[j] < 0) {
            std::cout << "Invalid available resource! Must be non-negative.\n";
            return;
        }
        available[j] = availData[j];
    }
    banker.setAvailable(available);
    
    // Display matrices
    banker.displayAllocationMatrix();
    banker.displayMaximumMatrix();
    banker.displayNeedMatrix();
    banker.displayAvailable();
    
    // Find safe sequence
    std::vector<int> safeSequence = banker.findSafeSequence();
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "           RESULT\n";
    std::cout << std::string(60, '=') << "\n";
    
    if (!safeSequence.empty()) {
        std::cout << "✓ SAFE SEQUENCE EXISTS:\n";
        for (size_t i = 0; i < safeSequence.size(); ++i) {
            std::cout << "R" << safeSequence[i];
            if (i < safeSequence.size() - 1) {
                std::cout << " → ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "✗ NO SAFE SEQUENCE EXISTS\n";
        std::cout << "System is in an unsafe state!\n";
    }
    std::cout << std::string(60, '=') << "\n";
}

/**
 * @brief Runs a quick demo for Priority Scheduling
 */
void runPrioritySchedulingDemo() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "           PRIORITY SCHEDULING DEMO\n";
    std::cout << std::string(60, '=') << "\n";
    
    RoadScheduler scheduler;
    
    // Demo road 1: Simple 2-city road
    Graph graph1(2);
    graph1.addEdge(0, 1, 10);
    auto result1 = graph1.findShortestPath(0, 1);
    
    Road road1;
    road1.id = 1;
    road1.distance = result1.first;
    road1.utility = 5;
    road1.traffic = 2;
    road1.estimatedTime = 10;
    road1.deadline = 15;
    scheduler.addRoad(road1);
    
    // Demo road 2: Another 2-city road
    Graph graph2(2);
    graph2.addEdge(0, 1, 20);
    auto result2 = graph2.findShortestPath(0, 1);
    
    Road road2;
    road2.id = 2;
    road2.distance = result2.first;
    road2.utility = 3;
    road2.traffic = 1;
    road2.estimatedTime = 8;
    road2.deadline = 20;
    scheduler.addRoad(road2);
    
    std::cout << "Demo data loaded successfully!\n";
    scheduler.schedule();
    scheduler.displayResults();
}

/**
 * @brief Runs a quick demo for Banker's Algorithm
 */
void runBankersDemo() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "           BANKER'S ALGORITHM DEMO\n";
    std::cout << std::string(60, '=') << "\n";
    
    BankersAlgorithm banker(2, 2);
    
    // Demo allocation matrix
    std::vector<std::vector<int>> allocation = {{0, 1}, {1, 0}};
    banker.setAllocation(allocation);
    
    // Demo maximum matrix
    std::vector<std::vector<int>> maximum = {{1, 2}, {2, 1}};
    banker.setMaximum(maximum);
    
    // Demo available resources
    std::vector<int> available = {1, 1};
    banker.setAvailable(available);
    
    std::cout << "Demo data loaded successfully!\n";
    
    // Display matrices
    banker.displayAllocationMatrix();
    banker.displayMaximumMatrix();
    banker.displayNeedMatrix();
    banker.displayAvailable();
    
    // Find safe sequence
    std::vector<int> safeSequence = banker.findSafeSequence();
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "           RESULT\n";
    std::cout << std::string(60, '=') << "\n";
    
    if (!safeSequence.empty()) {
        std::cout << "✓ SAFE SEQUENCE EXISTS:\n";
        for (size_t i = 0; i < safeSequence.size(); ++i) {
            std::cout << "R" << safeSequence[i];
            if (i < safeSequence.size() - 1) {
                std::cout << " → ";
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "✗ NO SAFE SEQUENCE EXISTS\n";
        std::cout << "System is in an unsafe state!\n";
    }
    std::cout << std::string(60, '=') << "\n";
}

/**
 * @brief Main function
 */
int main() {
    std::cout << "Welcome to Road Construction Scheduling System!\n";
    
    while (true) {
        displayMenu();
        
        int choice;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                runPriorityScheduling();
                break;
            case 2:
                runBankersAlgorithm();
                break;
            case 3: {
                std::string filename;
                std::cout << "Enter filename to load Priority Scheduling data: ";
                std::cin >> filename;
                RoadScheduler scheduler;
                if (loadPrioritySchedulingFromFile(filename, scheduler)) {
                    std::cout << "Data loaded from " << filename << " successfully!\n";
                    scheduler.schedule();
                    scheduler.displayResults();
                }
                break;
            }
            case 4: {
                std::string filename;
                std::cout << "Enter filename to load Banker's Algorithm data: ";
                std::cin >> filename;
                BankersAlgorithm banker(0, 0); // Will be properly initialized in loadBankersFromFile
                if (loadBankersFromFile(filename, banker)) {
                    std::cout << "Data loaded from " << filename << " successfully!\n";
                    
                    // Display matrices
                    banker.displayAllocationMatrix();
                    banker.displayMaximumMatrix();
                    banker.displayNeedMatrix();
                    banker.displayAvailable();
                    
                    // Find safe sequence
                    std::vector<int> safeSequence = banker.findSafeSequence();
                    
                    std::cout << "\n" << std::string(60, '=') << "\n";
                    std::cout << "           RESULT\n";
                    std::cout << std::string(60, '=') << "\n";
                    
                    if (!safeSequence.empty()) {
                        std::cout << "✓ SAFE SEQUENCE EXISTS:\n";
                        for (size_t i = 0; i < safeSequence.size(); ++i) {
                            std::cout << "R" << safeSequence[i];
                            if (i < safeSequence.size() - 1) {
                                std::cout << " → ";
                            }
                        }
                        std::cout << "\n";
                    } else {
                        std::cout << "✗ NO SAFE SEQUENCE EXISTS\n";
                        std::cout << "System is in an unsafe state!\n";
                    }
                    std::cout << std::string(60, '=') << "\n";
                }
                break;
            }
            case 5:
                runPrioritySchedulingDemo();
                break;
            case 6:
                runBankersDemo();
                break;
            case 7:
                std::cout << "Thank you for using Road Construction Scheduling System!\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please enter 1, 2, 3, 4, 5, 6, or 7.\n";
                break;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    
    return 0;
} 