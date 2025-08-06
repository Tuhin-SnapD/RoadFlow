#pragma once

#include <vector>
#include <stdexcept>

/**
 * @brief A simple queue implementation for graph algorithms
 * 
 * This class provides basic queue operations needed for
 * implementing graph traversal algorithms.
 */
class Queue {
private:
    std::vector<int> data;
    size_t front;
    size_t capacity;
    size_t rear;
    bool empty_flag;

public:
    /**
     * @brief Constructs a queue with the specified capacity
     * @param size Maximum number of elements the queue can hold
     */
    explicit Queue(size_t size = 100);

    /**
     * @brief Adds an element to the rear of the queue
     * @param value Element to add
     * @throws std::overflow_error if queue is full
     */
    void enqueue(int value);

    /**
     * @brief Removes and returns the element from the front of the queue
     * @return Front element
     * @throws std::underflow_error if queue is empty
     */
    int dequeue();

    /**
     * @brief Removes an element at a specific position
     * @param position Index of element to remove
     * @return Removed element
     */
    int removeAt(size_t position);

    /**
     * @brief Checks if the queue is empty
     * @return true if empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Checks if the queue is full
     * @return true if full, false otherwise
     */
    bool isFull() const;

    /**
     * @brief Gets the current size of the queue
     * @return Number of elements in the queue
     */
    size_t size() const;

    /**
     * @brief Displays all elements in the queue
     */
    void display() const;
}; 