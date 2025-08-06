#pragma once

#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <iomanip>

/**
 * @brief Performance benchmarking utility for algorithm analysis
 * 
 * This class provides tools to measure and compare the performance
 * of different algorithms and implementations.
 */
class Benchmark {
private:
    struct BenchmarkResult {
        std::string name;
        double averageTime;    // in milliseconds
        double minTime;        // in milliseconds
        double maxTime;        // in milliseconds
        int iterations;
        size_t inputSize;
    };

    std::vector<BenchmarkResult> results;

    /**
     * @brief Measures execution time of a function
     * @param func Function to benchmark
     * @param iterations Number of iterations to run
     * @return Average execution time in milliseconds
     */
    template<typename Func>
    double measureTime(Func func, int iterations = 100) {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < iterations; ++i) {
            func();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        return duration.count() / 1000.0 / iterations; // Convert to milliseconds
    }

public:
    /**
     * @brief Runs a benchmark test
     * @param name Name of the benchmark
     * @param func Function to benchmark
     * @param inputSize Size of input data
     * @param iterations Number of iterations
     */
    template<typename Func>
    void runBenchmark(const std::string& name, Func func, size_t inputSize, int iterations = 100) {
        std::vector<double> times;
        
        for (int i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            func();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            times.push_back(duration.count() / 1000.0); // Convert to milliseconds
        }
        
        // Calculate statistics
        double sum = 0, minTime = times[0], maxTime = times[0];
        for (double time : times) {
            sum += time;
            minTime = std::min(minTime, time);
            maxTime = std::max(maxTime, time);
        }
        
        BenchmarkResult result{
            name,
            sum / iterations,
            minTime,
            maxTime,
            iterations,
            inputSize
        };
        
        results.push_back(result);
    }

    /**
     * @brief Displays benchmark results in a formatted table
     */
    void displayResults() const {
        std::cout << "\n" << std::string(80, '=') << "\n";
        std::cout << "                           BENCHMARK RESULTS\n";
        std::cout << std::string(80, '=') << "\n";
        std::cout << std::left << std::setw(25) << "Algorithm" 
                  << std::setw(10) << "Input Size"
                  << std::setw(12) << "Avg (ms)"
                  << std::setw(12) << "Min (ms)"
                  << std::setw(12) << "Max (ms)"
                  << std::setw(10) << "Iterations" << "\n";
        std::cout << std::string(80, '-') << "\n";
        
        for (const auto& result : results) {
            std::cout << std::left << std::setw(25) << result.name
                      << std::setw(10) << result.inputSize
                      << std::setw(12) << std::fixed << std::setprecision(3) << result.averageTime
                      << std::setw(12) << std::fixed << std::setprecision(3) << result.minTime
                      << std::setw(12) << std::fixed << std::setprecision(3) << result.maxTime
                      << std::setw(10) << result.iterations << "\n";
        }
        std::cout << std::string(80, '=') << "\n";
    }

    /**
     * @brief Compares two algorithms and shows performance difference
     * @param algo1Name Name of first algorithm
     * @param algo1Func First algorithm function
     * @param algo2Name Name of second algorithm
     * @param algo2Func Second algorithm function
     * @param inputSize Size of input data
     * @param iterations Number of iterations
     */
    template<typename Func1, typename Func2>
    void compareAlgorithms(const std::string& algo1Name, Func1 algo1Func,
                          const std::string& algo2Name, Func2 algo2Func,
                          size_t inputSize, int iterations = 100) {
        runBenchmark(algo1Name, algo1Func, inputSize, iterations);
        runBenchmark(algo2Name, algo2Func, inputSize, iterations);
        
        if (results.size() >= 2) {
            const auto& result1 = results[results.size() - 2];
            const auto& result2 = results[results.size() - 1];
            
            double speedup = result1.averageTime / result2.averageTime;
            
            std::cout << "\n" << std::string(60, '=') << "\n";
            std::cout << "                    PERFORMANCE COMPARISON\n";
            std::cout << std::string(60, '=') << "\n";
            std::cout << algo1Name << " vs " << algo2Name << "\n";
            std::cout << "Input Size: " << inputSize << "\n";
            std::cout << "Iterations: " << iterations << "\n\n";
            std::cout << algo1Name << " average time: " << std::fixed << std::setprecision(3) 
                      << result1.averageTime << " ms\n";
            std::cout << algo2Name << " average time: " << std::fixed << std::setprecision(3) 
                      << result2.averageTime << " ms\n";
            std::cout << "Speedup: " << std::fixed << std::setprecision(2) << speedup << "x\n";
            
            if (speedup > 1.0) {
                std::cout << algo2Name << " is " << speedup << "x faster than " << algo1Name << "\n";
            } else {
                std::cout << algo1Name << " is " << (1.0/speedup) << "x faster than " << algo2Name << "\n";
            }
            std::cout << std::string(60, '=') << "\n";
        }
    }

    /**
     * @brief Clears all benchmark results
     */
    void clear() {
        results.clear();
    }

    /**
     * @brief Exports results to CSV format
     * @param filename Output filename
     */
    void exportToCSV(const std::string& filename) const;

    // Additional methods for test compatibility
    /**
     * @brief Starts timing
     */
    void start();

    /**
     * @brief Ends timing and returns elapsed time
     * @return Elapsed time in milliseconds
     */
    double end();

    /**
     * @brief Gets the number of measurements
     * @return Number of measurements
     */
    int getCount() const;

    /**
     * @brief Gets the average time
     * @return Average time in milliseconds
     */
    double getAverage() const;

    /**
     * @brief Gets the minimum time
     * @return Minimum time in milliseconds
     */
    double getMin() const;

    /**
     * @brief Gets the maximum time
     * @return Maximum time in milliseconds
     */
    double getMax() const;

    /**
     * @brief Gets the median time
     * @return Median time in milliseconds
     */
    double getMedian() const;

    /**
     * @brief Gets the standard deviation
     * @return Standard deviation in milliseconds
     */
    double getStandardDeviation() const;
}; 