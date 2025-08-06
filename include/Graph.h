#pragma once

#include <vector>
#include <limits>
#include <queue>
#include <unordered_map>

/**
 * @brief Represents a weighted graph for road network analysis
 * 
 * This class implements Dijkstra's shortest path algorithm to find
 * optimal routes between cities in a road construction network.
 */
class Graph {
private:
    std::vector<std::vector<int>> adjacencyMatrix;
    int numVertices;
    static const int INF = std::numeric_limits<int>::max();

public:
    /**
     * @brief Constructs a graph with the specified number of vertices
     * @param vertices Number of vertices (cities) in the graph
     */
    explicit Graph(int vertices);

    /**
     * @brief Adds an undirected edge between two vertices
     * @param from Source vertex
     * @param to Destination vertex
     * @param weight Weight of the edge (distance in km)
     */
    void addEdge(int from, int to, int weight);

    /**
     * @brief Finds the shortest path from source to destination using Dijkstra's algorithm
     * @param source Starting vertex
     * @param destination Target vertex
     * @return Pair containing shortest distance and path
     */
    std::pair<int, std::vector<int>> findShortestPath(int source, int destination);

    /**
     * @brief Gets the number of vertices in the graph
     * @return Number of vertices
     */
    int getVertexCount() const { return numVertices; }

    /**
     * @brief Prints the adjacency matrix for debugging
     */
    void printMatrix() const;
}; 