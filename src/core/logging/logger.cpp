#include "logger.hpp"

#include <atomic>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <print>
#include <string>

#if defined(_WIN32)
    #include <io.h>
#else
    #include <unistd.h>
#endif

namespace {
#if LOG_COLOR_ENABLED == 1
    constexpr std::string_view RESET = "\x1b[0m";
#endif

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

#if LOG_COLOR_ENABLED == 1
    [[nodiscard]]
    constexpr auto levelToColor(Log::Level level) -> std::string_view {
        switch (level) {
            case Log::Level::Fatal:
                return "\x1b[1;91m"; // bold bright red
            case Log::Level::Error:
                return "\x1b[31m";
            case Log::Level::Warn:
                return "\x1b[33m";
            case Log::Level::Info:
                return "\x1b[32m";
            case Log::Level::Debug:
                return "\x1b[36m";
            case Log::Level::Trace:
                return "\x1b[90m"; // bright black / gray
        }
        return "";
    }
#endif

    // A global mutex keeps each log line from interleaving with another
    // thread's output.
    std::mutex writeMutex;

    std::atomic<int> currentLevel{static_cast<int>(Log::Level::Info)};

    // Computed once, so we do not call isatty on every single log line.
    [[nodiscard]]
    auto colorsAvailable() -> bool {
#if LOG_COLOR_ENABLED == 1
        static const bool available = [] -> bool {
            // Respect the NO_COLOR convention for users who want plain output.
            if (std::getenv("NO_COLOR") != nullptr) {
                return false;
            }
#if defined(_WIN32)
            return _isatty(_fileno(stderr)) != 0;
#else
            return isatty(fileno(stderr)) != 0;
#endif
        }();
        return available;
#else
        return false;
#endif
}

    [[nodiscard]]
    auto formatTimestamp() -> std::string {
#if LOG_TIMESTAMP_ENABLED == 1
        const auto now = std::chrono::system_clock::now();
        const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                                now.time_since_epoch()) % 1000;

        const std::time_t seconds = std::chrono::system_clock::to_time_t(now);
        std::tm local{};
#if defined(_WIN32)
        localtime_s(&local, &seconds);
#else
        localtime_r(&seconds, &local);
#endif

        return std::format("[{:02}:{:02}:{:02}.{:03}] ",
                           local.tm_hour, local.tm_min, local.tm_sec,
                           millis.count());
#else
        return "";
#endif
    }
}

auto Log::isEnabled(Level level) -> bool {
    return static_cast<int>(level) <= currentLevel.load(std::memory_order_relaxed);
}

void Log::setLevel(Level level) {
    currentLevel.store(static_cast<int>(level), std::memory_order_relaxed);
}

auto Log::levelFromString(std::string_view name) -> std::optional<Level> {
    for (const Level level : {Level::Fatal, Level::Error, Level::Warn,
                              Level::Info, Level::Debug, Level::Trace}) {
        std::string_view candidate = levelToString(level);

        if (name.size() != candidate.size()) {
            continue;
        }

        bool matches = true;
        for (std::size_t i = 0; i < name.size(); ++i) {
            const auto lhs = static_cast<char>(
                std::tolower(static_cast<unsigned char>(name.at(i))));
            const auto rhs = static_cast<char>(
                std::tolower(static_cast<unsigned char>(candidate.at(i))));

            if (lhs != rhs) {
                matches = false;
                break;
            }
        }

        if (matches) {
            return level;
        }
    }

    return std::nullopt;
}

void Log::initFromEnv() {
    const char* value = std::getenv("LOG_LEVEL");

    if (value == nullptr) {
        return;
    }

    if (const auto level = levelFromString(value)) {
        setLevel(*level);
    } else {
        KWARN("Unknown LOG_LEVEL '{}', keeping current level", value);
    }
}

void Log::write(Level level, const char* file, int line, std::string_view message) {
    [[maybe_unused]] const bool useColor = colorsAvailable();

    std::string text = formatTimestamp();

#if LOG_COLOR_ENABLED == 1
    if (useColor) {
        text += levelToColor(level);
    }
#endif

    text += std::format("[{}]", levelToString(level));

#if LOG_COLOR_ENABLED == 1
    if (useColor) {
        text += RESET;
    }
#endif

    text += std::format(" {}:{}: {}\n",
                 file != nullptr ? file : "<unknown>",
                 line,
                 message);

    {
        const std::scoped_lock lock(writeMutex);
        std::print(stderr, "{}", text);
        std::fflush(stderr);
    }

    if (level == Level::Fatal) {
        std::abort();
    }
}