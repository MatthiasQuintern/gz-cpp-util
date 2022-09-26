#include "string_conversion.hpp"
#include "../exceptions.hpp"
#include "regex.hpp"


namespace gz {

bool isInt(const std::string& s) {
    return std::regex_match(s, re::types::intT);
}
bool isInt(const std::string_view& s) {
    return re::regex_match(s, re::types::intT);
}
bool isUInt(const std::string& s) {
    return std::regex_match(s, re::types::uintT);
}
bool isUInt(const std::string_view& s) {
    return re::regex_match(s, re::types::uintT);
}
bool isFloal(const std::string& s) {
    return std::regex_match(s, re::types::floatT);
}
bool isFloat(const std::string_view& s) {
    return re::regex_match(s, re::types::floatT);
}


int getIntOr(const std::string& s, int fallback) noexcept {
    try {
        fallback = std::stoi(s);
    }
    catch (...) {}
    return fallback;
}


unsigned int getUnsignedIntOr(const std::string& s, unsigned int fallback) noexcept {
    try {
        fallback = std::stoul(s);
    }
    catch (...) {}
    return fallback;
}


double getDoubleOr(const std::string& s, double fallback) noexcept {
    try {
        fallback = std::stod(s);
    }
    catch (...) {}
    return fallback;
}


float getFloatOr(const std::string& s, float fallback) noexcept {
    try {
        fallback = std::stof(s);
    }
    catch (...) {}
    return fallback;
}


bool getBoolOr(const std::string& s, bool fallback) noexcept {
    if (s == "true" or s == "True" or s == "1") {
        fallback = true;
    }
    else if (s == "false" or s == "False" or s == "0") {
        fallback = false;
    }
    return fallback;
}


std::string getStringOr(const std::string& s, const std::string& fallback) noexcept {
    if (s == "") { return fallback; }
    else { return s; }
}


// TODO: remove?
/* // int = 0, double = 1, string = 2 */
/* std::variant<std::string, int, double, bool> getVariant(std::string value, GetVariantType type, bool bFallback, int iFallback, double dFallback, const char* sFallback) { */
/*     std::variant<std::string, int, double, bool> val = value; */
/*     /1* cout << "id-attr" << id << attr << "val: " << std::get<string>(val); *1/ */
/*     switch (type) { */
/*         // to integer */
/*         case INT: */
/*             val = getIntOr(value, iFallback); */
/*             break; */
/*         case DOUBLE: */
/*             val = getDoubleOr(value, dFallback); */
/*             break; */
/*         case BOOL: */
/*             val = getBoolOr(value, bFallback); */
/*             break; */
/*         case STRING: */
/*             val = getStringOr(value, sFallback); */
/*             break; */
/*     } */
/*     return val; */
/* } */

//
// CONVERT FROM STRING
//
template<>
bool from_string<bool>(const std::string& s) { 
    if (s == "true" or s == "True" or s == "1") {
        return true;
    }
    else if (s == "false" or s == "False" or s == "0") {
        return false;
    }
    throw InvalidArgument("s is not a bool: '" + s + "'", "from_string<bool>");
}


} // namespace gz
