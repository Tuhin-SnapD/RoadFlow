#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include "Benchmark.h"
#include "Config.h"
#include "Logger.h"
#include "Graph.h"
#include "RoadScheduler.h"
#include "BankersAlgorithm.h"

void demonstrateBenchmarking() {
    std::cout << "\n=== BENCHMARKING DEMONSTRATION ===" << std::endl;
    
    Logger logger("benchmark_demo.log");
    logger.setLogLevel(LogLevel::INFO);
    
    Benchmark benchmark;
    
    // Create a test graph
    Graph graph(100);
    for (int i = 0; i < 100; ++i) {
        for (int j = i + 1; j < 100; ++j) {
            if (rand() % 10 < 3) { // 30% chance of edge
                graph.addEdge(i, j, rand() % 100 + 1);
            }
        }
    }
    
    // Benchmark graph operations
    benchmark.runBenchmark("Graph Construction", [&graph]() {
        Graph testGraph(50);
        for (int i = 0; i < 50; ++i) {
            for (int j = i + 1; j < 50; ++j) {
                if (rand() % 10 < 3) {
                    testGraph.addEdge(i, j, rand() % 100 + 1);
                }
            }
        }
    }, 50, 100);
    
    // Benchmark road scheduling
    RoadScheduler scheduler;
    for (int i = 0; i < 20; ++i) {
        Road road;
        road.id = i;
        road.priority = rand() % 10 + 1;
        road.deadline = rand() % 30 + 1;
        road.distance = rand() % 100 + 1;
        road.utility = rand() % 30 + 1;
        road.traffic = rand() % 20 + 1;
        road.estimatedTime = rand() % 15 + 1;
        scheduler.addRoad(road);
    }
    
    benchmark.runBenchmark("Road Scheduling", [&scheduler]() {
        RoadScheduler testScheduler;
        for (int i = 0; i < 10; ++i) {
            Road road;
            road.id = i;
            road.priority = rand() % 10 + 1;
            road.deadline = rand() % 30 + 1;
            road.distance = rand() % 100 + 1;
            road.utility = rand() % 30 + 1;
            road.traffic = rand() % 20 + 1;
            road.estimatedTime = rand() % 15 + 1;
            testScheduler.addRoad(road);
        }
        testScheduler.schedule();
    }, 10, 100);
    
    // Display results
    benchmark.displayResults();
    
    // Compare algorithms
    benchmark.compareAlgorithms("Graph Construction", [&graph]() {
        Graph testGraph(50);
        for (int i = 0; i < 50; ++i) {
            for (int j = i + 1; j < 50; ++j) {
                if (rand() % 10 < 3) {
                    testGraph.addEdge(i, j, rand() % 100 + 1);
                }
            }
        }
    }, "Road Scheduling", [&scheduler]() {
        RoadScheduler testScheduler;
        for (int i = 0; i < 10; ++i) {
            Road road;
            road.id = i;
            road.priority = rand() % 10 + 1;
            road.deadline = rand() % 30 + 1;
            road.distance = rand() % 100 + 1;
            road.utility = rand() % 30 + 1;
            road.traffic = rand() % 20 + 1;
            road.estimatedTime = rand() % 15 + 1;
            testScheduler.addRoad(road);
        }
        testScheduler.schedule();
    }, 50, 100);
}

void demonstrateConfiguration() {
    std::cout << "\n=== CONFIGURATION DEMONSTRATION ===" << std::endl;
    
    Config config;
    config.createDefaultConfig();
    
    std::cout << "Default configuration created." << std::endl;
    
    // Display some default settings
    std::cout << "Algorithm max iterations: " << config.getInt("algorithm.max_iterations") << std::endl;
    std::cout << "Logging level: " << config.get("logging.level") << std::endl;
    std::cout << "Performance benchmark iterations: " << config.getInt("performance.benchmark_iterations") << std::endl;
    
    // Modify some settings
    config.set("algorithm.max_iterations", "2000");
    config.set("logging.level", "DEBUG");
    config.set("performance.enable_profiling", "false");
    
    std::cout << "\nAfter modification:" << std::endl;
    std::cout << "Algorithm max iterations: " << config.getInt("algorithm.max_iterations") << std::endl;
    std::cout << "Logging level: " << config.get("logging.level") << std::endl;
    std::cout << "Performance profiling enabled: " << (config.getBool("performance.enable_profiling") ? "true" : "false") << std::endl;
    
    // Save configuration to file
    if (config.saveToFile("demo_config.txt")) {
        std::cout << "Configuration saved to demo_config.txt" << std::endl;
    }
    
    // Load configuration from file
    Config loaded_config;
    if (loaded_config.loadFromFile("demo_config.txt")) {
        std::cout << "Configuration loaded from file." << std::endl;
        std::cout << "Algorithm max iterations: " << loaded_config.getInt("algorithm.max_iterations") << std::endl;
    }
    
    // Display all configuration keys
    std::cout << "\nAll configuration keys:" << std::endl;
    for (const auto& key : config.getKeys()) {
        std::cout << "  - " << key << " = " << config.get(key) << std::endl;
    }
}

void demonstrateLogging() {
    std::cout << "\n=== LOGGING DEMONSTRATION ===" << std::endl;
    
    Logger logger("demo_application.log");
    logger.setLogLevel(LogLevel::DEBUG);
    logger.setConsoleOutput(true);
    logger.setFileOutput(true);
    
    std::cout << "Logger initialized with file output enabled." << std::endl;
    
    // Demonstrate different log levels
    logger.debug("This is a debug message");
    logger.info("This is an info message");
    logger.warning("This is a warning message");
    logger.error("This is an error message");
    logger.critical("This is a critical message");
    
    // Demonstrate custom log level
    logger.log(LogLevel::INFO, "Custom log level message");
    
    // Simulate some application events
    logger.info("Application started");
    logger.info("Loading configuration...");
    logger.info("Configuration loaded successfully");
    
    // Simulate performance logging
    logger.info("Performance: Graph Construction completed in 12.34 ms");
    logger.info("Performance: Path Finding completed in 23.45 ms");
    
    // Simulate error handling
    logger.error("File not found: config.txt");
    logger.warning("Invalid input format in line 15");
    
    // Show log file size
    size_t logSize = logger.getLogFileSize();
    std::cout << "Log file size: " << logSize << " bytes" << std::endl;
    
    logger.info("Application shutdown complete");
}

void demonstrateIntegration() {
    std::cout << "\n=== INTEGRATION DEMONSTRATION ===" << std::endl;
    
    Logger logger("integration_demo.log");
    Config config;
    Benchmark benchmark;
    
    // Initialize configuration
    config.createDefaultConfig();
    config.set("logging.level", "INFO");
    config.set("performance.benchmark_iterations", "50");
    
    // Setup logging based on configuration
    logger.setLogLevel(LogLevel::INFO);
    logger.setFileOutput(true);
    
    logger.info("Integration demo started");
    logger.info("Configuration loaded");
    
    // Demonstrate integrated benchmarking
    logger.info("Starting performance benchmarks");
    
    // Create test data
    Graph graph(20);
    for (int i = 0; i < 20; ++i) {
        for (int j = i + 1; j < 20; ++j) {
            if (rand() % 10 < 4) {
                graph.addEdge(i, j, rand() % 100 + 1);
            }
        }
    }
    
    logger.info("Test graph created with 20 vertices");
    
    // Benchmark graph operations
    for (int i = 0; i < 5; ++i) {
        benchmark.runBenchmark("Graph Operations", [&graph]() {
            // Simulate some graph operations
            for (int j = 0; j < 10; ++j) {
                graph.addEdge(rand() % 20, rand() % 20, rand() % 100 + 1);
            }
        }, 20, 50);
        
        logger.info("Benchmark iteration " + std::to_string(i + 1) + " completed");
    }
    
    // Check performance against threshold
    double threshold = config.getDouble("performance.threshold_ms", 100.0);
    logger.info("Performance threshold: " + std::to_string(threshold) + " ms");
    
    // Create road scheduling test
    RoadScheduler scheduler;
    for (int i = 0; i < 10; ++i) {
        Road road;
        road.id = i;
        road.priority = rand() % 10 + 1;
        road.deadline = rand() % 30 + 1;
        road.distance = rand() % 100 + 1;
        road.utility = rand() % 30 + 1;
        road.traffic = rand() % 20 + 1;
        road.estimatedTime = rand() % 15 + 1;
        scheduler.addRoad(road);
    }
    
    logger.info("Road scheduler created with 10 roads");
    
    // Benchmark scheduling
    for (int i = 0; i < 5; ++i) {
        benchmark.runBenchmark("Road Scheduling", [&scheduler]() {
            RoadScheduler testScheduler;
            for (int j = 0; j < 5; ++j) {
                Road road;
                road.id = j;
                road.priority = rand() % 10 + 1;
                road.deadline = rand() % 30 + 1;
                road.distance = rand() % 100 + 1;
                road.utility = rand() % 30 + 1;
                road.traffic = rand() % 20 + 1;
                road.estimatedTime = rand() % 15 + 1;
                testScheduler.addRoad(road);
            }
            testScheduler.schedule();
        }, 5, 50);
        
        logger.info("Scheduling benchmark iteration " + std::to_string(i + 1) + " completed");
    }
    
    // Test Banker's Algorithm
    logger.info("Testing Banker's Algorithm");
    
    std::vector<std::vector<int>> allocation = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    std::vector<std::vector<int>> max_need = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    std::vector<int> available = {3, 3, 2};
    
    BankersAlgorithm bankers(5, 3);
    
    for (int i = 0; i < 5; ++i) {
        benchmark.runBenchmark("Safety Check", [&bankers, &allocation, &max_need, &available]() {
            BankersAlgorithm testBankers(5, 3);
            testBankers.setAllocation(allocation);
            testBankers.setMaximum(max_need);
            testBankers.setAvailable(available);
            testBankers.isSafe();
        }, 5, 50);
        
        logger.info("Safety check benchmark iteration " + std::to_string(i + 1) + " completed");
    }
    
    // Display final results
    benchmark.displayResults();
    
    logger.info("Integration demo completed successfully");
}

void demonstrateErrorHandling() {
    std::cout << "\n=== ERROR HANDLING DEMONSTRATION ===" << std::endl;
    
    Logger logger("error_handling_demo.log");
    logger.setLogLevel(LogLevel::WARNING);
    
    // Test Graph error handling
    Graph graph(5);
    
    try {
        graph.addEdge(10, 15, 100); // Invalid vertices
        logger.error("Failed to catch invalid vertex");
    } catch (const std::exception& e) {
        logger.warning("Caught expected exception: " + std::string(e.what()));
    }
    
    // Test Config error handling
    Config config;
    
    // Test invalid integer conversion
    config.set("invalid_int", "not_a_number");
    int value = config.getInt("invalid_int", -1);
    logger.info("Invalid int conversion result: " + std::to_string(value));
    
    // Test file loading error
    Config invalid_config;
    if (!invalid_config.loadFromFile("nonexistent_file.txt")) {
        logger.warning("Expected file load failure");
    }
    
    // Test Benchmark with no data
    Benchmark benchmark;
    logger.info("Benchmark created with no measurements");
    
    std::cout << "Error handling demonstration completed." << std::endl;
}

int main() {
    std::cout << "Road Construction Scheduling System - Professional Features Demo" << std::endl;
    std::cout << "=================================================================" << std::endl;
    
    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    
    try {
        demonstrateConfiguration();
        demonstrateLogging();
        demonstrateBenchmarking();
        demonstrateIntegration();
        demonstrateErrorHandling();
        
        std::cout << "\n=== DEMO COMPLETED SUCCESSFULLY ===" << std::endl;
        std::cout << "Check the generated log files for detailed information." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Demo failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 