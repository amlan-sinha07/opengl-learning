#include "logger.hpp"

#include <print>

namespace {
    [[nodiscard]]
    auto levelToString(Log::Level level) -> std::string_view {
        switch (level) {
            case Log::Level::Fatal:
                return "FATAL";
            case Log::Level::Error:
                return "ERROR";
            case Log::Level::Warn:
                return "WARN";
            case Log::Level::Info:
                return "INFO";
            case Log::Level::Debug:
                return "DEBUG";
            case Log::Level::Trace:
                return "TRACE";
        }
        return "UNKNOWN";
    }

    int currentLevel{static_cast<int>(Log::Level::Info)};
}

bool Log::isEnabled(Level level) {
    return static_cast<int>(level) <= currentLevel;
}

void Log::setLevel(Level level) {
    currentLevel = static_cast<int>(level);
}

void Log::write(Level level, const char* file, int line, std::string_view message) {
    std::println(stderr, "[{}] {}:{}: {}",
                 levelToString(level),
                 file != nullptr ? file : "<unknown>",
                 line,
                 message);
}