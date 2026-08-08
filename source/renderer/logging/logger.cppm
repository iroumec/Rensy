module;

#include <mutex>
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
          file{fileName, std::ios::app} {}

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
