#include "Config.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>

Config::Config() : configFile("") {}

Config::Config(const std::string& filename) : configFile(filename) {
    if (!filename.empty()) {
        loadFromFile(filename);
    }
}

bool Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        auto [key, value] = parseLine(line);
        if (!key.empty()) {
            settings[key] = value;
        }
    }

    configFile = filename;
    return true;
}

bool Config::saveToFile(const std::string& filename) {
    std::string outputFile = filename.empty() ? configFile : filename;
    if (outputFile.empty()) {
        return false;
    }

    std::ofstream file(outputFile);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& [key, value] : settings) {
        file << key << "=" << value << "\n";
        if (file.fail()) {
            return false;
        }
    }

    return file.good();
}

void Config::set(const std::string& key, const std::string& value) {
    settings[key] = value;
}

std::string Config::get(const std::string& key, const std::string& defaultValue) const {
    auto it = settings.find(key);
    return (it != settings.end()) ? it->second : defaultValue;
}

int Config::getInt(const std::string& key, int defaultValue) const {
    auto it = settings.find(key);
    if (it == settings.end()) {
        return defaultValue;
    }

    try {
        return std::stoi(it->second);
    } catch (const std::exception&) {
        return defaultValue;
    }
}

double Config::getDouble(const std::string& key, double defaultValue) const {
    auto it = settings.find(key);
    if (it == settings.end()) {
        return defaultValue;
    }

    try {
        return std::stod(it->second);
    } catch (const std::exception&) {
        return defaultValue;
    }
}

bool Config::getBool(const std::string& key, bool defaultValue) const {
    auto it = settings.find(key);
    if (it == settings.end()) {
        return defaultValue;
    }

    std::string value = toLower(it->second);
    return (value == "true" || value == "1" || value == "yes" || value == "on");
}

bool Config::hasKey(const std::string& key) const {
    return settings.find(key) != settings.end();
}

void Config::remove(const std::string& key) {
    settings.erase(key);
}

void Config::clear() {
    settings.clear();
}

std::vector<std::string> Config::getKeys() const {
    std::vector<std::string> keys;
    keys.reserve(settings.size());
    for (const auto& [key, value] : settings) {
        keys.push_back(key);
    }
    return keys;
}

void Config::display() const {
    std::cout << "\nConfiguration Settings:\n";
    std::cout << "========================\n";
    for (const auto& [key, value] : settings) {
        std::cout << key << " = " << value << "\n";
    }
    std::cout << "========================\n";
}

void Config::createDefaultConfig() {
    settings.clear();
    
    // Default algorithm settings
    settings["algorithm.max_iterations"] = "1000";
    settings["algorithm.timeout_ms"] = "5000";
    settings["algorithm.threads"] = "4";
    
    // Default logging settings
    settings["logging.level"] = "INFO";
    settings["logging.file"] = "road_construction.log";
    settings["logging.console"] = "true";
    
    // Default performance settings
    settings["performance.benchmark_iterations"] = "100";
    settings["performance.enable_profiling"] = "true";
    
    // Default file paths
    settings["paths.data_dir"] = "./data";
    settings["paths.output_dir"] = "./output";
    settings["paths.temp_dir"] = "./temp";
}

std::pair<std::string, std::string> Config::parseLine(const std::string& line) const {
    std::string trimmed = trim(line);
    if (trimmed.empty() || trimmed[0] == '#') {
        return {"", ""};
    }

    size_t pos = trimmed.find('=');
    if (pos == std::string::npos) {
        return {"", ""};
    }

    std::string key = trim(trimmed.substr(0, pos));
    std::string value = trim(trimmed.substr(pos + 1));

    return {key, value};
}

std::string Config::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::string Config::toLower(const std::string& str) const {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Additional methods for test compatibility
void Config::setString(const std::string& key, const std::string& value) {
    set(key, value);
}

std::string Config::getString(const std::string& key, const std::string& defaultValue) const {
    return get(key, defaultValue);
}

void Config::setInt(const std::string& key, int value) {
    set(key, std::to_string(value));
}

void Config::setDouble(const std::string& key, double value) {
    set(key, std::to_string(value));
}

void Config::setBool(const std::string& key, bool value) {
    set(key, value ? "true" : "false");
}

void Config::removeKey(const std::string& key) {
    remove(key);
}

Config Config::createDefault() {
    Config config;
    config.createDefaultConfig();
    return config;
} 