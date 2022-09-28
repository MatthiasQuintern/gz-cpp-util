#pragma once

#include <vector>
#define LOG_MULTITHREAD

#include "util/string_conversion.hpp"

#include <iostream>
#include <string>

#ifdef LOG_MULTITHREAD 
#include <mutex>
#endif

namespace gz {

    /// Reserve a string size for each string in logArray. Set to 0 if you do not want to reserve memory for strings.
    constexpr unsigned int LOG_RESERVE_STRING_SIZE = 100;

    constexpr unsigned int LOG_TIMESTAMP_CHAR_COUNT = 22;
    constexpr unsigned int LOG_POSTPREFIX_CHAR_COUNT = 2;


    //
    // COLORS
    //
    /// Colors to be used in Log::clog
    enum Color {
        RESET, BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, BBLACK, BRED, BGREEN, BYELLOW, BBLUE, BMAGENTA, BCYAN, BWHITE
    };
    extern const char* COLORS[];


    //
    // LOG
    //
    /**
     * @brief Define types that can be logged with Log
     * @details
     *  As of now you can log type T with instance t:
     *  -# Any @ref util::Stringy "string-like type": eg. std::string, std::string_view 
     *  -# Any @ref util::WorksWithStdToString "type that works with std::toString()"
     *  -# Any @ref util::HasToStringMember "type that has a toString() const member that returns a string"
     *  -# Any @ref util::ContainerConvertibleToString "type that has a forward_iterator" which references any one of 1-3
     *  -# Any @ref util::PairConvertibleToString "type with t.first, t.second" provided t.first satisfies one of 1-4 and t.second satisfies 1-4
     *  -# Any @ref util::MapConvertibleToString "type that has a forward_iterator" which references 5
     *  -# Any @ref util::Vector2ConvertibleToString "type with t.x and t.y", provided t.x and t.y satisfy one of 1-6
     *  -# Any @ref util::Vector3ConvertibleToString "type with t.x, t.y, t.z", provided t.x, t.y, t.z satisfy one of 1-6
     *  -# Any @ref util::Vector4ConvertibleToString "type with t.x, t.y, t.z and t.w", provided t.x, t.y, t.z, t.w satisfy one of 1-6
     *  -# Any @ref ConvertibleToString "type for which an overload of" <code>util::Stringy toString(const T&)</code> exists in global or gz namespace
     *
     *  The higher number takes precedence in overload resolution for the log function.
     *
     *  1-6 include for example:
     *  - int, float, bool...
     *  - std::vector<std::string>, std::list<unsigned int>
     *  - std::map<std::string, std::vector<A>> if A.toString() returns a string - ...
     */
    template<typename T>
    concept Logable = ConvertibleToString<T>;

/**
 * @brief Manages printing messages to stdout and to logfiles.
 * @details
 *  @subsection log_concepts Logable types
 *   Log uses concepts to determine if a type is logable and how it should be logged. See the documentation for concept Logable for more details.
 *   
 *   If you want your custom data type to be logable, it easiest to provide a member function with this signature:
 *   @code
 *          public:
 *              std::string toString() const;
 *   @endcode
 *   Alternatively, or if the type is not a class overload <code> std::string toString(const T& t) </code> in global or gz namespace.
 *
 *  @subsection log_threads Thread safety
 *   Log can use a static mutex for thread safety. To use this feature, you have to #define LOG_MULTITHREAD at the top of log.hpp.
 *   Note that log uses the default std::cout buffer, so you should make sure it is not being used while logging something.
 *
 *  @subsection log_logfile Logfile
 *   The logs can be written to a logfile, which can be specified in the constructor.
 *   The logs are not continuously written to the logfile, since file operations are expensive. 
 *   Instead, the log is stored in memory and written to the file if a certain number of lines is reached, which you can specify in the constructor.
 *   If you want the the log to be continuously written to the file, set writeAfterLines=1.
 *
 * @todo Exception policies
 * @todo Remove vec2 or add vec3, vec4
 *
 */
class Log {
    public:
        /**
         * @brief Creates a log object, which can print messages to stdout and/or write them to a log file
         * @details By creating multiple instances with different parameters, logs can be easily turned on/off for different usages.
         *  If not existent, the parent directory of the logfile and the file itself will be created when initializing a log.
         *
         * @param logfile: Absolute or relative path to the logfile
         * @param showLog: Wether to print the messages to stdout
         * @param storeLog: Wether to save the messages to the logfile
         * @param prefix: A prefix that comes between the timestamp and the message. ": " is automatically appended to the prefix
         * @param prefixColor: The color of the prefix
         * @param clearLogfileOnRestart: If true, clear the logfile when initializing the log. That means only the log of most recent run is stored
         * @param writeAfterLines: Actually write the log to the logfile after so many lines. Must be at least 1
         *
         * @note Colors will only be shown when written to stdout, not in the logfile.
         */
        Log(std::string logfile="log.log", bool showLog=true, bool storeLog=true, std::string&& prefix="", Color prefixColor=RESET, bool clearLogfileOnRestart=true, unsigned int writeAfterLines=100);

        ~Log();

        /**
         * @brief Logs a message
         * @details Depending on the settings of the log instance, the message will be printed to stdout and/or written to the logfile.
         *  The current date and time is placed before the message.
         *  The message will look like this:
         *  <time>: <prefix>: <message>
         *  where time will be white, prefix in prefixColor and message white.
         * @param args Any number of arguments that satisfy concept Logable
         */
        template<Logable... Args>
        void log(Args&&... args) {
#ifdef LOG_MULTITHREAD 
            mtx.lock();
#endif
            getTime();
            logLines[iter] = time;
            logLines[iter] += prefix;
            vlog(" ", std::forward<Args>(args)...);
            logLines[iter] += "\n";

            std::cout << std::string_view(logLines[iter].c_str(), LOG_TIMESTAMP_CHAR_COUNT - 1) <<
                COLORS[prefixColor] << prefix << COLORS[RESET] << 
                std::string_view(logLines[iter].begin() + prefixLength, logLines[iter].end());
            if (++iter >= writeToFileAfterLines) {
                iter = 0;
                writeLog();
            }
#ifdef LOG_MULTITHREAD 
            mtx.unlock();
#endif
        }

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
         *  <time>: <prefix>: Error: <message>
         *  where time will be white, prefix in prefixColor, Error in red and message white.
         * @param args Any number of arguments that satisfy concept Logable
         */
        template<Logable... Args>
        void error(Args&&... args) {
            clog(RED, "Error", WHITE, std::forward<Args>(args)...);
        }

        /**
         * @brief Log a warnign
         * @details Prints the message with a yellow "Warning: " prefix.
         *  The message will look like this:
         *  <time>: <prefix>: Warning: <message>
         *  where time will be white, prefix in prefixColor, Warning in yellow and message white.
         * @param args Any number of arguments that satisfy concept Logable
         */
        template<Logable... Args>
        void warning(Args&&... args) {
            clog(YELLOW, "Warning", WHITE, std::forward<Args>(args)...);
        }

        /**
         * @brief Log a message in a certain color and with a colored type
         * @details
         *  The message will look like this:
         *  <time>: <prefix>: <type>: <message>
         *  where time will be white, prefix in prefixColor, type in typeColor and message in messageColor
         * @param args Any number of arguments that satisfy concept Logable
         */
        template<Logable... Args>
        void clog(Color typeColor, std::string&& type, Color messageColor, Args&&... args) {
#ifdef LOG_MULTITHREAD 
            mtx.lock();
#endif
            getTime();
            logLines[iter] = std::string(time);
            logLines[iter] += prefix + ": " + type + ": ";
            vlog(" ", std::forward<Args>(args)...);
            logLines[iter] += "\n";

            std::cout << std::string_view(logLines[iter].c_str(), LOG_TIMESTAMP_CHAR_COUNT - 1) <<
                COLORS[prefixColor] << prefix << COLORS[typeColor] << 
                std::string_view(logLines[iter].begin() + prefixLength + LOG_POSTPREFIX_CHAR_COUNT, logLines[iter].begin() + prefixLength + type.size() + 2 * LOG_POSTPREFIX_CHAR_COUNT) <<
                COLORS[messageColor] << std::string_view(logLines[iter].begin() + prefixLength + type.size() + 2 * LOG_POSTPREFIX_CHAR_COUNT, logLines[iter].end()) << COLORS[RESET];
            if (++iter >= writeToFileAfterLines) {
                iter = 0;
                writeLog();
            }
#ifdef LOG_MULTITHREAD 
            mtx.unlock();
#endif
        }

    private:
        // vlog for variadic log
        /// Log anything that can be appendend to std::string
        template<util::Stringy T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args) {
            logLines[iter] += t;
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }
        /// Log anything where toString exists
        template<ConvertibleToString T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args) requires (!util::Stringy<T>) {
            logLines[iter] += toString(t);
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        void vlog(const char* appendChars) {};

    private:
        /// Where the lines are stored
        std::vector<std::string> logLines;
        /// The current position in logLines
        size_t iter = 0;
        /// When iter reaches writeToFileAfterLines, write log to file
        unsigned int writeToFileAfterLines;
        /// Absolute path to the logfile
        std::string logFile;
        bool showLog;
        bool storeLog;
        void writeLog();

        Color prefixColor;
        std::string prefix;
        std::string::size_type prefixLength;

        /// Stores the current time in yyyy-mm-dd hh:mm:ss format
        char time[LOG_TIMESTAMP_CHAR_COUNT];
        /// Store the current time in yyyy-mm-dd hh:mm:ss format in time member
        void getTime();
#ifdef LOG_MULTITHREAD 
        /// Lock for std::cout
        static std::mutex mtx;
#endif
}; // class Log
} // namespace gz

/**
 * @file
 * @brief A logger capable of logging lots of different types and containers to stdout and/or a logfile.
 */
