#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>

Logger::Logger() : currentLevel(LogLevel::INFO), consoleOutput(true), fileOutput(false) {}

Logger::Logger(const std::string& filePath) : logFilePath(filePath), currentLevel(LogLevel::INFO), consoleOutput(true), fileOutput(false) {
    if (!filePath.empty()) {
        setFileOutput(true);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    currentLevel = level;
}

void Logger::setConsoleOutput(bool enable) {
    std::lock_guard<std::mutex> lock(logMutex);
    consoleOutput = enable;
}

void Logger::setFileOutput(bool enable) {
    std::lock_guard<std::mutex> lock(logMutex);
    fileOutput = enable;
    
    if (enable && !logFilePath.empty()) {
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.open(logFilePath, std::ios::app);
        if (!logFile.is_open()) {
            // Fallback to console output if file cannot be opened
            fileOutput = false;
            consoleOutput = true;
        }
    } else if (!enable && logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setLogFile(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(logMutex);
    logFilePath = filePath;
    
    if (fileOutput && !filePath.empty()) {
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.open(filePath, std::ios::app);
        if (!logFile.is_open()) {
            // Fallback to console output if file cannot be opened
            fileOutput = false;
            consoleOutput = true;
        }
    }
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::critical(const std::string& message) {
    log(LogLevel::CRITICAL, message);
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < currentLevel) {
        return;
    }
    
    writeLog(level, message);
}

void Logger::clearLog() {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile.close();
    }
    if (!logFilePath.empty()) {
        std::ofstream clearFile(logFilePath, std::ios::trunc);
        if (clearFile.is_open()) {
            clearFile.close();
        }
        if (fileOutput) {
            logFile.open(logFilePath, std::ios::app);
        }
    }
}

size_t Logger::getLogFileSize() const {
    if (logFile.is_open()) {
        // Get current position
        auto currentPos = logFile.tellp();
        
        // Seek to end to get size
        logFile.seekp(0, std::ios::end);
        auto size = logFile.tellp();
        
        // Restore position
        logFile.seekp(currentPos);
        
        return static_cast<size_t>(size);
    }
    return 0;
}

std::string Logger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string Logger::getLevelString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

void Logger::writeLog(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string timestamp = getTimestamp();
    std::string levelStr = getLevelString(level);
    std::string logMessage = "[" + timestamp + "] [" + levelStr + "] " + message;
    
    // Log to console
    if (consoleOutput) {
        std::ostream& output = (level >= LogLevel::ERROR) ? std::cerr : std::cout;
        output << logMessage << std::endl;
    }
    
    // Log to file
    if (fileOutput && logFile.is_open()) {
        logFile << logMessage << std::endl;
        logFile.flush();
    }
}

// Singleton instance
static Logger* g_loggerInstance = nullptr;

Logger* Logger::getInstance() {
    if (g_loggerInstance == nullptr) {
        g_loggerInstance = new Logger();
    }
    return g_loggerInstance;
}

void Logger::setLogToConsole(bool enable) {
    setConsoleOutput(enable);
}

void Logger::setLogToFile(bool enable, const std::string& filePath) {
    if (!filePath.empty()) {
        setLogFile(filePath);
    }
    setFileOutput(enable);
}

void Logger::logPerformance(const std::string& operation, double time) {
    info("Performance: " + operation + " completed in " + std::to_string(time) + " ms");
}

void Logger::logAlgorithmStart(const std::string& algorithm, const std::string& params) {
    info("Algorithm Start: " + algorithm + " with params: " + params);
}

void Logger::logAlgorithmEnd(const std::string& algorithm, double time) {
    info("Algorithm End: " + algorithm + " completed in " + std::to_string(time) + " ms");
}

void Logger::logDataLoad(const std::string& filename, size_t size) {
    info("Data Load: " + filename + " (" + std::to_string(size) + " bytes)");
}

void Logger::logDataSave(const std::string& filename, size_t size) {
    info("Data Save: " + filename + " (" + std::to_string(size) + " bytes)");
}

void Logger::logError(const std::string& message, const std::string& context) {
    error("[" + context + "] " + message);
}

void Logger::logWarning(const std::string& message, const std::string& context) {
    warning("[" + context + "] " + message);
}

void Logger::clearLogFile() {
    clearLog();
} 