#include "logger.hpp"

#include <array>
#include <cstdarg>
#include <cstdio>
#include <string_view>

// anon namespace will hold max buffer size = 1024? or 4096?
// level -> string function
// ar ki?
namespace {
    constexpr std::size_t LOG_BUFFER_SIZE = 1024;

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

void Log::setLevel(Log::Level level) {
    currentLevel = static_cast<int>(level);
}

void Log::output(Log::Level level, const char *fmt, ...) {
    if (static_cast<int>(level) > currentLevel) {
        return;
    }

    std::array<char, LOG_BUFFER_SIZE> message{};

    va_list args;
    va_start(args, fmt);
    std::vsnprintf(message.data(), message.size(), fmt, args);
    va_end(args);

    std::fprintf(stderr, "[%s] %s\n", levelToString(level).data(), message.data());
}