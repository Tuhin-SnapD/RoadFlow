#include "Queue.h"
#include <iostream>

Queue::Queue(size_t size) : capacity(size), front(0), rear(-1) {
    data.resize(capacity);
}

void Queue::enqueue(int value) {
    if (isFull()) {
        throw std::overflow_error("Queue is full");
    }
    
    rear = (rear + 1) % capacity;
    data[rear] = value;
}

int Queue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    
    int value = data[front];
    if (front == rear) {
        // Queue becomes empty
        front = 0;
        rear = -1;
    } else {
        front = (front + 1) % capacity;
    }
    
    return value;
}

int Queue::removeAt(size_t position) {
    if (isEmpty() || position >= size()) {
        throw std::out_of_range("Invalid position");
    }
    
    size_t actualPos = (front + position) % capacity;
    int value = data[actualPos];
    
    // Shift elements to fill the gap
    for (size_t i = position; i < size() - 1; ++i) {
        size_t current = (front + i) % capacity;
        size_t next = (front + i + 1) % capacity;
        data[current] = data[next];
    }
    
    if (front == rear) {
        // Queue becomes empty
        front = 0;
        rear = -1;
    } else {
        rear = (rear - 1 + capacity) % capacity;
    }
    
    return value;
}

bool Queue::isEmpty() const {
    return rear == -1;
}

bool Queue::isFull() const {
    return size() == capacity;
}

size_t Queue::size() const {
    if (isEmpty()) {
        return 0;
    }
    
    if (rear >= front) {
        return rear - front + 1;
    } else {
        return capacity - front + rear + 1;
    }
}

void Queue::display() const {
    if (isEmpty()) {
        std::cout << "Queue is empty";
        return;
    }
    
    size_t count = size();
    for (size_t i = 0; i < count; ++i) {
        size_t index = (front + i) % capacity;
        std::cout << data[index];
        if (i < count - 1) {
            std::cout << " ";
        }
    }
} 