#include <gtest/gtest.h>
#include "RoadScheduler.h"
#include "Graph.h"

class RoadSchedulerTest : public ::testing::Test {
protected:
    void SetUp() override {
        scheduler = new RoadScheduler();
    }

    void TearDown() override {
        delete scheduler;
    }

    RoadScheduler* scheduler;
};

TEST_F(RoadSchedulerTest, AddRoadTest) {
    Road road{1, 10, 5, 2, 8, 15, 0, 0, 0};
    scheduler->addRoad(road);
    
    // Test that road was added (we can't directly access private members,
    // but we can test through public interface)
    scheduler->schedule();
    auto sequence = scheduler->getOptimalSequence();
    EXPECT_EQ(sequence.size(), 1);
    EXPECT_EQ(sequence[0], 1);
}

TEST_F(RoadSchedulerTest, PriorityCalculationTest) {
    // Add roads with different priorities
    Road road1{1, 10, 5, 2, 8, 15, 0, 0, 0};  // Lower utility
    Road road2{2, 15, 8, 1, 10, 20, 0, 0, 0}; // Higher utility
    
    scheduler->addRoad(road1);
    scheduler->addRoad(road2);
    
    scheduler->schedule();
    auto sequence = scheduler->getOptimalSequence();
    
    // Road 2 should have higher priority due to higher utility
    EXPECT_EQ(sequence.size(), 2);
    EXPECT_EQ(sequence[0], 2); // Higher priority first
    EXPECT_EQ(sequence[1], 1);
}

TEST_F(RoadSchedulerTest, DeadlineCheckTest) {
    // Add roads with tight deadlines
    Road road1{1, 10, 5, 2, 8, 5, 0, 0, 0};   // Tight deadline
    Road road2{2, 15, 8, 1, 10, 20, 0, 0, 0}; // Loose deadline
    
    scheduler->addRoad(road1);
    scheduler->addRoad(road2);
    
    scheduler->schedule();
    
    // Should detect deadline issues
    bool deadlinesMet = scheduler->checkDeadlines();
    EXPECT_FALSE(deadlinesMet); // Road 1 has tight deadline
}

TEST_F(RoadSchedulerTest, PerformanceMetricsTest) {
    Road road1{1, 10, 5, 2, 8, 15, 0, 0, 0};
    Road road2{2, 15, 8, 1, 10, 20, 0, 0, 0};
    
    scheduler->addRoad(road1);
    scheduler->addRoad(road2);
    
    scheduler->schedule();
    
    double avgTurnaround = scheduler->getAverageTurnaroundTime();
    double avgWaiting = scheduler->getAverageWaitingTime();
    
    EXPECT_GT(avgTurnaround, 0);
    EXPECT_GT(avgWaiting, 0);
    EXPECT_GE(avgTurnaround, avgWaiting);
}

TEST_F(RoadSchedulerTest, EmptySchedulerTest) {
    scheduler->schedule();
    
    auto sequence = scheduler->getOptimalSequence();
    EXPECT_EQ(sequence.size(), 0);
    
    double avgTurnaround = scheduler->getAverageTurnaroundTime();
    double avgWaiting = scheduler->getAverageWaitingTime();
    
    EXPECT_EQ(avgTurnaround, 0);
    EXPECT_EQ(avgWaiting, 0);
}

TEST_F(RoadSchedulerTest, ClearTest) {
    Road road{1, 10, 5, 2, 8, 15, 0, 0, 0};
    scheduler->addRoad(road);
    
    scheduler->clear();
    scheduler->schedule();
    
    auto sequence = scheduler->getOptimalSequence();
    EXPECT_EQ(sequence.size(), 0);
}

TEST_F(RoadSchedulerTest, ComplexSchedulingTest) {
    // Test with multiple roads having different characteristics
    Road road1{1, 10, 5, 2, 8, 15, 0, 0, 0};   // Medium priority
    Road road2{2, 15, 8, 1, 10, 20, 0, 0, 0};  // High priority
    Road road3{3, 8, 3, 3, 6, 12, 0, 0, 0};    // Low priority
    
    scheduler->addRoad(road1);
    scheduler->addRoad(road2);
    scheduler->addRoad(road3);
    
    scheduler->schedule();
    
    auto sequence = scheduler->getOptimalSequence();
    EXPECT_EQ(sequence.size(), 3);
    
    // Check that sequence is optimal (highest priority first)
    EXPECT_EQ(sequence[0], 2); // Highest utility
    EXPECT_EQ(sequence[1], 1); // Medium utility
    EXPECT_EQ(sequence[2], 3); // Lowest utility
} 