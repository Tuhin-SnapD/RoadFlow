#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector> // Added missing include for std::vector

/**
 * @brief Configuration management system for the Road Construction project
 * 
 * This class provides a centralized way to manage application settings,
 * algorithm parameters, and system configurations.
 */
class Config {
private:
    std::map<std::string, std::string> settings;
    std::string configFile;

    /**
     * @brief Parses a configuration line
     * @param line Line to parse
     * @return Pair of key and value
     */
    std::pair<std::string, std::string> parseLine(const std::string& line) const;

    /**
     * @brief Trims whitespace from string
     * @param str String to trim
     * @return Trimmed string
     */
    std::string trim(const std::string& str) const;

    /**
     * @brief Converts string to lowercase
     * @param str String to convert
     * @return Lowercase string
     */
    std::string toLower(const std::string& str) const;

public:
    /**
     * @brief Default constructor
     */
    Config();

    /**
     * @brief Constructor with config file path
     * @param filename Configuration file path
     */
    explicit Config(const std::string& filename);

    /**
     * @brief Loads configuration from file
     * @param filename Configuration file path
     * @return true if successful, false otherwise
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Saves configuration to file
     * @param filename Output file path (optional, uses default if empty)
     * @return true if successful, false otherwise
     */
    bool saveToFile(const std::string& filename = "");

    /**
     * @brief Sets a configuration value
     * @param key Configuration key
     * @param value Configuration value
     */
    void set(const std::string& key, const std::string& value);

    /**
     * @brief Gets a configuration value
     * @param key Configuration key
     * @param defaultValue Default value if key not found
     * @return Configuration value
     */
    std::string get(const std::string& key, const std::string& defaultValue = "") const;

    /**
     * @brief Gets a configuration value as integer
     * @param key Configuration key
     * @param defaultValue Default value if key not found
     * @return Configuration value as integer
     */
    int getInt(const std::string& key, int defaultValue = 0) const;

    /**
     * @brief Gets a configuration value as double
     * @param key Configuration key
     * @param defaultValue Default value if key not found
     * @return Configuration value as double
     */
    double getDouble(const std::string& key, double defaultValue = 0.0) const;

    /**
     * @brief Gets a configuration value as boolean
     * @param key Configuration key
     * @param defaultValue Default value if key not found
     * @return Configuration value as boolean
     */
    bool getBool(const std::string& key, bool defaultValue = false) const;

    /**
     * @brief Checks if a configuration key exists
     * @param key Configuration key
     * @return true if key exists, false otherwise
     */
    bool hasKey(const std::string& key) const;

    /**
     * @brief Removes a configuration key
     * @param key Configuration key to remove
     */
    void remove(const std::string& key);

    /**
     * @brief Clears all configuration settings
     */
    void clear();

    /**
     * @brief Gets all configuration keys
     * @return Vector of configuration keys
     */
    std::vector<std::string> getKeys() const;

    /**
     * @brief Displays all configuration settings
     */
    void display() const;

    /**
     * @brief Creates default configuration
     */
    void createDefaultConfig();

    /**
     * @brief Gets the configuration file path
     * @return Configuration file path
     */
    std::string getConfigFile() const { return configFile; }

    // Additional methods for test compatibility
    /**
     * @brief Checks if configuration is empty
     * @return true if empty, false otherwise
     */
    bool empty() const { return settings.empty(); }

    /**
     * @brief Gets the number of settings
     * @return Number of settings
     */
    size_t size() const { return settings.size(); }

    /**
     * @brief Sets a string value
     * @param key Configuration key
     * @param value String value
     */
    void setString(const std::string& key, const std::string& value);

    /**
     * @brief Gets a string value
     * @param key Configuration key
     * @param defaultValue Default value
     * @return String value
     */
    std::string getString(const std::string& key, const std::string& defaultValue = "") const;

    /**
     * @brief Sets an integer value
     * @param key Configuration key
     * @param value Integer value
     */
    void setInt(const std::string& key, int value);

    /**
     * @brief Sets a double value
     * @param key Configuration key
     * @param value Double value
     */
    void setDouble(const std::string& key, double value);

    /**
     * @brief Sets a boolean value
     * @param key Configuration key
     * @param value Boolean value
     */
    void setBool(const std::string& key, bool value);

    /**
     * @brief Removes a key
     * @param key Key to remove
     */
    void removeKey(const std::string& key);

    /**
     * @brief Creates default configuration
     * @return Default configuration
     */
    static Config createDefault();
}; 