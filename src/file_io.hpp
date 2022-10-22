#pragma once

#include "util/string_conversion.hpp"

#include <map>
#include <unordered_map>
#include <vector>


namespace gz {

    /**
     * @brief Write a file that contains key = value pairs
     * @details
     *  This template function is instantiated for the default unordered_map<string, string> and the util::string_map from util/string.hpp
     * @throws FileIOError
     * @see @ref fio_t_key_value "Key-Value filetype"
     */
    template<typename Hash, typename Pred>
    bool writeKeyValueFile(const std::string& filepath, const std::unordered_map<std::string, std::string, Hash, Pred>& content);

    template<typename T>
    concept ReadKeyValueFileImplemented = 
        std::same_as<T, std::vector<std::pair<std::string, std::string>>> ||
        std::same_as<T, std::map<std::string, std::string>> ||
        std::same_as<T, std::unordered_map<std::string, std::string>> ;

    /**
     * @brief Read a file that contains key = value pairs
     * @throws FileIOError
     * @see @ref fio_t_key_value "Key-Value filetype"
     */
    template<ReadKeyValueFileImplemented T>
    T readKeyValueFile(const std::string& filepath, bool removeSpaces=false);
}

/**
 * @file
 * @brief Contains file reading/writing utility
 */
/**
 * @page FileIO
 * @section fio_filetypes Filetypes
 *  @subsection fio_t_key_value Simple Key-Value file
 *   A file that contains key - value pairs in each line, separated with "=".
 *   Whitespaces around the separator are allowed.
 *   If the first character of a line is "#", the whole line is a comment.
 *   Example:
 *   @code
 *    key1 = value1
 *    # this is a comment
 *    key2=  #this_is_value_not_a_comment
 *    arr = val1, val2, val3
 *   @endcode
 */
