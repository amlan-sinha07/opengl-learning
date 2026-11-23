/*
 * This class mostly will represent KOHI engine's
 * Logger and have a few differences only
 * author: Debargha Bose
 */
#pragma once

#include <cassert>
#include <cstdlib>
#include <format>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

// SUCH LOGS CAN BE DISABLED
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1

#ifndef NDEBUG
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#else
    // Release builds drop Debug/Trace entirely
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

// Prepend [HH:MM:SS.mmm] to every line
#ifndef LOG_TIMESTAMP_ENABLED
#define LOG_TIMESTAMP_ENABLED 1
#endif

// ANSI colors, only used when stderr is a terminal
#ifndef LOG_COLOR_ENABLED
#define LOG_COLOR_ENABLED 1
#endif

namespace Log {
enum class Level { Fatal = 0, Error = 1, Warn = 2, Info = 3, Debug = 4, Trace = 5 };

static_assert(Level::Fatal < Level::Error && Level::Error < Level::Warn &&
                  Level::Warn < Level::Info && Level::Info < Level::Debug &&
                  Level::Debug < Level::Trace,
              "Log levels must be ordered from most severe to least severe.");

// Thread safe: level is atomic and writes are serialized.
[[nodiscard]] auto isEnabled(Level level) -> bool;
void setLevel(Level level);

[[nodiscard]] auto levelFromString(std::string_view name) -> std::optional<Level>;

// Reads LOG_LEVEL (fatal|error|warn|info|debug|trace) and overrides the
// current level when the variable is set to a valid value.
void initFromEnv();

void write(Level level, const char *file, int line, std::string_view message);

template <typename... Args>
void output(Level level, const char *file, int line, std::format_string<Args...> fmt,
            const Args &...args) {
    if (!isEnabled(level)) {
        return;
    }
    write(level, file, line, std::vformat(fmt.get(), std::make_format_args(args...)));
}
[[noreturn]] inline void assertFail(const char *file, int line, std::string_view expr,
                                    std::string_view message) {
    output(Level::Error, file, line, "Assertion failed: {} -- {}", expr, message);
    std::abort();
}
}

//? macros for LOG calling
//! names for the macros have been not changed
#define KFATAL(...) Log::output(Log::Level::Fatal, __FILE__, __LINE__, __VA_ARGS__)

#define KERROR(...) Log::output(Log::Level::Error, __FILE__, __LINE__, __VA_ARGS__)

#if LOG_INFO_ENABLED == 1
#define KINFO(...) Log::output(Log::Level::Info, __FILE__, __LINE__, __VA_ARGS__)
#else
#define KINFO(...) ((void)0)
#endif

#if LOG_WARN_ENABLED == 1
#define KWARN(...) Log::output(Log::Level::Warn, __FILE__, __LINE__, __VA_ARGS__)
#else
#define KWARN(...) ((void)0)
#endif

#if LOG_DEBUG_ENABLED == 1
#define KDEBUG(...) Log::output(Log::Level::Debug, __FILE__, __LINE__, __VA_ARGS__)
#else
#define KDEBUG(...) ((void)0)
#endif

#if LOG_TRACE_ENABLED == 1
#define KTRACE(...) Log::output(Log::Level::Trace, __FILE__, __LINE__, __VA_ARGS__)
#else
#define KTRACE(...) ((void)0)
#endif

// Compiles out completely in release builds (NDEBUG).
#ifdef NDEBUG
#define KASSERT(condition, message) ((void)0)
#else
#define KASSERT(condition, message)         \
    (static_cast<bool>(condition) ? (void)0 \
                                  : Log::assertFail(__FILE__, __LINE__, #condition, (message)))

#endif
