#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <mutex>

/**
 * @brief Log levels for the logging system
 */
enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

/**
 * @brief Professional logging system for the Road Construction project
 * 
 * This class provides comprehensive logging capabilities with different
 * log levels, file output, and thread safety.
 */
class Logger {
private:
    mutable std::ofstream logFile;
    std::string logFilePath;
    LogLevel currentLevel;
    bool consoleOutput;
    bool fileOutput;
    std::mutex logMutex;

    /**
     * @brief Gets current timestamp as string
     * @return Formatted timestamp string
     */
    std::string getTimestamp() const;

    /**
     * @brief Gets log level string
     * @param level Log level
     * @return String representation of log level
     */
    std::string getLevelString(LogLevel level) const;

    /**
     * @brief Writes log message to output streams
     * @param level Log level
     * @param message Log message
     */
    void writeLog(LogLevel level, const std::string& message);

public:
    /**
     * @brief Default constructor
     */
    Logger();

    /**
     * @brief Constructor with log file path
     * @param filePath Path to log file
     */
    explicit Logger(const std::string& filePath);

    /**
     * @brief Destructor
     */
    ~Logger();

    /**
     * @brief Sets the log level
     * @param level New log level
     */
    void setLogLevel(LogLevel level);

    /**
     * @brief Enables or disables console output
     * @param enable true to enable, false to disable
     */
    void setConsoleOutput(bool enable);

    /**
     * @brief Enables or disables file output
     * @param enable true to enable, false to disable
     */
    void setFileOutput(bool enable);

    /**
     * @brief Sets the log file path
     * @param filePath New log file path
     */
    void setLogFile(const std::string& filePath);

    /**
     * @brief Logs a debug message
     * @param message Debug message
     */
    void debug(const std::string& message);

    /**
     * @brief Logs an info message
     * @param message Info message
     */
    void info(const std::string& message);

    /**
     * @brief Logs a warning message
     * @param message Warning message
     */
    void warning(const std::string& message);

    /**
     * @brief Logs an error message
     * @param message Error message
     */
    void error(const std::string& message);

    /**
     * @brief Logs a critical message
     * @param message Critical message
     */
    void critical(const std::string& message);

    /**
     * @brief Logs a message with custom level
     * @param level Log level
     * @param message Log message
     */
    void log(LogLevel level, const std::string& message);

    /**
     * @brief Gets the current log level
     * @return Current log level
     */
    LogLevel getLogLevel() const { return currentLevel; }

    /**
     * @brief Gets the log file path
     * @return Log file path
     */
    std::string getLogFilePath() const { return logFilePath; }

    /**
     * @brief Checks if console output is enabled
     * @return true if enabled, false otherwise
     */
    bool isConsoleOutputEnabled() const { return consoleOutput; }

    /**
     * @brief Checks if file output is enabled
     * @return true if enabled, false otherwise
     */
    bool isFileOutputEnabled() const { return fileOutput; }

    /**
     * @brief Clears the log file
     */
    void clearLog();

    /**
     * @brief Gets log file size in bytes
     * @return Log file size
     */
    size_t getLogFileSize() const;

    // Additional methods for test compatibility
    /**
     * @brief Gets singleton instance
     * @return Pointer to singleton instance
     */
    static Logger* getInstance();

    /**
     * @brief Sets console output
     * @param enable true to enable, false to disable
     */
    void setLogToConsole(bool enable);

    /**
     * @brief Sets file output
     * @param enable true to enable, false to disable
     * @param filePath Optional file path
     */
    void setLogToFile(bool enable, const std::string& filePath = "");

    /**
     * @brief Logs performance data
     * @param operation Operation name
     * @param time Time in milliseconds
     */
    void logPerformance(const std::string& operation, double time);

    /**
     * @brief Logs algorithm start
     * @param algorithm Algorithm name
     * @param params Parameters
     */
    void logAlgorithmStart(const std::string& algorithm, const std::string& params);

    /**
     * @brief Logs algorithm end
     * @param algorithm Algorithm name
     * @param time Time in milliseconds
     */
    void logAlgorithmEnd(const std::string& algorithm, double time);

    /**
     * @brief Logs data load event
     * @param filename File name
     * @param size Data size
     */
    void logDataLoad(const std::string& filename, size_t size);

    /**
     * @brief Logs data save event
     * @param filename File name
     * @param size Data size
     */
    void logDataSave(const std::string& filename, size_t size);

    /**
     * @brief Logs error
     * @param message Error message
     * @param context Error context
     */
    void logError(const std::string& message, const std::string& context);

    /**
     * @brief Logs warning
     * @param message Warning message
     * @param context Warning context
     */
    void logWarning(const std::string& message, const std::string& context);

    /**
     * @brief Clears log file
     */
    void clearLogFile();
};

 