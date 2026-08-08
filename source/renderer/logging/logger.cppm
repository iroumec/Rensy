module;

#include <mutex>
#include <ctime>
#include <chrono>
#include <format>
#include <fstream>
#include <string_view>

export module renderer:logging.logger;

// ============================================================================
// Imports
// ============================================================================

import :logging.level;

// ============================================================================
// Declarations
// ============================================================================

static std::string timestampedFileName(const std::string &fileName)
{
    const auto now = std::chrono::system_clock::now();
    const auto date = std::chrono::system_clock::to_time_t(now);

    const std::tm localTime = *std::localtime(&date);

    char timestamp[32];

    std::strftime(
        timestamp,
        sizeof(timestamp),
        "%Y-%m-%d_%H-%M-%S",
        &localTime);

    const auto dot = fileName.find_last_of('.');

    if (dot == std::string::npos)
    {
        return fileName + "_" + timestamp;
    }

    return fileName.substr(0, dot) + "_" + timestamp + fileName.substr(dot);
}

export class Logger
{
    LogLevel currentLevel;
    mutable std::mutex mutex;
    mutable std::ofstream file;

public:
    Logger(
        LogLevel level = LogLevel::Info,
        const std::string &fileName = "renderer.log")
        : currentLevel{level},
          file{timestampedFileName(fileName), std::ios::app} {}

    constexpr bool enabled(LogLevel level) const
    {
        return level <= currentLevel;
    }

    template <typename... Args>
    void log(
        LogLevel level,
        std::format_string<Args...> format,
        Args &&...args) const
    {
        if (!enabled(level))
            return;

        std::string message = std::format(format, std::forward<Args>(args)...);

        // Lock is automatically freed when the scope ends.
        {
            std::lock_guard lock(mutex);

            file << message << '\n';
            file.flush();
        }
    }

    template <typename... Args>
    void error(
        std::format_string<Args...> format,
        Args &&...args) const
    {
        if (!enabled(LogLevel::Error))
            return;

        log(LogLevel::Error,
            format,
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warning(
        std::format_string<Args...> format,
        Args &&...args) const
    {
        if (!enabled(LogLevel::Warning))
            return;

        log(LogLevel::Warning,
            format,
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(
        std::format_string<Args...> format,
        Args &&...args) const
    {
        if (!enabled(LogLevel::Info))
            return;

        log(LogLevel::Info,
            format,
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(
        std::format_string<Args...> format,
        Args &&...args) const
    {
        if (!enabled(LogLevel::Debug))
            return;

        log(LogLevel::Debug,
            format,
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    void trace(
        std::format_string<Args...> format,
        Args &&...args) const
    {
        if (!enabled(LogLevel::Trace))
            return;

        log(LogLevel::Trace,
            format,
            std::forward<Args>(args)...);
    }
};

// ============================================================================
// EOF
// ============================================================================
