#include "log.hpp"

#include <filesystem>
#include <fstream>
#include <ctime>

namespace gz {

    namespace fs = std::filesystem;

    const char* COLORS[] = {
        "\033[0m", // RESET
        "\033[30m", // BLACK
        "\033[31m", // RED
        "\033[32m", // GREEN
        "\033[33m", // YELLOW
        "\033[34m", // BLUE
        "\033[35m", // MAGENTA
        "\033[36m", // CYAN
        "\033[37m", // WHITE
        "\033[1;30m", // BBLACK
        "\033[1;31m", // BRED
        "\033[1;32m", // BGREEN
        "\033[1;33m", // BYELLOW
        "\033[1;34m", // BBLUE
        "\033[1;35m", // BMAGENTA
        "\033[1;36m", // BCYAN
        "\033[1;37m", // BWHITE
    };


#ifdef LOG_MULTITHREAD 
    std::mutex Log::mtx;
#endif
    Log::Log(std::string logfile, bool showLog, bool storeLog, std::string&& prefix_, Color prefixColor, bool clearLogfileOnRestart, unsigned int writeAfterLines)
        : showLog(showLog), storeLog(storeLog), prefixColor(prefixColor), prefix(prefix_ + ": "), prefixLength(prefix.size() + LOG_TIMESTAMP_CHAR_COUNT - 1), writeToFileAfterLines(writeAfterLines) {
        // get absolute path to the logfile
        fs::path logpath(logfile);
        if (!logpath.is_absolute()) {
            logpath = fs::current_path() / logpath;
        }
        // create directory of logfile
        if (!fs::is_directory(logpath.parent_path())) {
            fs::create_directory(logpath.parent_path());
        }
        logFile = std::move(logpath.string());

        // if clearLogfileOnRestart, open the file to clear it
        if (clearLogfileOnRestart and fs::is_regular_file(logfile)) {
            std::ofstream file(logFile, std::ofstream::trunc);
            file.close();
        }

        if (writeToFileAfterLines == 0) { writeToFileAfterLines = 1; }
        logLines.resize(writeAfterLines);
        // reserve memory for strings
        if (LOG_RESERVE_STRING_SIZE > 0) {
            for (size_t i = 0; i < logLines.size(); i++) {
                logLines[i].reserve(LOG_RESERVE_STRING_SIZE);
            }
        }

        /* log("Initialising log with settings: logFile: " + logFile + */ 
        /*         ", showLog - " + boolToString(showLog) + ", storeLog - " + boolToString(storeLog)); */
    }


    Log::~Log() {
        if (storeLog) { writeLog(); }
    }


    void Log::getTime() {
        std::time_t t = std::time(0);
        struct std::tm *tmp;
        tmp = std::localtime(&t);
        
        // stores the date and time in time: yyyy-mm-dd hh:mm:ss:
        std::strftime(time, sizeof(time), "%F %T: ", tmp);
    }

    
    void Log::writeLog() {
        std::ofstream file(logFile);
        if (file.is_open()) {
            for (std::string message : logLines) {
                file << message;
            }
            getTime();
            std::string message = time;
            message += "Written log to file: " + logFile + "\n";
            /* file << message; */
            if (showLog) { std::cout << message; }
        }
        else {
            std::cout << COLORS[RED] << "LOG ERROR: " << COLORS[RESET] << "Could not open file '" << logFile << "'." << '\n';
        }
        file.close();
    }
} // namespace gz
