#pragma once
#include <fstream>

class Logger {

public:
    static Logger& Instance();

    void Init();

    void Log(const std::string& level, const std::string& message);

    void Info(const std::string& msg) { Log("INFO", msg); }
    void Warn(const std::string& msg) { Log("WARN", msg); }
    void Error(const std::string& msg) { Log("ERROR", msg); }
    void Fatal(const std::string& msg) { Log("FATAL", msg); }

    ~Logger() {
        Info("Log file closed\n");
        if (logFile.is_open()) {
            logFile.close();
        }
    }

private:
    Logger() = default;
    std::fstream logFile;
};


#define LOG_INFO(msg)  Logger::Instance().Info(msg)
#define LOG_WARN(msg)  Logger::Instance().Warn(msg)
#define LOG_ERROR(msg) Logger::Instance().Error(msg)
#define LOG_FATAL(msg) Logger::Instance().Fatal(msg)