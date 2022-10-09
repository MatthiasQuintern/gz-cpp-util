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
     * @brief Return the string
     */
    template<util::Stringy T>
    inline std::string toString(const T& t) {
        return static_cast<std::string>(t);
    }

    /**
     * @brief Construct a string from a string like-type
     */
    template<util::CanConstructString T>
    inline std::string toString(const T& t) {
        return std::string(t);
    }

    /**
     * @overload
     * @brief Construct a string from a type having a toString() const member function
     */
    template<util::HasToStringMember T>
    inline std::string toString(const T& t) {
        return t.toString();
    }

    /**
     * @overload
     * @brief Construct a string from a number
     * @returns std::to_string(t)
     */
    template<util::WorksWithStdToString T>
    inline std::string toString(const T& t) {
        return std::to_string(t);
    }

    /**
     * @brief Construct a string from a boolean
     * @details
     *  Unlike std::to_string(bool), which returns 0 or 1, this function returns "true" or "false"
     * @returns "true" or "false"
     */
    inline std::string toString(const bool& b) {
        return b ? "true" : "false";
    }

    /**
     * @overload
     * @brief Construct a string from a forward range
     */
    template<util::ContainerConvertibleToString T>
    std::string toString(const T& t) {
        std::string s = "[ ";
        for (auto it = t.begin(); it != t.end(); it++) {
            s += toString(*it) + ", ";
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
    inline std::string toString(const T& t) {
        return "{ " + toString(t.first) + ", " + toString(t.second) + " }";
    }

    /**
     * @overload
     * @brief Construct a string from a forward range holding a pair, eg a map
     */
    template<util::MapConvertibleToString T>
    std::string toString(const T& t) {
        std::string s = "{ ";
        for (const auto& [k, v] : t) {
            s += toString(k) + ": ";
            s += toString(v) + ", ";
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
    inline std::string toString(const T& t) {
        return toString(*t);        
    }

    /**
     * @overload
     * @brief Construct a string from a vector with x, y members
     */
    template<util::Vector2ConvertibleToString T>
    inline std::string toString(const T& t) {
        std::string s = "( ";
        s += toString(t.x) + ", ";
        s += toString(t.y) + " )";
        return s;
    }

    /**
     * @overload
     * @brief Construct a string from a vector with x, y members
     */
    template<util::Vector3ConvertibleToString T>
    inline std::string toString(const T& t) {
        std::string s = "( ";
        s += toString(t.x) + ", ";
        s += toString(t.y) + ", ";
        s += toString(t.z) + " )";
        return s;
    }

    /**
     * @overload
     * @brief Construct a string from a vector with x, y, z, w members
     */
    template<util::Vector4ConvertibleToString T>
    inline std::string toString(const T& t) {
        std::string s = "( ";
        s += toString(t.x) + ", ";
        s += toString(t.y) + ", ";
        s += toString(t.z) + ", ";
        s += toString(t.w) + " )";
        return s;
    }

    /**
     * @overload
     * @brief Construct a string from a type that has toString declared in global namespace
     */
    template<util::ConvertibleToStringGlobal T>
    inline std::string toString(const T& t) {
        return ::toString(t);
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
 *  The fromString()functions (except for the bool one) simply return std::stoXX. These can throw std::invalid_argument and std::out_of_range.
 *  See https://en.cppreference.com/w/cpp/string/basic_string/stol
 */

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
/**
* @}
*/

//
// CONCEPTS
//
    /**
     * @brief Any type where toString(t) const exists returns a string-like type
     * @note The function only has to exist, it does not have to be noexcept!
     */  
    template<typename T>
    concept ConvertibleToString = requires(const T& t) { 
        { toString(t) } -> util::Stringy; 
    };
    /* concept CovertibleToString = requires(const T& t) { { toString(t) }; }; */

    /**
     * @brief Any type where fromString(string) exists and returns T
     * @note The function only has to exist, it does not have to be noexcept!
     */  
    template<typename T>
    concept ConstructibleFromString = requires(const std::string& s) {
        { fromString<T>(s) } -> std::same_as<T>;
    };

    /**
     * @brief Any type where toString(t) and fromString(string) exist
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
 * @section sc_toString Convert to string
 *  You can use the toString() function to turn certain types into strings.
 *  Concepts are used to determine the correct overload of the function.
 *
 *  The concept ConvertibleToString is satisfied for types that can be converted to string 
 *  using toString().
 *  
 * @section sc_fromString Construct from string
 *  You can use the fromString() function to create certain types from a string.
 *
 *  The concept ConstructibleFromString is satisfied for types that can be constructed from a string with fromString().
 *
 *  When constructing something from a string, there is of course the problem that errors occur at runtime when
 *  the string is unsuitable for construction. In this case, the fromString functions from this library throw a InvalidArgument exception.
 *
 * @section sc_overloads Overloading the string conversion functions
 *  @subsection sc_toString_ov Overload for toString
 *   If you want your custom type to be convertible to string, you have different options.
 *   You can either add an <code>toString() const</code> member to your class or overload 
 *   <code>std::string toString(const T&)</code>.
 *   Example for a class called <code>Custom</code>
 *   @code
 *    std::string toString(const Custom& c) {
 *        std::string s;
 *        ...
 *        return s;
 *    }
 *   @endcode
 *   To satisfy the concept, this overload has of course to visible by the compiler,
 *   so you have to at least declare it in a header file.
 *    

 *  @subsection sc_fromString_ov Overload for fromString
 *   Writing an overload for fromString needs a little bit more boiler plate.
 *   Since fromString is a templated function, you need to declare it as such.
 *   The function declaration in this library uses a concept so that it is only
 *   declared for the types that are actully implemented.
 *   Example for a class called <code>Custom</code>
 *   @code
 *    // declare as template, but only for Custom
 *    template<std::same_as<Custom> T>
 *    Custom fromString(const std::string& s);
 *
 *    // instantiation/definition, but only for Custom
 *    template<>
 *    Custom fromString<Custom>(const std::string& s) {
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
 *    Custom c2 = fromString(toString(c1));
 *    assert(c1 == c2);
 *   @endcode
 *
 *   SettingsManager expects the strings from toString() to be a single line.
 *   If it has multiple lines, it will not load it correctly when loading from a file.
 *
 *  @todo Implement fromString for vectors that hold ConstructibleFromString types
 *  @todo Make fromString throw InvalidArgument, write docs
 *  @todo Make macro for all types/concepts where someone would want to implement fromString and toString explicitly, eg vectors
 */
} // namespace gz
