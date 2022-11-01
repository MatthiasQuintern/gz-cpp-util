#include "utility.hpp"

#include <sstream>
#include <iostream>


namespace gz::util {

std::vector<std::string> splitStringInVector(std::string& s, char separator) {
    // remove linebreaks from the end
    if (*(s.end()) == '\n') { s.erase(s.end()); }

    /* std::unique_ptr<std::unordered_map<Entity, std::string>> params (new std::unordered_map<Entity, std::string>); */
    std::vector<std::string> v;
    std::stringstream ss(s);
    std::string temp;

    while (std::getline(ss, temp, separator)) {
        // if has "=": store latter part in vector
        if (temp.find("=") != std::string::npos) {
            int eqPos = temp.find("=");
            v.emplace_back(temp.substr(eqPos + 1, temp.length()));
        }
        else {
            v.emplace_back(temp);
        }
    }
    return v;
}


template<SplitStringInVectorImplemented T>
std::vector<T> splitStringInVector(const std::string_view& s, const std::string& separator, bool skipEmptyStrings) {
    std::vector<T> v;

    std::string::size_type posStart = 0;
    std::string::size_type posEnd = s.find(separator, posStart);
    while (posEnd != std::string::npos) {
        if (!(skipEmptyStrings and posStart == posEnd)) {
            v.emplace_back(T(s.begin() + posStart, s.begin() + posEnd));
        }
        posStart = posEnd + 1;
        posEnd = s.find(separator, posStart);
    }
    // last element
    if (posStart < s.size()) {
        v.emplace_back(T(s.begin() + posStart, s.end()));
    }
    // if last char is separator, append empty string 
    else if (!skipEmptyStrings and posStart == s.size()) {
        v.emplace_back(T(s.begin(), s.begin()));
    }
    return v;
}

template std::vector<std::string_view> splitStringInVector<std::string_view>(const std::string_view&, const std::string&, bool);
template std::vector<std::string> splitStringInVector<std::string>(const std::string_view&, const std::string&, bool);

} // namespace gz::util
