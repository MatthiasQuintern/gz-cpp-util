#pragma once

#include <vector>

#include "string/to_string.hpp"

#include <iostream>
#include <string>

#define LOG_SUBLOGS

#ifdef LOG_SUBLOGS
#include <memory>
#endif

#ifdef LOG_MULTITHREAD 
#include <mutex>
#endif

// the higher level needs to include the lower ones
#ifdef LOG_LEVEL_0
#define LOG_LEVEL_1
#endif

#ifdef LOG_LEVEL_1
#define LOG_LEVEL_2
#endif

#ifdef LOG_LEVEL_2
#define LOG_LEVEL_3
#endif

namespace gz {
    /// Reserve a string size for each string in logArray. Set to 0 if you do not want to reserve memory for strings.
    constexpr unsigned int LOG_RESERVE_STRING_SIZE = 100;
    constexpr unsigned int ARG_COUNT_RESERVE_COUNT = 6;

    constexpr unsigned int LOG_TIMESTAMP_CHAR_COUNT = 22;
    constexpr unsigned int LOG_POSTPREFIX_CHAR_COUNT = 2;


    //
    // COLORS
    //
    /// Colors to be used in Log::clog
    enum Color {
        RESET, 
        BLACK,  RED,  GREEN,  YELLOW,  BLUE,  MAGENTA,  CYAN,  WHITE, 
        BO_BLACK, BO_RED, BO_GREEN, BO_YELLOW, BO_BLUE, BO_MAGENTA, BO_CYAN, BO_WHITE,
        BG_BLACK, BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE,
        LI_RED,  LI_GREEN,  LI_YELLOW,  LI_BLUE,  LI_MAGENTA,  LI_CYAN,  LI_WHITE, LI_BLACK,
    };
    extern const char* COLORS[];


    //
    // LOG
    //
    /**
     * @brief Define types that can be logged with Log
     * @details
     *  Log can log everything where `gz::toString(const T&)` exists.
     *  See @ref sc_toStringImplemented "this for more details".
     */
    template<typename T>
    concept Logable = ConvertibleToString<T>;

    class Log;
    /**
     * @brief Create info for a Log object
     */
    struct LogCreateInfo {
        /// @brief Absolute or relative path to the logfile
        std::string logfile = "log.log";
        /// @brief Wether to print the messages to stdout
        bool showLog = true;
        /// @brief Wether to save the messages to the logfile
        bool storeLog = true;
        /// @brief A prefix that comes between the timestamp and the message. ": " is automatically appended to the prefix
        std::string prefix = "";
        /// @brief The color of the prefix
        Color prefixColor = RESET;
        /// @brief Wether to prepend a timestamp to the message
        bool showTime = true;
        /// @brief The color of the timestamp
        Color timeColor = RESET;
        /// @brief If true, clear the logfile when initializing the log. That means only the log of most recent run is stored
        bool clearLogfileOnRestart = true;
        /// @brief Actually write the log to the logfile after so many lines. Must be at least 1
        unsigned int writeAfterLines = 100;
    };

#ifdef LOG_SUBLOGS
    /**
     * @brief Resources that are normally members of Log when not using `LOG_SUBLOGS`
     */
    struct LogResources {
        /// Where the lines are stored
        std::vector<std::string> logLines;
        /// Used during log: string views into the single substrings in logLines[currentLine]
        std::vector<std::string::size_type> argsBegin;
        /// The current position in logLines
        size_t iter = 0;


        unsigned int writeToFileAfterLines;
        bool clearLogfileOnRestart;
        /// Absolute path to the logfile
        std::string logFile;
        bool storeLog;

        bool showTime;
        Color timeColor;
        /// Stores the current time in yyyy-mm-dd hh:mm:ss format
        char time[LOG_TIMESTAMP_CHAR_COUNT];
    };  // class LogResources
#endif

/**
 * @brief Manages printing messages to stdout and to logfiles.
 * @details
 *  @subsection log_concepts Logable types
 *   Log uses concepts to determine if a type is logable and how it should be logged. See the documentation for concept Logable for more details.
 *   
 *   If you want your custom data type to be logable, @ref sc_ov_toString "write an overload for gz::toString()"
 *
 *  @subsection log_threads Thread safety
 *   Log can use a static mutex for thread safety. To use this feature, you have to `#define LOG_MULTITHREAD` @b before including `log.hpp`.
 *   Note that log uses the default std::cout buffer, so you should make sure it is not being used while logging something.
 *
 *  @subsection log_subs Sublogs
 *   If you want multiple log instances that share a logfile, you can @ref createSublog "create a sublog" from the parent.
 *   The sublog inherits all settings and resources from the parent, except for showLog and the prefix.
 *   This feature is not available by default, you need to `#define LOG_SUBLOGS`.
 *
 *   Note that the sublog may outlive the parent, as they @ref LogResources "share their resources" with a shared_ptr.
 *   You can also create sublogs from sublogs.
 *
 *  @subsection log_logfile Logfile
 *   The logs can be written to a logfile, which can be specified in the constructor.
 *   The logs are not continuously written to the logfile, since file operations are expensive. 
 *   Instead, the log is stored in memory and written to the file if a certain number of lines is reached, which you can specify in the constructor.
 *   If you want the log to be continuously written to the file, set `writeAfterLines` to 1.
 *
 *  @subsection log_levels Loglevels
 *   There are 4 different log levels (0-3), where the lower ones include the higher ones.
 *   To set the log level to `X`, where `X` is one of {0, 1, 2, 3}, 
 *   define `#define LOG_LEVEL_X` @b before including `log.hpp`.
 *   You can then use @ref log0 "logX" or @ref clog0 "clogX".
 *
 *   If @ref log0 "logX" function log level is lower than the set log level, 
 *   the function call will be a noop and thus optimized away be the compiler.\n
 *   You can think of:
 *   - `LOG_LEVEL_0` as "trace"
 *   - `LOG_LEVEL_1` as "debug"
 *   - `LOG_LEVEL_2` as "info"
 *   - `LOG_LEVEL_3` as "error/important"
 *
 *   @note operator()(), log(), clog(), warning() and error() are always 'on', regardless of which (if any) log level is defined.
 *   
 * @todo Exception policies
 * @todo Use own ostream and not std::cout
 * @todo Make colors cross platform
 */
class Log {
    public:
        /**
         * @brief Create a log with default settings
         * @details
         *  - `showLog = true`
         *  - `storeLog = false`
         *  - `prefix = ""`
         *  - `showTime = false`
         */
        Log();
        /**
         * @brief Creates a log object, which can print messages to stdout and/or write them to a log file
         * @details 
         *  By creating multiple instances with different parameters, logs can be easily turned on/off for different usages.
         */
        Log(LogCreateInfo&& createInfo);
#ifdef LOG_SUBLOGS
        Log createSublog(bool showLog, const std::string& prefix, Color prefixColor=gz::Color::RESET); 
    private:
        Log(std::shared_ptr<LogResources>&& resources, bool showLog, const std::string& prefix, Color prefixColor);
    public:
#endif
        ~Log();

    // 
    // ACTUAL LOGGING
    //
        /**
         * @name Logging
         */
        /// @{
        /**
         * @brief Logs a message
         * @details Depending on the settings of the log instance, the message will be printed to stdout and/or written to the logfile.
         *  The current date and time is placed before the message.
         *  The message will look like this:
         *  \<time>: \<prefix>: \<message>
         *  where time will be white, prefix in prefixColor and message white.
         * @param args Any number of arguments that satisfy concept Logable
         */
        template<Logable... Args>
        void log(Args&&... args);

        /**
         * @brief Log a message in a certain color
         * @details
         *  The message will look like this:
         *  \<time>: \<prefix>: \<message0> \<message1>...
         *  where time will be white, prefix in prefixColor, and messageI in colors[I]. 
         *  If there are less colors than message arguments, the last color is used for all remaining messages.
         * @param args Any number of arguments that satisfy concept Logable
         * @param colors Vector of colors, where the nth color refers to the nth arg
         */
        template<Logable... Args>
        void clog(const std::vector<Color>& colors, Args&&... args);


    // 
    // CONVENCIENCE
    //
        /**
         * @brief Logs a message. Overload for convenience, same behavior as log()
         */
        template<Logable... Args>
        void operator() (Args&&... args) {
            log(std::forward<Args>(args)...);
        }

        /**
         * @brief Log an error
         * @details Prints the message with a red "Error: " prefix.
         *  The message will look like this:
         *  \<time>: \<prefix>: Error: \<message>
         *  where time will be white, prefix in prefixColor, Error in red and message white.
         * @param args Any number of arguments that satisfy concept Logable
         */
        template<Logable... Args>
        void error(Args&&... args) {
            clog({RED, WHITE}, "Error:", std::forward<Args>(args)...);
        }

        /**
         * @brief Log a warning
         * @details Prints the message with a yellow "Warning: " prefix.
         *  The message will look like this:
         *  \<time>: \<prefix>: Warning: \<message>
         *  where time will be white, prefix in prefixColor, Warning in yellow and message white.
         * @param args Any number of arguments that satisfy concept Logable
         */
        template<Logable... Args>
        void warning(Args&&... args) {
            clog({YELLOW, WHITE}, "Warning:", std::forward<Args>(args)...);
        }
        /// @}
        /**
         * @name Logging at different levels
         */
        /// @{
        /**
         * @brief Enabled with LOG_LEVEL_0 or higher
         */
        template<Logable... Args>
        inline void log0(Args&&... args);
        /**
         * @brief Enabled with LOG_LEVEL_1 or higher
         */
        template<Logable... Args>
        inline void log1(Args&&... args);
        /**
         * @brief Enabled with LOG_LEVEL_2 or higher
         */
        template<Logable... Args>
        inline void log2(Args&&... args);
        /**
         * @brief Enabled with LOG_LEVEL_3 or higher
         */
        template<Logable... Args>
        inline void log3(Args&&... args);

        /**
         * @brief Enabled with LOG_LEVEL_0 or higher
         */
        template<Logable... Args>
        inline void clog0(const std::vector<Color>& colors, Args&&... args);
        /**
         * @brief Enabled with LOG_LEVEL_1 or higher
         */
        template<Logable... Args>
        inline void clog1(const std::vector<Color>& colors, Args&&... args);
        /**
         * @brief Enabled with LOG_LEVEL_2 or higher
         */
        template<Logable... Args>
        inline void clog2(const std::vector<Color>& colors, Args&&... args);
        /**
         * @brief Enabled with LOG_LEVEL_3 or higher
         */
        template<Logable... Args>
        inline void clog3(const std::vector<Color>& colors, Args&&... args);
        /// @}

    private:
        // vlog for variadic log
        /// Log anything that can be appendend to std::string
        template<util::Stringy T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args);

        /// Log anything where toString exists
        template<ConvertibleToString T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args) requires (!util::Stringy<T>);

        /// End for the recursion
        void vlog(const char* appendChars) {};

    private:
        void init();

#ifdef LOG_SUBLOGS
        std::shared_ptr<LogResources> resources;

        std::vector<std::string>& logLines() { return resources->logLines; };
        std::vector<std::string::size_type>& argsBegin() { return resources->argsBegin; };
        size_t& iter() { return resources->iter; };

        unsigned int& writeToFileAfterLines() { return resources->writeToFileAfterLines; };
        bool& clearLogfileOnRestart() { return resources->clearLogfileOnRestart; };
        std::string& logFile() { return resources->logFile; };
        bool& storeLog() { return resources->storeLog; };

        bool& showTime() { return resources->showTime; };
        Color& timeColor() { return resources->timeColor; };
        char* time() { return resources->time; };
#else
        /// Where the lines are stored
        std::vector<std::string> logLines_;
        /// Used during log: string views into the single substrings in logLines[currentLine]
        std::vector<std::string::size_type> argsBegin_;
        /// The current position in logLines
        size_t iter_ = 0;

        /// When iter reaches writeToFileAfterLines, write log to file
        unsigned int writeToFileAfterLines_;
        bool clearLogfileOnRestart_;
        /// Absolute path to the logfile
        std::string logFile_;
        bool storeLog_;

        bool showTime_;
        Color timeColor_;
        /// Stores the current time in yyyy-mm-dd hh:mm:ss format
        char time_[LOG_TIMESTAMP_CHAR_COUNT];

        // getters
        std::vector<std::string>& logLines() { return logLines_; };
        std::vector<std::string::size_type>& argsBegin() { return argsBegin_; };
        size_t& iter() { return iter_; };

        unsigned int& writeToFileAfterLines() { return writeToFileAfterLines_; };
        bool& clearLogfileOnRestart() { return clearLogfileOnRestart_; };
        std::string& logFile() { return logFile_; };
        bool& storeLog() { return storeLog_; };

        bool& showTime() { return showTime_; };
        Color& timeColor() { return timeColor_; };
        char* time() { return time_; };
#endif
        /**
         * @brief Write the log to the logfile
         * @details
         *  Opens the file in append mode and writes the strings in logLines from 0 to iter to it. Sets iter to 0.
         */
        void writeLog();

        bool showLog;
        Color prefixColor;
        std::string prefix;

        /// Store the current time in yyyy-mm-dd hh:mm:ss format in time member
        void getTime();

#ifdef LOG_MULTITHREAD 
        /// Lock for std::cout
        static std::mutex mtx;
#endif
}; // class Log


//
// DEFINITIONS
//
    template<Logable... Args>
    void Log::log(Args&&... args) {
#ifdef LOG_MULTITHREAD 
        mtx.lock();
#endif
        argsBegin().clear();
        if (showTime()) {
            getTime();
            logLines()[iter()] = time();
        }
        else {
            logLines()[iter()].clear();
        }
        argsBegin().emplace_back(logLines()[iter()].size());
        logLines()[iter()] += prefix;

        vlog(" ", std::forward<Args>(args)...);
        logLines()[iter()] += "\n";
        argsBegin().emplace_back(logLines()[iter()].size());

        if (showLog) {
            // time
            std::cout << COLORS[timeColor()] << std::string_view(logLines()[iter()].begin(), logLines()[iter()].begin() + argsBegin()[0]) 
            // prefix
                << COLORS[prefixColor] << std::string_view(logLines()[iter()].begin() + argsBegin()[0], logLines()[iter()].begin() + argsBegin()[1]) << COLORS[RESET]
            // message
                << std::string_view(logLines()[iter()].begin() + argsBegin()[1], logLines()[iter()].end());
        }
        if (++iter() >= writeToFileAfterLines()) {
            iter() = 0;
            writeLog();
        }
#ifdef LOG_MULTITHREAD 
        mtx.unlock();
#endif
    }


    template<Logable... Args>
    void Log::clog(const std::vector<Color>& colors, Args&&... args) {
#ifdef LOG_MULTITHREAD 
        mtx.lock();
#endif
        argsBegin().clear();
        if (showTime()) {
            getTime();
            logLines()[iter()] = std::string(time());
        }
        else {
            logLines()[iter()].clear();
        }
        argsBegin().emplace_back(logLines()[iter()].size());
        logLines()[iter()] += prefix;

        vlog(" ", std::forward<Args>(args)...);
        logLines()[iter()] += "\n";
        argsBegin().emplace_back(logLines()[iter()].size());

        if (showLog) {
            // time
            std::cout << COLORS[timeColor()] << std::string_view(logLines()[iter()].begin(), logLines()[iter()].begin() + argsBegin()[0]) 
            // prefix
                << COLORS[prefixColor] << std::string_view(logLines()[iter()].begin() + argsBegin()[0], logLines()[iter()].begin() + argsBegin()[1]) << COLORS[RESET];
            // max index where i can be used for colors and i+2 can be used for currentViews
            size_t maxI = std::min(colors.size(), argsBegin().size() - 2);
            for (size_t i = 0; i < maxI; i++) {
                std::cout << COLORS[colors[i]] << std::string_view(logLines()[iter()].begin() + argsBegin()[i+1], logLines()[iter()].begin() + argsBegin()[i+2]);
            }
            // log the rest, maxI is now <= argsBegin.size() - 2
            std::cout << std::string_view(logLines()[iter()].begin() + argsBegin()[maxI+1], logLines()[iter()].end()) << COLORS[RESET];
        }
        if (++iter() >= writeToFileAfterLines()) {
            iter() = 0;
            writeLog();
        }
#ifdef LOG_MULTITHREAD 
        mtx.unlock();
#endif
    };


    template<util::Stringy T, Logable... Args>
    void Log::vlog(const char* appendChars, T&& t,  Args&&... args) {
        argsBegin().emplace_back(logLines()[iter()].size());
        logLines()[iter()] += std::string(t);
        logLines()[iter()] += appendChars;
        vlog(" ", std::forward<Args>(args)...);
    }
    /// Log anything where toString exists
    template<ConvertibleToString T, Logable... Args>
    void Log::vlog(const char* appendChars, T&& t,  Args&&... args) requires (!util::Stringy<T>) {
        argsBegin().emplace_back(logLines()[iter()].size());
        logLines()[iter()] += toString(t);
        logLines()[iter()] += appendChars;
        vlog(" ", std::forward<Args>(args)...);
    }


    template<Logable... Args>
    inline void Log::log0(Args&&... args) {
#ifdef LOG_LEVEL_0
        this->log(std::forward<Args>(args)...);
#endif
    }

    template<Logable... Args>
    inline void Log::log1(Args&&... args) {
#ifdef LOG_LEVEL_1
        this->log(std::forward<Args>(args)...);
#endif
    }

    template<Logable... Args>
    inline void Log::log2(Args&&... args) {
#ifdef LOG_LEVEL_2
        this->log(std::forward<Args>(args)...);
#endif
    }

    template<Logable... Args>
    inline void Log::log3(Args&&... args) {
#ifdef LOG_LEVEL_3
        this->log(std::forward<Args>(args)...);
#endif
    }


    template<Logable... Args>
    inline void Log::clog0(const std::vector<Color>& colors, Args&&... args) {
#ifdef LOG_LEVEL_0
        this->clog(colors, std::forward<Args>(args)...);
#endif
    }

    template<Logable... Args>
    inline void Log::clog1(const std::vector<Color>& colors, Args&&... args) {
#ifdef LOG_LEVEL_1
        this->clog(colors, std::forward<Args>(args)...);
#endif
    }

    template<Logable... Args>
    inline void Log::clog2(const std::vector<Color>& colors, Args&&... args) {
#ifdef LOG_LEVEL_2
        this->clog(colors, std::forward<Args>(args)...);
#endif
    }

    template<Logable... Args>
    inline void Log::clog3(const std::vector<Color>& colors, Args&&... args) {
#ifdef LOG_LEVEL_3
        this->clog(colors, std::forward<Args>(args)...);
#endif
    }
} // namespace gz

/**
 * @file
 * @brief A logger capable of logging lots of different types and containers to stdout and/or a logfile.
 */
