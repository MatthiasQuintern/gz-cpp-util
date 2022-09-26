#include "string.hpp"

#include <sstream>


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

} // namespace gz::util
