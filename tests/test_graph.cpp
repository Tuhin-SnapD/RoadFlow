#include <gtest/gtest.h>
#include "Graph.h"

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a test graph with 5 cities
        graph = new Graph(5);
    }

    void TearDown() override {
        delete graph;
    }

    Graph* graph;
};

TEST_F(GraphTest, ConstructorTest) {
    Graph g(3);
    EXPECT_EQ(g.getVertexCount(), 3);
}

TEST_F(GraphTest, AddEdgeTest) {
    graph->addEdge(0, 1, 10);
    graph->addEdge(1, 2, 20);
    
    // Test that edges are added correctly by checking shortest paths
    auto result1 = graph->findShortestPath(0, 1);
    EXPECT_EQ(result1.first, 10);
    
    auto result2 = graph->findShortestPath(1, 2);
    EXPECT_EQ(result2.first, 20);
}

TEST_F(GraphTest, DijkstraShortestPathTest) {
    // Create a simple graph: 0 --10-- 1 --20-- 2
    graph->addEdge(0, 1, 10);
    graph->addEdge(1, 2, 20);
    graph->addEdge(0, 2, 50); // Direct path with higher cost
    
    auto result = graph->findShortestPath(0, 2);
    
    EXPECT_EQ(result.first, 30);  // Path through city 1 (10 + 20)
}

TEST_F(GraphTest, ComplexGraphTest) {
    // Create a more complex graph
    graph->addEdge(0, 1, 4);
    graph->addEdge(0, 2, 2);
    graph->addEdge(1, 2, 1);
    graph->addEdge(1, 3, 5);
    graph->addEdge(2, 3, 8);
    graph->addEdge(2, 4, 10);
    graph->addEdge(3, 4, 2);
    
    auto result = graph->findShortestPath(0, 4);
    
    EXPECT_EQ(result.first, 10);  // 0 -> 2 -> 1 -> 3 -> 4 (2 + 1 + 5 + 2)
}

TEST_F(GraphTest, DisconnectedGraphTest) {
    // Test with disconnected components
    graph->addEdge(0, 1, 5);
    graph->addEdge(2, 3, 8);
    
    auto result = graph->findShortestPath(0, 3);
    
    EXPECT_EQ(result.first, std::numeric_limits<int>::max()); // Unreachable
}

TEST_F(GraphTest, SelfLoopTest) {
    graph->addEdge(0, 0, 5); // Self loop
    
    auto result = graph->findShortestPath(0, 0);
    
    EXPECT_EQ(result.first, 0); // Should be 0 for same vertex
}

TEST_F(GraphTest, InvalidVertexTest) {
    EXPECT_THROW(graph->addEdge(5, 0, 10), std::out_of_range);
    EXPECT_THROW(graph->addEdge(0, 5, 10), std::out_of_range);
    EXPECT_THROW(graph->findShortestPath(0, 5), std::out_of_range);
} 