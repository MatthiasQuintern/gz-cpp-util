#pragma once

#include "util/string.hpp"
#include "util/string_conversion.hpp"


namespace gz {

    /**
     * @brief Write a file that contains key = value pairs
     * @details
     *  This template function is instantiated for the default unordered_map<string, string> and the util::string_map from util/string.hpp
     * @throws FileIOError
     */
    template<typename Hash, typename Pred>
    bool writeKeyValueFile(const std::string& filepath, const std::unordered_map<std::string, std::string, Hash, Pred>& content);

    /**
     * @brief Read a file that contains key = value pairs
     * @throws FileIOError
     */
    std::unordered_map<std::string, std::string> readKeyValueFile(const std::string& filepath, bool removeSpaces=false);

}
