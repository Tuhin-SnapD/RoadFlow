#include <gtest/gtest.h>
#include <gtest/gtest-death-test.h>
#include "Benchmark.h"
#include "Config.h"
#include "Logger.h"
#include <algorithm> // Add missing include for std::find
#include <thread>
#include <chrono>
#include <fstream>
#include <filesystem>

class BenchmarkTest : public ::testing::Test {
protected:
    void SetUp() override {
        benchmark.clear();
    }
    
    Benchmark benchmark;
};

class ConfigTest : public ::testing::Test {
protected:
    void SetUp() override {
        config.clear();
        test_file = "test_config.txt";
    }
    
    void TearDown() override {
        if (std::filesystem::exists(test_file)) {
            std::filesystem::remove(test_file);
        }
    }
    
    Config config;
    std::string test_file;
};

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        logger = Logger::getInstance();
        logger->setLogLevel(LogLevel::DEBUG);
        logger->setLogToConsole(false);
        test_log_file = "test_log.txt";
    }
    
    void TearDown() override {
        logger->setLogToFile(false);
        if (std::filesystem::exists(test_log_file)) {
            std::filesystem::remove(test_log_file);
        }
    }
    
    Logger* logger;
    std::string test_log_file;
};

// Benchmark Tests
TEST_F(BenchmarkTest, Constructor) {
    EXPECT_EQ(benchmark.getCount(), 0);
    EXPECT_EQ(benchmark.getAverage(), 0.0);
    EXPECT_EQ(benchmark.getMin(), 0.0);
    EXPECT_EQ(benchmark.getMax(), 0.0);
}

TEST_F(BenchmarkTest, SingleMeasurement) {
    benchmark.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    double time = benchmark.end();
    
    EXPECT_EQ(benchmark.getCount(), 1);
    EXPECT_GT(time, 0.0);
    EXPECT_GT(benchmark.getAverage(), 0.0);
    EXPECT_GT(benchmark.getMin(), 0.0);
    EXPECT_GT(benchmark.getMax(), 0.0);
}

TEST_F(BenchmarkTest, MultipleMeasurements) {
    for (int i = 0; i < 5; ++i) {
        benchmark.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        benchmark.end();
    }
    
    EXPECT_EQ(benchmark.getCount(), 5);
    EXPECT_GT(benchmark.getAverage(), 0.0);
    EXPECT_GT(benchmark.getMin(), 0.0);
    EXPECT_GT(benchmark.getMax(), 0.0);
    EXPECT_GT(benchmark.getMedian(), 0.0);
    EXPECT_GE(benchmark.getStandardDeviation(), 0.0);
}

TEST_F(BenchmarkTest, ClearMeasurements) {
    benchmark.start();
    benchmark.end();
    EXPECT_EQ(benchmark.getCount(), 1);
    
    benchmark.clear();
    EXPECT_EQ(benchmark.getCount(), 0);
    EXPECT_EQ(benchmark.getAverage(), 0.0);
}

TEST_F(BenchmarkTest, StatisticsAccuracy) {
    std::vector<double> test_values = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    for (double value : test_values) {
        benchmark.start();
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(value * 1000)));
        benchmark.end();
    }
    
    EXPECT_EQ(benchmark.getCount(), 5);
    EXPECT_NEAR(benchmark.getAverage(), 3.0, 1.0); // Allow some tolerance
    EXPECT_GT(benchmark.getMin(), 0.0);
    EXPECT_GT(benchmark.getMax(), benchmark.getMin());
}

// Config Tests
TEST_F(ConfigTest, Constructor) {
    EXPECT_TRUE(config.empty());
    EXPECT_EQ(config.size(), 0);
}

TEST_F(ConfigTest, SetAndGetString) {
    config.setString("test_key", "test_value");
    EXPECT_EQ(config.getString("test_key"), "test_value");
    EXPECT_EQ(config.getString("nonexistent", "default"), "default");
}

TEST_F(ConfigTest, SetAndGetInt) {
    config.setInt("test_int", 42);
    EXPECT_EQ(config.getInt("test_int"), 42);
    EXPECT_EQ(config.getInt("nonexistent", 100), 100);
}

TEST_F(ConfigTest, SetAndGetDouble) {
    config.setDouble("test_double", 3.14);
    EXPECT_DOUBLE_EQ(config.getDouble("test_double"), 3.14);
    EXPECT_DOUBLE_EQ(config.getDouble("nonexistent", 2.71), 2.71);
}

TEST_F(ConfigTest, SetAndGetBool) {
    config.setBool("test_bool", true);
    EXPECT_TRUE(config.getBool("test_bool"));
    
    config.setBool("test_bool2", false);
    EXPECT_FALSE(config.getBool("test_bool2"));
}

TEST_F(ConfigTest, HasKey) {
    EXPECT_FALSE(config.hasKey("test_key"));
    config.setString("test_key", "value");
    EXPECT_TRUE(config.hasKey("test_key"));
}

TEST_F(ConfigTest, RemoveKey) {
    config.setString("test_key", "value");
    EXPECT_TRUE(config.hasKey("test_key"));
    
    config.removeKey("test_key");
    EXPECT_FALSE(config.hasKey("test_key"));
}

TEST_F(ConfigTest, SaveAndLoadFile) {
    config.setString("key1", "value1");
    config.setInt("key2", 42);
    config.setDouble("key3", 3.14);
    config.setBool("key4", true);
    
    EXPECT_TRUE(config.saveToFile(test_file));
    
    Config loaded_config;
    EXPECT_TRUE(loaded_config.loadFromFile(test_file));
    
    EXPECT_EQ(loaded_config.getString("key1"), "value1");
    EXPECT_EQ(loaded_config.getInt("key2"), 42);
    EXPECT_DOUBLE_EQ(loaded_config.getDouble("key3"), 3.14);
    EXPECT_TRUE(loaded_config.getBool("key4"));
}

TEST_F(ConfigTest, GetKeys) {
    config.setString("key1", "value1");
    config.setString("key2", "value2");
    config.setString("key3", "value3");
    
    auto keys = config.getKeys();
    EXPECT_EQ(keys.size(), 3);
    EXPECT_NE(std::find(keys.begin(), keys.end(), "key1"), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), "key2"), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), "key3"), keys.end());
}

TEST_F(ConfigTest, CreateDefault) {
    Config default_config = Config::createDefault();
    EXPECT_FALSE(default_config.empty());
    EXPECT_EQ(default_config.getString("app_name"), "Road Construction Scheduler");
    EXPECT_EQ(default_config.getString("app_version"), "1.0.0");
    EXPECT_FALSE(default_config.getBool("debug_mode"));
    EXPECT_TRUE(default_config.getBool("verbose_output"));
}

// Logger Tests
TEST_F(LoggerTest, SingletonPattern) {
    Logger* logger1 = Logger::getInstance();
    Logger* logger2 = Logger::getInstance();
    EXPECT_EQ(logger1, logger2);
}

TEST_F(LoggerTest, LogLevels) {
    logger->setLogLevel(LogLevel::INFO);
    
    // These should not be logged
    logger->debug("Debug message");
    logger->setLogToFile(true, test_log_file);
    
    // These should be logged
    logger->info("Info message");
    logger->warning("Warning message");
    logger->error("Error message");
    logger->critical("Critical message");
    
    logger->setLogToFile(false);
    
    std::ifstream log_file(test_log_file);
    std::string content((std::istreambuf_iterator<char>(log_file)),
                        std::istreambuf_iterator<char>());
    
    EXPECT_NE(content.find("Info message"), std::string::npos);
    EXPECT_NE(content.find("Warning message"), std::string::npos);
    EXPECT_NE(content.find("Error message"), std::string::npos);
    EXPECT_NE(content.find("Critical message"), std::string::npos);
}

TEST_F(LoggerTest, FileLogging) {
    logger->setLogToFile(true, test_log_file);
    logger->info("Test message");
    logger->setLogToFile(false);
    
    EXPECT_TRUE(std::filesystem::exists(test_log_file));
    
    std::ifstream log_file(test_log_file);
    std::string content((std::istreambuf_iterator<char>(log_file)),
                        std::istreambuf_iterator<char>());
    
    EXPECT_NE(content.find("Test message"), std::string::npos);
    EXPECT_NE(content.find("[INFO]"), std::string::npos);
}

TEST_F(LoggerTest, PerformanceLogging) {
    logger->setLogToFile(true, test_log_file);
    logger->logPerformance("Test Operation", 123.456);
    logger->setLogToFile(false);
    
    std::ifstream log_file(test_log_file);
    std::string content((std::istreambuf_iterator<char>(log_file)),
                        std::istreambuf_iterator<char>());
    
    EXPECT_NE(content.find("Performance: Test Operation completed in 123.456 ms"), std::string::npos);
}

TEST_F(LoggerTest, AlgorithmLogging) {
    logger->setLogToFile(true, test_log_file);
    logger->logAlgorithmStart("Dijkstra", "graph_size=100");
    logger->logAlgorithmEnd("Dijkstra", 45.67);
    logger->setLogToFile(false);
    
    std::ifstream log_file(test_log_file);
    std::string content((std::istreambuf_iterator<char>(log_file)),
                        std::istreambuf_iterator<char>());
    
    EXPECT_NE(content.find("Starting algorithm: Dijkstra with parameters: graph_size=100"), std::string::npos);
    EXPECT_NE(content.find("Algorithm completed: Dijkstra in 45.670 ms"), std::string::npos);
}

TEST_F(LoggerTest, DataLogging) {
    logger->setLogToFile(true, test_log_file);
    logger->logDataLoad("roads.txt", 150);
    logger->logDataSave("output.txt", 150);
    logger->setLogToFile(false);
    
    std::ifstream log_file(test_log_file);
    std::string content((std::istreambuf_iterator<char>(log_file)),
                        std::istreambuf_iterator<char>());
    
    EXPECT_NE(content.find("Data loaded from roads.txt: 150 records"), std::string::npos);
    EXPECT_NE(content.find("Data saved to output.txt: 150 records"), std::string::npos);
}

TEST_F(LoggerTest, ErrorAndWarningLogging) {
    logger->setLogToFile(true, test_log_file);
    logger->logError("File not found", "loadData");
    logger->logWarning("Invalid input", "validateInput");
    logger->setLogToFile(false);
    
    std::ifstream log_file(test_log_file);
    std::string content((std::istreambuf_iterator<char>(log_file)),
                        std::istreambuf_iterator<char>());
    
    EXPECT_NE(content.find("Error in loadData: File not found"), std::string::npos);
    EXPECT_NE(content.find("Warning in validateInput: Invalid input"), std::string::npos);
}

TEST_F(LoggerTest, ClearLogFile) {
    logger->setLogToFile(true, test_log_file);
    logger->info("First message");
    logger->clearLogFile();
    logger->info("Second message");
    logger->setLogToFile(false);
    
    std::ifstream log_file(test_log_file);
    std::string content((std::istreambuf_iterator<char>(log_file)),
                        std::istreambuf_iterator<char>());
    
    EXPECT_EQ(content.find("First message"), std::string::npos);
    EXPECT_NE(content.find("Second message"), std::string::npos);
}

// Integration Tests
TEST_F(ConfigTest, IntegrationWithLogger) {
    Config config;
    config.setString("log_file", "integration_test.log");
    config.setBool("debug_mode", true);
    config.setInt("max_iterations", 1000);
    
    Logger* logger = Logger::getInstance();
    logger->setLogToFile(true, config.getString("log_file"));
    logger->setLogLevel(config.getBool("debug_mode") ? LogLevel::DEBUG : LogLevel::INFO);
    
    logger->info("Integration test started");
    logger->debug("Max iterations: " + std::to_string(config.getInt("max_iterations")));
    logger->info("Integration test completed");
    
    logger->setLogToFile(false);
    
    EXPECT_TRUE(std::filesystem::exists("integration_test.log"));
    std::filesystem::remove("integration_test.log");
}

TEST_F(BenchmarkTest, IntegrationWithLogger) {
    Benchmark benchmark;
    Logger* logger = Logger::getInstance();
    
    logger->setLogToFile(true, "benchmark_integration.log");
    
    for (int i = 0; i < 3; ++i) {
        benchmark.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        double time = benchmark.end();
        logger->logPerformance("Test Operation " + std::to_string(i), time);
    }
    
    logger->info("Benchmark completed. Average: " + std::to_string(benchmark.getAverage()) + " ms");
    logger->setLogToFile(false);
    
    EXPECT_TRUE(std::filesystem::exists("benchmark_integration.log"));
    std::filesystem::remove("benchmark_integration.log");
} 