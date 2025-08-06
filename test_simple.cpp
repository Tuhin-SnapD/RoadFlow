#include <iostream>
#include "RoadScheduler.h"
#include "Graph.h"

int main() {
    std::cout << "Testing Road Construction System..." << std::endl;
    
    // Test Graph functionality
    Graph graph(3);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 5);
    
    auto result = graph.findShortestPath(0, 2);
    std::cout << "Shortest path from 0 to 2: " << result.first << " km" << std::endl;
    
    // Test RoadScheduler functionality
    RoadScheduler scheduler;
    
    Road road1;
    road1.id = 1;
    road1.distance = 10;
    road1.utility = 5;
    road1.traffic = 2;
    road1.estimatedTime = 10;
    road1.deadline = 15;
    
    Road road2;
    road2.id = 2;
    road2.distance = 20;
    road2.utility = 3;
    road2.traffic = 1;
    road2.estimatedTime = 8;
    road2.deadline = 20;
    
    scheduler.addRoad(road1);
    scheduler.addRoad(road2);
    
    scheduler.schedule();
    scheduler.displayResults();
    
    std::cout << "Test completed successfully!" << std::endl;
    return 0;
} 