#include "util.hpp"

#include "gz_regex.hpp"

namespace gz::util {
//
// Type Conversion
//
bool isInt(std::string& s) {
    return std::regex_match(s, re::types::intT);
}
bool isInt(std::string_view& s) {
    return re::regex_match(s, re::types::intT);
}
int getInt(std::string& s, int fallback) {
    try {
        fallback = std::stoi(s);
    }
    catch (std::invalid_argument& e) {}
    return fallback;
}


bool isUInt(std::string& s) {
    return std::regex_match(s, re::types::uintT);
}
bool isUInt(std::string_view& s) {
    return re::regex_match(s, re::types::uintT);
}
unsigned int getUnsignedInt(std::string& s, unsigned int fallback) {
    try {
        fallback = std::stoul(s);
    }
    catch (std::invalid_argument& e) {}
    return fallback;
}


double getDouble(std::string& s, double fallback) {
    try {
        fallback = std::stod(s);
    }
    catch (std::invalid_argument& e) {}
    return fallback;
}


bool isFloal(std::string& s) {
    return std::regex_match(s, re::types::floatT);
}
bool isFloat(std::string_view& s) {
    return re::regex_match(s, re::types::floatT);
}
float getFloat(std::string& s, float fallback) {
    try {
        fallback = std::stof(s);
    }
    catch (std::invalid_argument& e) {}
    return fallback;
}



bool getBool(std::string& s, bool fallback) {
    if (s == "true" or s == "True" or s == "1") {
        fallback = true;
    }
    return fallback;
}


std::string getString(std::string s, std::string fallback) {
    if (s == "") { return fallback; }
    else { return s; }
}


// int = 0, double = 1, string = 2
std::variant<std::string, int, double, bool> getVariant(std::string value, Type type, bool bFallback, int iFallback, double dFallback, const char* sFallback) {
    std::variant<std::string, int, double, bool> val = value;
    /* cout << "id-attr" << id << attr << "val: " << std::get<string>(val); */
    switch (type) {
        // to integer
        case INT:
            val = getInt(value, iFallback);
            break;
        case DOUBLE:
            val = getDouble(value, dFallback);
            break;
        case BOOL:
            val = getBool(value, bFallback);
            break;
        default:
            val = getString(value, sFallback);
            break;
    }
    return val;
}



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
