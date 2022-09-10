#pragma once

#define LOG_MULTITHREAD

#include <iostream>
#include <string>
#include <concepts>
#include <ranges>
#include <unordered_map>
#include <vector>

#ifdef LOG_MULTITHREAD 
#include <mutex>
#endif

namespace gz {

    /// Reserve a string size for each string in logArray. Set to 0 if you do not want to reserve memory for strings.
    constexpr unsigned int LOG_RESERVE_STRING_SIZE = 100;

    constexpr unsigned int LOG_TIMESTAMP_CHAR_COUNT = 22;
    constexpr unsigned int LOG_POSTPREFIX_CHAR_COUNT = 2;


    inline const char* boolToString(bool b) {
        return b ? "true" : "false";
    }

    //
    // CONCEPTS
    //
    /// is appendable to std::string
    template<typename T> 
    /* concept Stringy = std::same_as<T, std::string> || std::convertible_to<T, std::string_view>; */
    concept Stringy = requires(T t, std::string s) { s += t; };

    /// has .to_string() member
    template<typename T>
    concept HasToString = !Stringy<T> && requires(T t) { { t.to_string() }-> Stringy; };
    
    /// an overload of Stringy to_string(const T&) exists in global or gz namespace
    template<typename T>
    concept ExistsToString = !Stringy<T> && !HasToString<T> && requires(const T& t) { { to_string(t) } -> Stringy; };

    /// works with std::to_string(), except bool
    template<typename T>
    concept WorksWithStdToString = !std::same_as<T, bool> && !Stringy<T> && !HasToString<T> && !ExistsToString<T> && requires(T t) { { std::to_string(t) } -> Stringy; };

    /// string-like, has .to_string() member, to_string(const T&) exits, works with std::to_string() or bool
    template<typename T>
    concept PrintableNoPtr = Stringy<T> || HasToString<T> || ExistsToString<T> || WorksWithStdToString<T> || std::same_as<T, bool>;

    /// Everything from PrintableNoPtr but "behind" a pointer
    template<typename T>
    concept Printable = PrintableNoPtr<T> || requires(T t) { { *(t.get()) } ->  PrintableNoPtr; };

    /// Type having printable .x and .y members
    template<typename T>
    concept Vector2Printable = !Printable<T> && 
        requires(T t) { { t.x } -> Printable; { t.y } -> Printable; };

    /// Pair having printable elements
    template<typename T>
    concept PairPrintable = !Vector2Printable<T> && !Printable<T> && 
        requires(T p) { { p.first } -> Printable; } &&  (requires(T p){ { p.second } -> Printable; } ||  requires(T p){ { p.second } -> Vector2Printable; }); 

    /// Container having printable elements
    template<typename T>
    concept ContainerPrintable = !Printable<T> && !Vector2Printable<T> &&  !PairPrintable<T> &&
        std::ranges::forward_range<T> && (Printable<std::ranges::range_reference_t<T>> || Vector2Printable<std::ranges::range_reference_t<T>>); 

    /// Container having printable pairs
    template<typename T>
    concept MapPrintable = !Printable<T> && !Vector2Printable<T> && !ContainerPrintable<T> &&
        std::ranges::forward_range<T> && PairPrintable<std::ranges::range_reference_t<T>>;

    template<typename T>
    concept LogableNotPointer = Printable<T> || Vector2Printable<T> || PairPrintable<T> || ContainerPrintable<T> || MapPrintable<T>;

    template<typename T> 
    concept LogableSmartPointer = requires(T t) { { *(t.get()) } ->  LogableNotPointer; };


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
     *  -# Any @ref Stringy "string-like type": eg. std::string, std::string_view 
     *  -# Any @ref WorksWithStdToString "type that works with std::to_string()"
     *  -# Any @ref ExistsToString "type for which an overload of" <code>Stringy to_string(const T&)</code> exists in global or gz namespace
     *  -# Any @ref HasToString "type that has a to_string() const member that returns a string"
     *  -# Any @ref Vector2Printable "type with t.x and t.y", provided t.x and t.y satisfy one of 1-3
     *  -# Any @ref PairPrintable "type with t.first, t.second" provided t.first satisfies one of 1-3 and t.second satisfies 1-4
     *  -# Any @ref ContainerPrintable "type that has a forward_iterator" which references any one of 1-5
     *
     *  The higher number takes precedence in overload resolution for the log function.
     *
     *  1-7 include for example:
     *  - int, float, bool...
     *  - std::vector<std::string>, std::list<unsigned int>
     *  - std::map<A, vec2<float>> if A.to_string() returns a string
     *  - ...
     */
    template<typename T>
    concept Logable = LogableNotPointer<T> || LogableSmartPointer<T>;

/**
 * @brief Manages printing messages to stdout and to logfiles.
 * @details
 *  @subsection log_concepts Logable types
 *   Log uses concepts to determine if a type is logable and how it should be logged. See the documentation for concept Logable for more details.
 *   
 *   If you want your custom data type to be logable, it easiest to provide a member function with this signature:
 *   @code
 *          public:
 *              std::string to_string() const;
 *   @endcode
 *   Alternatively, or if the type is not a class overload <code> std::string to_string(const T& t) </code> in global or gz namespace.
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
            logLines[iter] = getTime();
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
            logLines[iter] = time;
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
        template<Stringy T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args) {
            logLines[iter] += t;
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        /// Log anything that has a to_string() member
        template<HasToString T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args) {
            logLines[iter] += t.to_string();
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        /// Log anything where to_string(const T&) -> Stringy
        template<ExistsToString T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args) {
            logLines[iter] += to_string(t);
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        /// Log anything that works with std::to_string()
        template<WorksWithStdToString T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args) {
            logLines[iter] += std::to_string(t);
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        /// Log bool
        template<typename T, Logable... Args> 
            requires(std::same_as<T, bool>)
        void vlog(const char* appendChars, T&& b,  Args&&... args) {
            logLines[iter] += boolToString(b);
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        /// Log vec2
        template<Vector2Printable V,  Logable... Args>
        void vlog(const char* appendChars, V&& v,  Args&&... args) {
            logLines[iter] += "(";
            vlog("", v.x);
            logLines[iter] += ", ";
            vlog("", v.y);
            logLines[iter] += ")";
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        /// Log a pair
        template<PairPrintable P,  Logable... Args>
        void vlog(const char* appendChars, P&& p,  Args&&... args) {
            logLines[iter] += "(";
            vlog("", p.first);
            logLines[iter] += ", ";
            vlog("" ,p.second);
            logLines[iter] += ")";
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        /// Log a container using iterators
        template<ContainerPrintable T, Logable... Args>
        void vlog(const char* appendChars, T&& t,  Args&&... args) {;
            logLines[iter] += "[";
            for (auto it = t.begin(); it != t.end(); it++) {
                vlog(", ", *it); 
            }
            logLines[iter] += "]";
            logLines[iter] += appendChars;
            vlog(" ", std::forward< Args>(args)...);
        }

        /// Log a container containing a pair
        template<MapPrintable T, Logable... Args>
        void vlog(const char* appendChars, T&& t, Args&&... args) {
            logLines[iter] += "{";
            for (const auto& [k, v] : t) {
                vlog(": ", k);
                vlog(", ", v);
            }
            logLines[iter] += "}";
            logLines[iter] += appendChars;
            vlog(" ", std::forward<Args>(args)...);
        }

        /// Log any logable element that is stored in a pointer
        template<LogableSmartPointer T, Logable... Args>
        void vlog(const char* appendChars, T&& t, Args&&... args) {
            vlog("", *t);
            vlog(" ", std::forward<Args>(args)...);
        }

        void vlog(const char* appendChars) {};

    private:
        /// Where the lines are stored
        std::vector<std::string> logLines;
        /// The current position in logLines
        size_t iter;
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
