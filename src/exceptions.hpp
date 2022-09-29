#pragma once

#include <exception>
#include <string>

namespace gz {

    /**
     * @brief The parent for all other exceptions
     */
    class Exception : public std::exception {
        public:
            Exception(const std::string& what) : whatStr(what) {};
            Exception(const std::string& what, const std::string& functionName) : whatStr(functionName + ": " + what) {};
            virtual const char* what() const noexcept override { return whatStr.c_str(); };
        private:
            std::string whatStr;
    };

    /**
     * @brief Any error that occurs during file io
     */
    class FileIOError : public Exception {
        public:
            FileIOError(const std::string& what) : Exception(what) {};
            FileIOError(const std::string& what, const std::string& functionName)
                : Exception(what, functionName) {};
    };

    /**
     * @brief Any error that implies an invalid argument was passed to a function
     */
    class InvalidArgument : public Exception {
        public:
            InvalidArgument(const std::string& what) : Exception(what) {};
            InvalidArgument(const std::string& what, const std::string& functionName)
                : Exception(what, functionName) {};
    };

    /**
     * @brief Any error where a wrong type was used
     */
    class InvalidType : public Exception {
        public:
            InvalidType(const std::string& what) : Exception(what) {};
            InvalidType(const std::string& what, const std::string& functionName)
                : Exception(what, functionName) {};
    };


}

/**
 * @file
 * @brief Contains exceptions used in this library
 */
