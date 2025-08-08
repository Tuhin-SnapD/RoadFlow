#pragma once

#include <vector>
#include <string>

/**
 * @brief Represents a road construction project
 */
struct Road {
    int id;
    int distance;           // Shortest path distance from Dijkstra's algorithm
    int utility;           // Utility value in days
    int traffic;           // Traffic impact in days
    int estimatedTime;     // Estimated construction time in days
    int deadline;          // Deadline in days
    int priority;          // Calculated priority
    int waitingTime;       // Waiting time
    int completionTime;    // Total completion time
};

/**
 * @brief Handles priority-based scheduling for road construction projects
 * 
 * This class implements a priority scheduling algorithm that considers
 * multiple factors including distance, utility, traffic, and deadlines
 * to determine the optimal construction sequence.
 */
class RoadScheduler {
private:
    std::vector<Road> roads;

    /**
     * @brief Calculates priorities for all roads based on multiple factors
     */
    void calculatePriorities();

    /**
     * @brief Finds the road with maximum priority
     * @return Index of road with highest priority
     */
    int findMaxPriority() const;

    /**
     * @brief Calculates waiting and completion times
     */
    void calculateTimes();

public:
    /**
     * @brief Adds a road to the scheduler
     * @param road Road to add
     */
    void addRoad(const Road& road);

    /**
     * @brief Runs the priority scheduling algorithm
     */
    void schedule();

    /**
     * @brief Displays the scheduling results
     */
    void displayResults() const;

    /**
     * @brief Checks if all deadlines can be met
     * @return true if all deadlines can be met, false otherwise
     */
    bool checkDeadlines() const;

    /**
     * @brief Gets the optimal construction sequence
     * @return Vector of road IDs in optimal order
     */
    std::vector<int> getOptimalSequence() const;

    /**
     * @brief Gets average turnaround time
     * @return Average turnaround time in days
     */
    double getAverageTurnaroundTime() const;

    /**
     * @brief Gets average waiting time
     * @return Average waiting time in days
     */
    double getAverageWaitingTime() const;

    /**
     * @brief Clears all roads from the scheduler
     */
    void clear();
}; 