#include "Benchmark.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>

// Private member variables for timing
static std::chrono::high_resolution_clock::time_point startTime;
static std::vector<double> measurements;

void Benchmark::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

double Benchmark::end() {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    double timeMs = duration.count() / 1000.0;
    measurements.push_back(timeMs);
    return timeMs;
}

int Benchmark::getCount() const {
    return static_cast<int>(measurements.size());
}

double Benchmark::getAverage() const {
    if (measurements.empty()) return 0.0;
    double sum = std::accumulate(measurements.begin(), measurements.end(), 0.0);
    return sum / measurements.size();
}

double Benchmark::getMin() const {
    if (measurements.empty()) return 0.0;
    return *std::min_element(measurements.begin(), measurements.end());
}

double Benchmark::getMax() const {
    if (measurements.empty()) return 0.0;
    return *std::max_element(measurements.begin(), measurements.end());
}

double Benchmark::getMedian() const {
    if (measurements.empty()) return 0.0;
    
    std::vector<double> sorted = measurements;
    std::sort(sorted.begin(), sorted.end());
    
    size_t size = sorted.size();
    if (size % 2 == 0) {
        return (sorted[size/2 - 1] + sorted[size/2]) / 2.0;
    } else {
        return sorted[size/2];
    }
}

double Benchmark::getStandardDeviation() const {
    if (measurements.size() < 2) return 0.0;
    
    double mean = getAverage();
    double sumSquaredDiff = 0.0;
    
    for (double measurement : measurements) {
        double diff = measurement - mean;
        sumSquaredDiff += diff * diff;
    }
    
    return std::sqrt(sumSquaredDiff / (measurements.size() - 1));
}

void Benchmark::exportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    
    file << "Algorithm,Input Size,Avg (ms),Min (ms),Max (ms),Iterations\n";
    
    for (const auto& result : results) {
        file << result.name << ","
             << result.inputSize << ","
             << result.averageTime << ","
             << result.minTime << ","
             << result.maxTime << ","
             << result.iterations << "\n";
    }
} 