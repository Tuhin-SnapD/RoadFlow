#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <iomanip>

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
    std::cout << "3. Exit\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "Enter your choice (1-3): ";
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
    std::cin >> numRoads;
    
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
        int numCities, numRoutes;
        std::cout << "Enter number of cities (number them from 0): ";
        std::cin >> numCities;
        
        std::cout << "Enter number of routes: ";
        std::cin >> numRoutes;
        
        Graph graph(numCities);
        
        // Add routes to graph
        for (int j = 0; j < numRoutes; ++j) {
            int city1, city2, distance;
            std::cout << "Enter route " << (j + 1) << " (city1 city2 distance): ";
            std::cin >> city1 >> city2 >> distance;
            graph.addEdge(city1, city2, distance);
        }
        
        // Find shortest path
        int startCity, endCity;
        std::cout << "Enter start city: ";
        std::cin >> startCity;
        std::cout << "Enter destination city: ";
        std::cin >> endCity;
        
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
        
        std::cout << "Enter utility of the road (in days): ";
        std::cin >> road.utility;
        
        std::cout << "Enter traffic impact (in days): ";
        std::cin >> road.traffic;
        
        std::cout << "Enter estimated construction time (in days): ";
        std::cin >> road.estimatedTime;
        
        std::cout << "Enter deadline (in days): ";
        std::cin >> road.deadline;
        
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
    
    int numRoads, numResources;
    std::cout << "Enter number of roads: ";
    std::cin >> numRoads;
    
    std::cout << "Enter number of resource types: ";
    std::cin >> numResources;
    
    if (numRoads <= 0 || numResources <= 0) {
        std::cout << "Invalid input!\n";
        return;
    }
    
    BankersAlgorithm banker(numRoads, numResources);
    
    // Input allocation matrix
    std::vector<std::vector<int>> allocation(numRoads, std::vector<int>(numResources));
    std::cout << "\nEnter allocation matrix:\n";
    for (int i = 0; i < numRoads; ++i) {
        std::cout << "Road R" << i << " allocation: ";
        for (int j = 0; j < numResources; ++j) {
            std::cin >> allocation[i][j];
        }
    }
    banker.setAllocation(allocation);
    
    // Input maximum matrix
    std::vector<std::vector<int>> maximum(numRoads, std::vector<int>(numResources));
    std::cout << "\nEnter maximum need matrix:\n";
    for (int i = 0; i < numRoads; ++i) {
        std::cout << "Road R" << i << " maximum: ";
        for (int j = 0; j < numResources; ++j) {
            std::cin >> maximum[i][j];
        }
    }
    banker.setMaximum(maximum);
    
    // Input available resources
    std::vector<int> available(numResources);
    std::cout << "\nEnter available resources: ";
    for (int j = 0; j < numResources; ++j) {
        std::cin >> available[j];
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
            case 3:
                std::cout << "Thank you for using Road Construction Scheduling System!\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please enter 1, 2, or 3.\n";
                break;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    
    return 0;
} 