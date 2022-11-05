#include "log.hpp"

#include <filesystem>
#include <fstream>
#include <ctime>
#include <ios>
#include <memory>

namespace gz {
    namespace fs = std::filesystem;

    const char* COLORS[] = {
        "\033[0m", // RESET
        // normal
        "\033[0;30m", // BLACK
        "\033[0;31m", // RED
        "\033[0;32m", // GREEN
        "\033[0;33m", // YELLOW
        "\033[0;34m", // BLUE
        "\033[0;35m", // MAGENTA
        "\033[0;36m", // CYAN
        "\033[0;37m", // WHITE
        // bold
        "\033[0;1;30m", // BO_BLACK
        "\033[0;1;31m", // BO_RED
        "\033[0;1;32m", // BO_GREEN
        "\033[0;1;33m", // BO_YELLOW
        "\033[0;1;34m", // BO_BLUE
        "\033[0;1;35m", // BO_MAGENTA
        "\033[0;1;36m", // BO_CYAN
        "\033[0;1;37m", // BO_WHITE
        // background
        "\033[0;40m", // BO_BLACK
        "\033[0;41m", // BO_RED
        "\033[0;42m", // BO_GREEN
        "\033[0;30;43m", // BO_YELLOW
        "\033[0;44m", // BO_BLUE
        "\033[0;45m", // BO_MAGENTA
        "\033[0;46m", // BO_CYAN
        "\033[0;47m", // BO_WHITE
        // light
        "\033[0;38;5;9m", // LI_RED
        "\033[0;38;5;10m", // LI_GREEN
        "\033[0;38;5;11m", // LI_YELLOW
        "\033[0;38;5;12m", // LI_BLUE
        "\033[0;38;5;13m", // LI_MAGENTA
        "\033[0;38;5;14m", // LI_CYAN
        "\033[0;38;5;15m", // LI_WHITE
        "\033[0;38;5;169m", // LI_BLACK
    };


#ifdef LOG_MULTITHREAD 
// Static member initialization
    std::mutex Log::mtx;
#endif

    Log::Log()
        : showLog(true), 
            prefixColor(Color::RESET), 
            prefix("")
    {
#ifdef LOG_SUBLOGS
        resources = std::make_shared<LogResources>();
#endif
        iter() = 0;
        writeToFileAfterLines() = 100;
        clearLogfileOnRestart() = false;
        logFile() = "default.log";
        storeLog() = false;
        showTime() = false;
        timeColor() = Color::RESET;

        init();
    }

    Log::Log(LogCreateInfo&& ci)
        : showLog(ci.showLog), 
            prefixColor(ci.prefixColor), 
            prefix(ci.prefix)
    {
#ifdef LOG_SUBLOGS
        resources = std::make_shared<LogResources>();
#endif
        iter() = 0;
        writeToFileAfterLines() = ci.writeAfterLines;
        clearLogfileOnRestart() = ci.clearLogfileOnRestart;
        logFile() = ci.logfile;
        storeLog() = ci.storeLog;
        showTime() = ci.showTime;
        timeColor() = ci.timeColor;

        init();
    }

    
#ifdef LOG_SUBLOGS
    Log Log::createSublog(bool showLog, const std::string& prefix, Color prefixColor) {
        return Log(std::shared_ptr<LogResources>(resources), showLog, prefix, prefixColor);
    }

    Log::Log(std::shared_ptr<LogResources>&& resources_, bool showLog, const std::string& prefix, Color prefixColor)
        : resources(std::move(resources_)), showLog(showLog), prefixColor(prefixColor), prefix(prefix)
    {

    }
#endif


    void Log::init() {
        // get absolute path to the logfile
        fs::path logpath(std::move(logFile()));
        if (!logpath.is_absolute()) {
            logpath = fs::current_path() / logpath;
        }
        // create directory of logfile
        if (!fs::is_directory(logpath.parent_path())) {
            fs::create_directory(logpath.parent_path());
        }
        logFile() = logpath.string();

        // if clearLogfileOnRestart, open the file to clear it
        if (clearLogfileOnRestart() and fs::is_regular_file(logpath)) {
            std::ofstream file(logFile(), std::ofstream::trunc);
            file.close();
        }

        if (writeToFileAfterLines() == 0) { writeToFileAfterLines() = 1; }
        logLines().resize(writeToFileAfterLines());
        // reserve memory for strings
        if (LOG_RESERVE_STRING_SIZE > 0) {
            for (size_t i = 0; i < logLines().size(); i++) {
                logLines()[i].reserve(LOG_RESERVE_STRING_SIZE);
            }
        }

        // reserve memory for argsBegin
        argsBegin().reserve(ARG_COUNT_RESERVE_COUNT);

        if (!prefix.empty()) {
            prefix += ": ";
        }
    }


    Log::~Log() {
        if (storeLog()) { writeLog(); }
    }


    void Log::getTime() {
        std::time_t t = std::time(0);
        struct std::tm *tmp;
        tmp = std::localtime(&t);
        // stores the date and time in time: yyyy-mm-dd hh:mm:ss:
        std::strftime(time(), LOG_TIMESTAMP_CHAR_COUNT, "%F %T: ", tmp);
    }

    
    void Log::writeLog() {
        std::ofstream file(logFile(), std::ios_base::app);
        if (file.is_open()) {
            for (std::string message : logLines()) {
                file << message;
            }
            getTime();
            std::string message = time();
            message += "Written log to file: " + logFile() + "\n";
            /* file << message; */
            if (showLog) { std::cout << message; }
        }
        else {
            std::cout << COLORS[RED] << "LOG ERROR: " << COLORS[RESET] << "Could not open file '" << logFile() << "'." << '\n';
        }
        file.close();
    }
} // namespace gz
