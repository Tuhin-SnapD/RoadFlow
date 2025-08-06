#include <gtest/gtest.h>
#include "BankersAlgorithm.h"

class BankersAlgorithmTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a test instance with 3 roads and 3 resource types
        banker = new BankersAlgorithm(3, 3);
    }

    void TearDown() override {
        delete banker;
    }

    BankersAlgorithm* banker;
};

TEST_F(BankersAlgorithmTest, ConstructorTest) {
    BankersAlgorithm b(2, 2);
    // Test that constructor works without throwing
    EXPECT_TRUE(true);
}

TEST_F(BankersAlgorithmTest, SafeStateTest) {
    // Test case from the test plan - should be safe
    std::vector<std::vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2}
    };
    
    std::vector<std::vector<int>> maximum = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2}
    };
    
    std::vector<int> available = {7, 4, 3};
    
    banker->setAllocation(allocation);
    banker->setMaximum(maximum);
    banker->setAvailable(available);
    
    EXPECT_TRUE(banker->isSafe());
    
    auto safeSequence = banker->findSafeSequence();
    EXPECT_FALSE(safeSequence.empty());
    EXPECT_EQ(safeSequence.size(), 3);
}

TEST_F(BankersAlgorithmTest, UnsafeStateTest) {
    // Create an unsafe state
    std::vector<std::vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2}
    };
    
    std::vector<std::vector<int>> maximum = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2}
    };
    
    std::vector<int> available = {0, 0, 0}; // No available resources
    
    banker->setAllocation(allocation);
    banker->setMaximum(maximum);
    banker->setAvailable(available);
    
    EXPECT_FALSE(banker->isSafe());
    
    auto safeSequence = banker->findSafeSequence();
    EXPECT_TRUE(safeSequence.empty());
}

TEST_F(BankersAlgorithmTest, NeedMatrixCalculationTest) {
    std::vector<std::vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2}
    };
    
    std::vector<std::vector<int>> maximum = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2}
    };
    
    banker->setAllocation(allocation);
    banker->setMaximum(maximum);
    
    // The need matrix should be calculated correctly
    // Need[i][j] = Maximum[i][j] - Allocation[i][j]
    // Road 0: {7-0, 5-1, 3-0} = {7, 4, 3}
    // Road 1: {3-2, 2-0, 2-0} = {1, 2, 2}
    // Road 2: {9-3, 0-0, 2-2} = {6, 0, 0}
    
    // We can't directly test the need matrix as it's private,
    // but we can verify through the safe sequence
    std::vector<int> available = {7, 4, 3};
    banker->setAvailable(available);
    
    auto safeSequence = banker->findSafeSequence();
    EXPECT_FALSE(safeSequence.empty());
}

TEST_F(BankersAlgorithmTest, SingleRoadTest) {
    BankersAlgorithm singleBanker(1, 2);
    
    std::vector<std::vector<int>> allocation = {{1, 0}};
    std::vector<std::vector<int>> maximum = {{3, 2}};
    std::vector<int> available = {2, 2};
    
    singleBanker.setAllocation(allocation);
    singleBanker.setMaximum(maximum);
    singleBanker.setAvailable(available);
    
    EXPECT_TRUE(singleBanker.isSafe());
    
    auto safeSequence = singleBanker.findSafeSequence();
    EXPECT_EQ(safeSequence.size(), 1);
    EXPECT_EQ(safeSequence[0], 0);
}

TEST_F(BankersAlgorithmTest, NoResourcesTest) {
    BankersAlgorithm noResourceBanker(2, 0);
    
    std::vector<std::vector<int>> allocation = {};
    std::vector<std::vector<int>> maximum = {};
    std::vector<int> available = {};
    
    noResourceBanker.setAllocation(allocation);
    noResourceBanker.setMaximum(maximum);
    noResourceBanker.setAvailable(available);
    
    EXPECT_TRUE(noResourceBanker.isSafe());
    
    auto safeSequence = noResourceBanker.findSafeSequence();
    EXPECT_EQ(safeSequence.size(), 2);
}

TEST_F(BankersAlgorithmTest, ComplexSafeStateTest) {
    // Test with more complex scenario
    BankersAlgorithm complexBanker(4, 3);
    
    std::vector<std::vector<int>> allocation = {
        {1, 0, 2},
        {0, 1, 0},
        {3, 0, 1},
        {2, 1, 1}
    };
    
    std::vector<std::vector<int>> maximum = {
        {3, 2, 2},
        {1, 1, 2},
        {6, 1, 3},
        {2, 1, 2}
    };
    
    std::vector<int> available = {1, 1, 2};
    
    complexBanker.setAllocation(allocation);
    complexBanker.setMaximum(maximum);
    complexBanker.setAvailable(available);
    
    EXPECT_TRUE(complexBanker.isSafe());
    
    auto safeSequence = complexBanker.findSafeSequence();
    EXPECT_EQ(safeSequence.size(), 4);
    
    // Verify all roads are included in the sequence
    std::vector<bool> found(4, false);
    for (int road : safeSequence) {
        found[road] = true;
    }
    for (bool f : found) {
        EXPECT_TRUE(f);
    }
}

TEST_F(BankersAlgorithmTest, EdgeCaseTest) {
    // Test edge case where all resources are allocated
    std::vector<std::vector<int>> allocation = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    
    std::vector<std::vector<int>> maximum = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    
    std::vector<int> available = {0, 0, 0};
    
    banker->setAllocation(allocation);
    banker->setMaximum(maximum);
    banker->setAvailable(available);
    
    EXPECT_TRUE(banker->isSafe()); // All needs are 0, so it's safe
    
    auto safeSequence = banker->findSafeSequence();
    EXPECT_EQ(safeSequence.size(), 3);
} 