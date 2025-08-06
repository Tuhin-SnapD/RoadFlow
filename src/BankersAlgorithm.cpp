#include "BankersAlgorithm.h"
#include <iostream>
#include <iomanip>

BankersAlgorithm::BankersAlgorithm(int roads, int resources) 
    : numRoads(roads), numResources(resources) {
    
    allocation.resize(roads, std::vector<int>(resources, 0));
    maximum.resize(roads, std::vector<int>(resources, 0));
    need.resize(roads, std::vector<int>(resources, 0));
    available.resize(resources, 0);
    finished.resize(roads, false);
}

void BankersAlgorithm::setAllocation(const std::vector<std::vector<int>>& alloc) {
    allocation = alloc;
    calculateNeed();
}

void BankersAlgorithm::setMaximum(const std::vector<std::vector<int>>& max) {
    maximum = max;
    calculateNeed();
}

void BankersAlgorithm::setAvailable(const std::vector<int>& avail) {
    available = avail;
}

void BankersAlgorithm::calculateNeed() {
    for (int i = 0; i < numRoads; ++i) {
        for (int j = 0; j < numResources; ++j) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool BankersAlgorithm::canAllocate(int roadIndex) const {
    for (int j = 0; j < numResources; ++j) {
        if (need[roadIndex][j] > available[j]) {
            return false;
        }
    }
    return true;
}

std::vector<int> BankersAlgorithm::findSafeSequence() {
    std::vector<int> safeSequence;
    std::vector<int> work = available;
    std::vector<bool> finish = finished;
    
    int count = 0;
    while (count < numRoads) {
        bool found = false;
        
        for (int i = 0; i < numRoads; ++i) {
            if (!finish[i] && canAllocate(i)) {
                // Allocate resources
                for (int j = 0; j < numResources; ++j) {
                    work[j] += allocation[i][j];
                }
                
                safeSequence.push_back(i);
                finish[i] = true;
                found = true;
                count++;
            }
        }
        
        if (!found) {
            // No safe sequence exists
            return {};
        }
    }
    
    return safeSequence;
}

bool BankersAlgorithm::isSafe() const {
    return !findSafeSequence().empty();
}

void BankersAlgorithm::displayNeedMatrix() const {
    std::cout << "\nNeed Matrix:\n";
    std::cout << std::string(50, '-') << "\n";
    
    for (int i = 0; i < numRoads; ++i) {
        std::cout << "Road R" << i << ": ";
        for (int j = 0; j < numResources; ++j) {
            std::cout << std::setw(4) << need[i][j];
            if (j < numResources - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::string(50, '-') << "\n";
}

void BankersAlgorithm::displayAllocationMatrix() const {
    std::cout << "\nAllocation Matrix:\n";
    std::cout << std::string(50, '-') << "\n";
    
    for (int i = 0; i < numRoads; ++i) {
        std::cout << "Road R" << i << ": ";
        for (int j = 0; j < numResources; ++j) {
            std::cout << std::setw(4) << allocation[i][j];
            if (j < numResources - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::string(50, '-') << "\n";
}

void BankersAlgorithm::displayMaximumMatrix() const {
    std::cout << "\nMaximum Need Matrix:\n";
    std::cout << std::string(50, '-') << "\n";
    
    for (int i = 0; i < numRoads; ++i) {
        std::cout << "Road R" << i << ": ";
        for (int j = 0; j < numResources; ++j) {
            std::cout << std::setw(4) << maximum[i][j];
            if (j < numResources - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::string(50, '-') << "\n";
}

void BankersAlgorithm::displayAvailable() const {
    std::cout << "\nAvailable Resources:\n";
    std::cout << std::string(30, '-') << "\n";
    
    for (int j = 0; j < numResources; ++j) {
        std::cout << "Resource " << j << ": " << available[j];
        if (j < numResources - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n" << std::string(30, '-') << "\n";
} 