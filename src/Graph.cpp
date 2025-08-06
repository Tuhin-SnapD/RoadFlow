#include "Graph.h"
#include <iostream>
#include <algorithm>

Graph::Graph(int vertices) : numVertices(vertices) {
    adjacencyMatrix.resize(vertices, std::vector<int>(vertices, INF));
    
    // Initialize diagonal elements to 0
    for (int i = 0; i < vertices; ++i) {
        adjacencyMatrix[i][i] = 0;
    }
}

void Graph::addEdge(int from, int to, int weight) {
    if (from >= 0 && from < numVertices && to >= 0 && to < numVertices) {
        // For undirected graph, add edge in both directions
        if (adjacencyMatrix[from][to] == INF || adjacencyMatrix[from][to] > weight) {
            adjacencyMatrix[from][to] = weight;
            adjacencyMatrix[to][from] = weight;
        }
    }
}

std::pair<int, std::vector<int>> Graph::findShortestPath(int source, int destination) {
    if (source < 0 || source >= numVertices || destination < 0 || destination >= numVertices) {
        return {INF, {}};
    }

    std::vector<int> distance(numVertices, INF);
    std::vector<int> previous(numVertices, -1);
    std::vector<bool> visited(numVertices, false);

    distance[source] = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
        // Find vertex with minimum distance value among unvisited vertices
        int minDistance = INF;
        int minIndex = -1;

        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && distance[v] < minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) break;

        visited[minIndex] = true;

        // Update distance values of adjacent vertices
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && 
                adjacencyMatrix[minIndex][v] != INF && 
                distance[minIndex] != INF &&
                distance[minIndex] + adjacencyMatrix[minIndex][v] < distance[v]) {
                
                distance[v] = distance[minIndex] + adjacencyMatrix[minIndex][v];
                previous[v] = minIndex;
            }
        }
    }

    // Reconstruct path
    std::vector<int> path;
    if (distance[destination] != INF) {
        int current = destination;
        while (current != -1) {
            path.push_back(current);
            current = previous[current];
        }
        std::reverse(path.begin(), path.end());
    }

    return {distance[destination], path};
}

void Graph::printMatrix() const {
    std::cout << "Adjacency Matrix:\n";
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] == INF) {
                std::cout << "INF ";
            } else {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
} 