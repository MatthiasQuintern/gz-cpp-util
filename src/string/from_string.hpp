#pragma once

#include "../concepts.hpp"
#include <string>

#define GZ_UTIL_STRING_CONCEPTS

/**
 * @brief Declaration of fromString in global namespace, so that concepts can use it
 * @details
 *  This declaration only exists so that ::fromString can be used in concepts.
 */
template<gz::util::False T>
T fromString(const std::string& s);

namespace gz::util {
    template<typename T>
    concept ConstructibleFromStringGlobal = requires(const std::string& s) {
        { ::fromString<T>(s) } -> std::same_as<T>;
    };

    /**
     * @brief toString is implemented for these types
     */
    template<typename T>
    concept GetTypeFromStringImplemented = 
        std::same_as<T, int> or
        std::same_as<T, long> or
        std::same_as<T, long long> or
        std::same_as<T, unsigned int> or
        std::same_as<T, unsigned long> or
        std::same_as<T, unsigned long long> or
        std::same_as<T, float> or
        std::same_as<T, double> or
        std::same_as<T, long double> or
        std::same_as<T, bool>;
}  // namespace gz::util

namespace gz {
    /**
     * @name Construct a type from a string
     * @note 
     *  The fromString() functions (except for the bool one) simply return std::stoXX. These can throw std::invalid_argument and std::out_of_range.
     *  See https://en.cppreference.com/w/cpp/string/basic_string/stol
     */
    /// @{
        /**
         * @brief Declaration of fromString, but only for the types for which it is implemented
         */
        template<util::GetTypeFromStringImplemented T>
        T fromString(const std::string& s);

        /// @returns std::stoi(s)
        template<> inline int fromString<int>(const std::string& s) {
            return std::stoi(s);
        }
        /// @returns std::stol(s)
        template<> inline long fromString<long>(const std::string& s) {
            return std::stol(s);
        }
        /// @returns std::stoll(s)
        template<> inline long long fromString<long long>(const std::string& s) {
            return std::stoll(s);
        }
        /// @returns std::stoul(s)
        template<> inline unsigned int fromString<unsigned int>(const std::string& s) {
            return std::stoul(s);
        }
        /// @returns std::stoul(s)
        template<> inline unsigned long fromString<unsigned long>(const std::string& s) {
            return std::stoul(s);
        }
        /// @returns std::stoull(s)
        template<> inline unsigned long long fromString<unsigned long long>(const std::string& s) {
            return std::stoull(s);
        }
        /// @returns std::stof(s)
        template<> inline float fromString<float>(const std::string& s) {
            return std::stof(s);
        }
        /// @returns std::stod(s)
        template<> inline double fromString<double>(const std::string& s) {
            return std::stod(s);
        }
        /// @returns std::stold(s)
        template<> inline long double fromString<long double>(const std::string& s) {
            return std::stold(s);
        }
        /**
         * @brief Convert a string to bool
         * @details
         *  - returns true if s = "true" or "True" or "1"
         *  - returns false if s = "false" or "False" or "0"
         *  - throws InvalidArgument otherwise
         */
        template<> bool fromString<bool>(const std::string& s);

        /**
         * @overload
         * @brief Construct T from a string using a fromString that is declared in global namespace
         */
        template<util::ConstructibleFromStringGlobal T>
        inline T fromString(const std::string& s) {
            return ::fromString<T>(s);
        }
    /// @}


    /**
     * @brief Any type where fromString(string) exists and returns T
     * @note The function only has to exist, it does not have to be noexcept!
     */  
    template<typename T>
    concept ConstructibleFromString = requires(const std::string& s) {
        { fromString<T>(s) } -> std::same_as<T>;
    };
}  // namespace gz

/**
 * @file
 * @brief Contains functions to construct types from string
 * @todo Make these functions usable with std::string_view
 */
