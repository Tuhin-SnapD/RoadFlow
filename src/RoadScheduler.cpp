#include "RoadScheduler.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void RoadScheduler::addRoad(const Road& road) {
    roads.push_back(road);
}

void RoadScheduler::calculatePriorities() {
    totalSum = 0;
    
    // Calculate sum of all factors
    for (const auto& road : roads) {
        int prioritySum = road.distance + road.utility + road.traffic;
        totalSum += prioritySum;
    }
    
    // Calculate priorities as percentages
    for (auto& road : roads) {
        int prioritySum = road.distance + road.utility + road.traffic;
        road.priority = (prioritySum * 100) / totalSum;
    }
    
    // Handle ties by considering utility, traffic, and distance
    for (size_t i = 0; i < roads.size(); ++i) {
        for (size_t j = i + 1; j < roads.size(); ++j) {
            if (roads[i].priority == roads[j].priority) {
                if (roads[i].utility > roads[j].utility) {
                    ++roads[i].priority;
                } else if (roads[j].utility > roads[i].utility) {
                    ++roads[j].priority;
                } else if (roads[i].traffic > roads[j].traffic) {
                    ++roads[i].priority;
                } else if (roads[j].traffic > roads[i].traffic) {
                    ++roads[j].priority;
                } else if (roads[i].distance > roads[j].distance) {
                    ++roads[i].priority;
                } else if (roads[j].distance > roads[i].distance) {
                    ++roads[j].priority;
                } else {
                    ++roads[i].priority;
                }
            }
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
    std::vector<Road> tempRoads = roads;
    int currentTime = 0;
    
    for (size_t i = 0; i < roads.size(); ++i) {
        int maxIndex = findMaxPriority();
        if (maxIndex != -1) {
            tempRoads[maxIndex].waitingTime = currentTime;
            currentTime += tempRoads[maxIndex].estimatedTime;
            tempRoads[maxIndex].completionTime = currentTime;
            tempRoads[maxIndex].priority = -1; // Mark as processed
        }
    }
    
    roads = tempRoads;
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
        std::cout << "\n✓ All deadlines can be met with the current schedule.\n";
    } else {
        std::cout << "\n⚠ Some deadlines may be compromised.\n";
    }
    
    std::cout << "\nOptimal Construction Sequence: ";
    auto sequence = getOptimalSequence();
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << "Road" << sequence[i];
        if (i < sequence.size() - 1) {
            std::cout << " → ";
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
    totalSum = 0;
} 