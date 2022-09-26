#pragma once 

#include "string_concepts.hpp"

#include <string>

namespace gz {

/**
 * @name Functions that determine if s is a string representation of a certain type, using regex.
 * @{
 */
    bool isInt(const std::string& s);
    bool isInt(const std::string_view& s);
    bool isUInt(const std::string& s);
    bool isUInt(const std::string_view& s);
    bool isFloat(const std::string& s);
    bool isFloat(const std::string_view& s);
/**
 * @}
 */


/**
 * @name Convert to type or return fallback
 * @todo Use string_views wothout constructing a std::string
 * @{
 */
    int getIntOr(const std::string& s, int fallback=0) noexcept;
    inline int getIntOr(const std::string_view& s, int fallback=0) noexcept { return getIntOr(std::string(s), fallback); }

    unsigned int getUnsignedIntOr(const std::string& s, unsigned int fallback=0) noexcept;
    /* inline unsigned int getUnsignedIntOr(const std::string&& s, unsigned int fallback=0) { return getUnsignedIntOr(s, fallback); } */
    inline unsigned int getUnsignedIntOr(const std::string_view& s, unsigned int fallback=0) noexcept { return getUnsignedIntOr(std::string(s), fallback); }

    double getDoubleOr(const std::string& s, double fallback=0) noexcept;
    /* inline double getDoubleOr(const std::string&& s, double fallback=0) { return getDoubleOr(s, fallback); } */
    inline double getDoubleOr(const std::string_view& s, double fallback=0) noexcept { return getDoubleOr(std::string(s), fallback); }

    float getFloatOr(const std::string& s, float fallback=0) noexcept;
    /* inline float getFloatOr(const std::string&& s, float fallback=0) { return getDoubleOr(s, fallback); } */
    inline float getFloatOr(const std::string_view& s, float fallback=0) noexcept { return getDoubleOr(std::string(s), fallback); }

    bool getBoolOr(const std::string& s, bool fallback=false) noexcept;
    /* inline bool getBoolOr(const std::string&& s, bool fallback=false) { return getBoolOr(s, fallback); } */
    inline bool getBoolOr(const std::string_view& s, bool fallback=false) noexcept { return getBoolOr(std::string(s), fallback); }

    /**
     * @brief Returns the string or fallback if string is empty.
     */
    std::string getStringOr(const std::string& s, const std::string& fallback="none") noexcept;
/**
 * @}
 */
    // TODO: remove?
    /* enum GetVariantType { */
    /*     INT, DOUBLE, STRING, BOOL, */
    /* }; */
    /*
     * @brief Converts the given string to the requested type and puts returns it in a variant
     * @details
     *  Tries to convert the string to the specified type.
     *  If that fails a default value is returned. 
     *  This is either 1 for int or double or "none" for strings.
     *
     * @param value String which should be converted
     * @param type GetVariantType datatype to return in the variant
     *
     * @returns Variant containing the value in the given datatype.
     */
    /* std::variant<std::string, int, double, bool> getVariant(std::string value, GetVariantType type=STRING, bool bFallback=false, int iFallback=0, double dFallback=0, const char* sFallback="none"); */
     
//
// CONVERT TO STRING
//
/**
 * @name Converting a type to string
 * @{
 */
    /**
     * @brief Construct a string from a string like-type
     */
    template<util::Stringy T>
    inline std::string to_string(const T& t) {
        return t;
    }

    /**
     * @overload
     * @brief Construct a string from a type having a to_string() const member function
     */
    template<util::HasToStringMember T>
    inline std::string to_string(const T& t) {
        return t.to_string();
    }

    /**
     * @overload
     * @brief Construct a string from a number
     * @returns std::to_string(t)
     */
    template<util::WorksWithStdToString T>
    inline std::string to_string(const T& t) {
        return std::to_string(t);
    }

    /**
     * @brief Construct a string from a boolean
     * @details
     *  Unlike std::to_string(bool), which returns 0 or 1, this function returns "true" or "false"
     * @returns "true" or "false"
     */
    inline std::string to_string(const bool& b) {
        return b ? "true" : "false";
    }

    /**
     * @overload
     * @brief Construct a string from a forward range
     */
    template<util::ContainerConvertibleToString T>
    std::string to_string(const T& t) {
        std::string s = "[ ";
        for (auto it = t.begin(); it != t.end(); it++) {
            s += to_string(*it) + ", ";
        }
        if (s.size() > 2) {
            s.erase(s.size() - 2);
        }
        s += " ]";
        return s;
    }

    /**
     * @overload
     * @brief Construct a string from a pair
     */
    template<util::PairConvertibleToString T>
    inline std::string to_string(const T& t) {
        return "{ " + to_string(t.first) + ", " + to_string(t.second) + " }";
    }

    /**
     * @overload
     * @brief Construct a string from a forward range holding a pair, eg a map
     */
    template<util::MapConvertibleToString T>
    std::string to_string(const T& t) {
        std::string s = "{ ";
        for (const auto& [k, v] : t) {
            s += to_string(k) + ": ";
            s += to_string(v) + ", ";
        }
        if (s.size() > 2) {
            s.erase(s.size() - 2);
        }
        s += " }";
        return s;
    }

    /**
     * @overload
     * @brief Construct a string from the element the pointer points at
     */
    template<util::PointerConvertibleToString T>
    inline std::string to_string(const T& t) {
        return to_string(*t);        
    }

    /**
     * @overload
     * @brief Construct a string from a vector with x, y members
     */
    template<util::Vector2ConvertibleToString T>
    inline std::string to_string(const T& t) {
        std::string s = "( ";
        s += to_string(t.x) + ", ";
        s += to_string(t.z) + " )";
        return s;
    }

    /**
     * @overload
     * @brief Construct a string from a vector with x, y members
     */
    template<util::Vector3ConvertibleToString T>
    inline std::string to_string(const T& t) {
        std::string s = "( ";
        s += to_string(t.x) + ", ";
        s += to_string(t.y) + ", ";
        s += to_string(t.z) + " )";
        return s;
    }

    /**
     * @overload
     * @brief Construct a string from a vector with x, y, z, w members
     */
    template<util::Vector4ConvertibleToString T>
    inline std::string to_string(const T& t) {
        std::string s = "( ";
        s += to_string(t.x) + ", ";
        s += to_string(t.y) + ", ";
        s += to_string(t.z) + ", ";
        s += to_string(t.w) + " )";
        return s;
    }
/**
* @}
*/

//
// CONVERT FROM STRING
//
/**
 * @name Construct a type from a string
 * @note 
 *  The from_string()functions (except for the bool one) simply return std::stoXX. These can throw std::invalid_argument and std::out_of_range.
 *  See https://en.cppreference.com/w/cpp/string/basic_string/stol
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

    template<GetTypeFromStringImplemented T>
    T from_string(const std::string& s);

    /// @returns std::stoi(s)
    template<> inline int from_string<int>(const std::string& s) {
        return std::stoi(s);
    }
    /// @returns std::stol(s)
    template<> inline long from_string<long>(const std::string& s) {
        return std::stol(s);
    }
    /// @returns std::stoll(s)
    template<> inline long long from_string<long long>(const std::string& s) {
        return std::stoll(s);
    }
    /// @returns std::stoul(s)
    template<> inline unsigned int from_string<unsigned int>(const std::string& s) {
        return std::stoul(s);
    }
    /// @returns std::stoul(s)
    template<> inline unsigned long from_string<unsigned long>(const std::string& s) {
        return std::stoul(s);
    }
    /// @returns std::stoull(s)
    template<> inline unsigned long long from_string<unsigned long long>(const std::string& s) {
        return std::stoull(s);
    }
    /// @returns std::stof(s)
    template<> inline float from_string<float>(const std::string& s) {
        return std::stof(s);
    }
    /// @returns std::stod(s)
    template<> inline double from_string<double>(const std::string& s) {
        return std::stod(s);
    }
    /// @returns std::stold(s)
    template<> inline long double from_string<long double>(const std::string& s) {
        return std::stold(s);
    }
    /**
     * @brief Convert a string to bool
     * @details
     *  - returns true if s = "true" or "True" or "1"
     *  - returns false if s = "false" or "False" or "0"
     *  - throws InvalidArgument otherwise
     */
    template<> bool from_string<bool>(const std::string& s);
/**
* @}
*/


//
// CONCEPTS
//
    /**
     * @brief Any type where to_string(t) const exists returns a string-like type
     * @note The function only has to exist, it does not have to be noexcept!
     */  
    template<typename T>
    concept ConvertibleToString = requires(const T& t) { { to_string(t) } -> util::Stringy; };
    /* concept CovertibleToString = requires(const T& t) { { to_string(t) }; }; */

    /**
     * @brief Any type where from_string(string) exists and returns T
     * @note The function only has to exist, it does not have to be noexcept!
     */  
    template<typename T>
    concept ConstructibleFromString = requires(const std::string& s) {
        { from_string<T>(s) } -> std::same_as<T>;
    };

    /**
     * @brief Any type where to_string(t) and from_string(string) exist
     */  
    template<typename T>
    concept StringConvertible = ConvertibleToString<T> and ConstructibleFromString<T>;

} // namespace gz

/**
 * @file
 * @brief Contains utilities for type conversions from string
 */

namespace gz {
/**
 * @page string_conversion String conversion
 * @section sc_about About
 *  This library provides utility for string conversion, from and to std::string.
 *
 *  There also three important concepts, ConvertibleToString, ConstructibleFromString and @ref StringConvertible which are
 *  used in the @ref Log "logger" and the @ref SettingsManager "settings manager" to log and store types.
 *
 *  If you want to use your own data type with one of these, 
 *  you can easily @ref sc_overloads "write your own string conversion" function for your custom datatype.
 *  
 * @section sc_to_string Convert to string
 *  You can use the to_string() function to turn certain types into strings.
 *  Concepts are used to determine the correct overload of the function.
 *
 *  The concept ConvertibleToString is satisfied for types that can be converted to string 
 *  using to_string().
 *  
 * @section sc_from_string Construct from string
 *  You can use the from_string() function to create certain types from a string.
 *
 *  The concept ConstructibleFromString is satisfied for types that can be constructed from a string with from_string().
 *
 *  When constructing something from a string, there is of course the problem that errors occur at runtime when
 *  the string is unsuitable for construction. In this case, the from_string functions from this library throw a InvalidArgument exception.
 *
 * @section sc_overloads Overloading the string conversion functions
 *  @subsection sc_to_string_ov Overload for to_string
 *   If you want your custom type to be convertible to string, you have different options.
 *   You can either add an <code>to_string() const</code> member to your class or overload 
 *   <code>std::string to_string(const T&)</code>.
 *   Example for a class called <code>Custom</code>
 *   @code
 *    std::string to_string(const Custom& c) {
 *        std::string s;
 *        ...
 *        return s;
 *    }
 *   @endcode
 *   To satisfy the concept, this overload has of course to visible by the compiler,
 *   so you have to at least declare it in a header file.
 *    

 *  @subsection sc_from_string_ov Overload for from_string
 *   Writing an overload for from_string needs a little bit more boiler plate.
 *   Since from_string is a templated function, you need to declare it as such.
 *   The function declaration in this library uses a concept so that it is only
 *   declared for the types that are actully implemented.
 *   Example for a class called <code>Custom</code>
 *   @code
 *    // declare as template, but only for Custom
 *    template<std::same_as<Custom> T>
 *    Custom from_string(const std::string& s);
 *
 *    // instantiation/definition, but only for Custom
 *    template<>
 *    Custom from_string<Custom>(const std::string& s) {
 *        ... 
 *        return Custom(...);
 *     };
 *   @endcode
 *
 *  @subsection sc_notes Notes 
 *   You should write your function so that the output of one can be used as input of the other.
 *   In other words:
 *   @code
 *    Custom c1;
 *    Custom c2 = from_string(to_string(c1));
 *    assert(c1 == c2);
 *   @endcode
 *
 *   SettingsManager expects the strings from to_string() to be a single line.
 *   If it has multiple lines, it will not load it correctly when loading from a file.
 *
 *  @todo Implement from_string for vectors that hold ConstructibleFromString types
 *  @todo Make from_string throw InvalidArgument, write docs
 *  @todo Make macro for all types/concepts where someone would want to implement from_string and to_string explicitly, eg vectors
 */
} // namespace gz
