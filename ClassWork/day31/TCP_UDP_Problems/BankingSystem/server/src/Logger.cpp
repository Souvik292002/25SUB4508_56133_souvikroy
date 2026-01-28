#include "../include/Logger.h"
#include <fstream>
#include <ctime>

Logger::Logger(const std::string& filePath)
    : logFilePath(filePath) {}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);

    std::ofstream file(logFilePath, std::ios::app);
    time_t now = time(nullptr);

    file << "[" << ctime(&now) << "] "
         << message << std::endl;
}
