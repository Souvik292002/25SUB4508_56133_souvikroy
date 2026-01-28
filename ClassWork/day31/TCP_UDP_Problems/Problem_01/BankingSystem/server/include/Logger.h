#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>

/*
 Logger:
 - Handles persistent logging
 - Thread-safe
 - Used for invalid access attempts
*/
class Logger {
private:
    std::mutex logMutex;
    std::string logFilePath;

public:
    explicit Logger(const std::string& filePath);
    void log(const std::string& message);
};

#endif
