#pragma once

#include <regex>
#include <string_view>

namespace gz::re {
    struct types {
        /// convertible with std::stoi
        static const std::regex intT;
        /// convertible with std::stoul
        static const std::regex uintT;
        /// convertible with std::stof
        static const std::regex floatT;
    };


    /**
     * @name Regex compability with std::string_view
     */
    /// @{
    using svmatch = std::match_results<std::string_view::const_iterator>;
    using svsub_match = std::sub_match<std::string_view::const_iterator>;

    inline std::string_view get_sv(const svsub_match& m) {
        return std::string_view(m.first, m.length());
    }
    /// @details Code taken from u/deleted :) https://www.reddit.com/r/cpp/comments/aqt7a0/status_of_string_view_and_regex/
    inline bool regex_match(std::string_view sv, svmatch& m, const std::regex& e, std::regex_constants::match_flag_type flags=std::regex_constants::match_default) {
        return std::regex_match(sv.begin(), sv.end(), m, e, flags);
    }
    /// @details Code taken from u/deleted :) https://www.reddit.com/r/cpp/comments/aqt7a0/status_of_string_view_and_regex/
    inline bool regex_match(std::string_view sv, const std::regex& e, std::regex_constants::match_flag_type flags = std::regex_constants::match_default) {
        return std::regex_match(sv.begin(), sv.end(), e, flags);
    }

    inline bool regex_search(std::string_view sv, svmatch& m, const std::regex& e, std::regex_constants::match_flag_type flags=std::regex_constants::match_default) {
        return std::regex_search(sv.begin(), sv.end(), m, e, flags);
    }
    inline bool regex_search(std::string_view sv, const std::regex& e, std::regex_constants::match_flag_type flags = std::regex_constants::match_default) {
        return std::regex_search(sv.begin(), sv.end(), e, flags);
    }
    /// @}
}


/**
 * @file
 * @brief Utility for using regex with std::string_view and some regular expressions
 */
