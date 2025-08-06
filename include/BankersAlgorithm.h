#pragma once

#include <vector>
#include <string>

/**
 * @brief Implements Banker's Algorithm for resource allocation in road construction
 * 
 * This class ensures safe resource allocation by preventing deadlocks
 * in road construction projects where multiple resources are required.
 */
class BankersAlgorithm {
private:
    std::vector<std::vector<int>> allocation;  // Currently allocated resources
    std::vector<std::vector<int>> maximum;     // Maximum resource needs
    std::vector<std::vector<int>> need;        // Remaining resource needs
    std::vector<int> available;                // Available resources
    std::vector<bool> finished;                // Track completed processes
    int numRoads;
    int numResources;

    /**
     * @brief Calculates the need matrix
     */
    void calculateNeed();

    /**
     * @brief Checks if a road can be allocated resources
     * @param roadIndex Index of the road to check
     * @return true if resources can be allocated, false otherwise
     */
    bool canAllocate(int roadIndex) const;

public:
    /**
     * @brief Constructs a Banker's Algorithm instance
     * @param roads Number of roads (processes)
     * @param resources Number of resource types
     */
    BankersAlgorithm(int roads, int resources);

    /**
     * @brief Sets the allocation matrix
     * @param alloc Allocation matrix
     */
    void setAllocation(const std::vector<std::vector<int>>& alloc);

    /**
     * @brief Sets the maximum need matrix
     * @param max Maximum need matrix
     */
    void setMaximum(const std::vector<std::vector<int>>& max);

    /**
     * @brief Sets the available resources
     * @param avail Available resources vector
     */
    void setAvailable(const std::vector<int>& avail);

    /**
     * @brief Runs the Banker's Algorithm to find a safe sequence
     * @return Vector containing safe sequence of road indices, empty if unsafe
     */
    std::vector<int> findSafeSequence();

    /**
     * @brief Checks if the current state is safe
     * @return true if safe, false otherwise
     */
    bool isSafe() const;

    /**
     * @brief Displays the need matrix
     */
    void displayNeedMatrix() const;

    /**
     * @brief Displays the allocation matrix
     */
    void displayAllocationMatrix() const;

    /**
     * @brief Displays the maximum matrix
     */
    void displayMaximumMatrix() const;

    /**
     * @brief Displays available resources
     */
    void displayAvailable() const;
}; 