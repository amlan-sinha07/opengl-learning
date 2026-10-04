/* 
* This class mostly will represent KOHI engine's
* Logger and have a few differences only
* author: Debargha Bose
 */
#pragma once

#include <cassert>

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

namespace Log {
    enum class Level {
        Fatal = 0,
        Error = 1,
        Warn = 2,
        Info = 3,
        Debug = 4,
        Trace = 5
    };

    static_assert(
        Level::Fatal < Level::Error
            && Level::Error < Level::Warn
            && Level::Warn < Level::Info
            && Level::Info < Level::Debug
            && Level::Debug < Level::Trace,
        "Log levels must be ordered from most severe to least severe."
    );

    //! not thread safe
    //todo make thread safe
    void output(Level level, const char* file, int line, const char* fmt, ...);
    void setLevel(Level level);
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

#define KASSERT(condition, message) \
    do { \
        const bool condition_result = static_cast<bool>(condition); \
        if (!condition_result) { \
            KERROR("Assertion failed: %s -- %s", #condition, message); \
        } \
        assert(condition_result); \
    } while (false)
