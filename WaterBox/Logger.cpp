#include "Logger.h"
#include "WaterBox.h"
#include <chrono>
#include <sstream>
#include "SDL3/SDL.h"
#include <filesystem>

#ifdef ENABLE_CONSOLE

#define DEBUG_CONTAINER(param) param
#include <iostream>

#else

#define DEBUG_CONTAINER(param)

#endif



#ifdef __ANDROID__
#include <android/log.h>

#define LOGCAT_INFO(msg) \
    __android_log_print(ANDROID_LOG_INFO, "WaterBox", "%s", msg)

#else

#define LOGCAT_INFO(msg)

#endif


Logger& Logger::Instance(){
    static Logger logger;
    return logger;
}

void Logger::Init()
{
    std::string filename;

#ifdef ENABLE_CONSOLE
    filename = "WaterBox_LOG.log";
#else
    auto* pref = SDL_GetPrefPath("WaterBox", "WaterBox");

    std::filesystem::path path(pref);
    path /= "WaterBox.log";

    filename = path.string();

    SDL_free(pref);
#endif


    


    logFile.open(filename, std::ios::out);
    if (!logFile.is_open()) {
        DEBUG_CONTAINER (std::cerr << "Failed to open log file: " << filename << std::endl);
    }
    Info("Log file opened\n");
}

void Logger::Log(const std::string& level, const std::string& message)
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif



    std::stringstream ss;
    ss << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";
    ss << "[" << level << "] " << message << "\n";

    std::string formatted = ss.str();


    if (logFile.is_open()) {
        logFile << formatted;
        logFile.flush();
    }

#ifdef __ANDROID__
    __android_log_print(
        ANDROID_LOG_INFO,
        "WaterBox",
        "%s",
        formatted.c_str());
#else
    DEBUG_CONTAINER(std::cout << formatted);
#endif
}
