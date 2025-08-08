#include "RoadScheduler.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits> // Add missing include for std::numeric_limits

void RoadScheduler::addRoad(const Road& road) {
    roads.push_back(road);
}

void RoadScheduler::calculatePriorities() {
    // Calculate priorities based on utility (higher utility = higher priority)
    // Also consider traffic and distance as secondary factors
    for (auto& road : roads) {
        // Primary factor: utility (higher is better)
        // Secondary factors: traffic (higher is better), distance (lower is better)
        // Use long long to prevent overflow
        long long priority = static_cast<long long>(road.utility) * 100 + 
                           static_cast<long long>(road.traffic) * 10 - 
                           static_cast<long long>(road.distance);
        
        // Clamp to int range to prevent overflow
        if (priority > std::numeric_limits<int>::max()) {
            road.priority = std::numeric_limits<int>::max();
        } else if (priority < std::numeric_limits<int>::min()) {
            road.priority = std::numeric_limits<int>::min();
        } else {
            road.priority = static_cast<int>(priority);
        }
    }
}

int RoadScheduler::findMaxPriority() const {
    int maxPriority = -1;
    int maxIndex = -1;
    
    for (size_t i = 0; i < roads.size(); ++i) {
        if (roads[i].priority > maxPriority) {
            maxPriority = roads[i].priority;
            maxIndex = i;
        }
    }
    
    return maxIndex;
}

void RoadScheduler::calculateTimes() {
    // Store original priorities before modifying them
    std::vector<int> originalPriorities;
    for (const auto& road : roads) {
        originalPriorities.push_back(road.priority);
    }
    
    std::vector<Road> tempRoads = roads;
    int currentTime = 0;
    
    // Use a more efficient approach: sort by priority once, then process in order
    std::vector<std::pair<int, size_t>> priorityIndices;
    for (size_t i = 0; i < tempRoads.size(); ++i) {
        priorityIndices.push_back({tempRoads[i].priority, i});
    }
    
    // Sort by priority (descending order)
    std::sort(priorityIndices.begin(), priorityIndices.end(), 
              std::greater<std::pair<int, size_t>>());
    
    // Process roads in priority order
    for (const auto& [priority, index] : priorityIndices) {
        tempRoads[index].waitingTime = currentTime;
        currentTime += tempRoads[index].estimatedTime;
        tempRoads[index].completionTime = currentTime;
    }
    
    roads = tempRoads;
    
    // Restore original priorities for getOptimalSequence
    for (size_t i = 0; i < roads.size(); ++i) {
        roads[i].priority = originalPriorities[i];
    }
}

void RoadScheduler::schedule() {
    calculatePriorities();
    calculateTimes();
}

void RoadScheduler::displayResults() const {
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "PRIORITY SCHEDULING RESULTS\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "HIGHER THE PRIORITY GREATER WILL BE THE PREFERENCE\n\n";
    
    std::cout << std::left << std::setw(8) << "ROAD" 
              << std::setw(18) << "PRIORITY" 
              << std::setw(15) << "ESTIMATED TIME" 
              << std::setw(15) << "WAITING TIME" 
              << std::setw(15) << "COMPLETION TIME" << "\n";
    std::cout << std::string(80, '-') << "\n";
    
    for (const auto& road : roads) {
        std::cout << std::left << std::setw(8) << ("Road" + std::to_string(road.id))
                  << std::setw(18) << road.priority
                  << std::setw(15) << (std::to_string(road.estimatedTime) + " days")
                  << std::setw(15) << (std::to_string(road.waitingTime) + " days")
                  << std::setw(15) << (std::to_string(road.completionTime) + " days") << "\n";
    }
    
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Average Turnaround Time: " << getAverageTurnaroundTime() << " days\n";
    std::cout << "Average Waiting Time: " << getAverageWaitingTime() << " days\n";
    
    if (checkDeadlines()) {
        std::cout << "\n[OK] All deadlines can be met with the current schedule.\n";
    } else {
        std::cout << "\n[WARNING] Some deadlines may be compromised.\n";
    }
    
    std::cout << "\nOptimal Construction Sequence: ";
    auto sequence = getOptimalSequence();
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << "Road" << sequence[i];
        if (i < sequence.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n" << std::string(80, '=') << "\n";
}

bool RoadScheduler::checkDeadlines() const {
    for (const auto& road : roads) {
        if (road.completionTime > road.deadline) {
            return false;
        }
    }
    return true;
}

std::vector<int> RoadScheduler::getOptimalSequence() const {
    std::vector<std::pair<int, int>> roadPriorities;
    for (const auto& road : roads) {
        roadPriorities.push_back({road.priority, road.id});
    }
    
    std::sort(roadPriorities.begin(), roadPriorities.end(), 
              std::greater<std::pair<int, int>>());
    
    std::vector<int> sequence;
    for (const auto& pair : roadPriorities) {
        sequence.push_back(pair.second);
    }
    
    return sequence;
}

double RoadScheduler::getAverageTurnaroundTime() const {
    if (roads.empty()) return 0.0;
    
    int totalTurnaround = 0;
    for (const auto& road : roads) {
        totalTurnaround += road.completionTime;
    }
    
    return static_cast<double>(totalTurnaround) / roads.size();
}

double RoadScheduler::getAverageWaitingTime() const {
    if (roads.empty()) return 0.0;
    
    int totalWaiting = 0;
    for (const auto& road : roads) {
        totalWaiting += road.waitingTime;
    }
    
    return static_cast<double>(totalWaiting) / roads.size();
}

void RoadScheduler::clear() {
    roads.clear();
} 