#pragma once 

#include "to_string.hpp"
#include "from_string.hpp"

#include <string>
#include <bitset>

#ifdef FORMAT 
#include <format>
#else
#include <sstream>
#include <iomanip>
#endif

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
     * @todo Use string_views without constructing a std::string
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
    /// @}
     
    //
    // HEX/OCT
    //
    /**
     * @name Converting an integer to/from a hex/oct/bin string
     * @todo Move to std::format, when P0645R10 is implemented in gcc libstd
     * @note 
     *  The fromHexString() and fromOctString() functions use `std::hex`, while fromBinString() uses `std::bitset`. Both can throw `std::invalid_argument` and the latter can also throw `std::out_of_range`.
     *  See https://en.cppreference.com/w/cpp/utility/bitset/bitset and https://en.cppreference.com/w/cpp/io/manip/hex
     */
    /// @{
        /**
         * @brief Convert an integer to hexdecimal string (prefixed with 0x)
         * @param digits 
         *  Minimum number of digits. Defaults to the amount of digits required to represent the largest possible number of type T.
         *  If digits is smaller than the needed amount to represent t, the needed amount is used.
         */
        template<std::integral T>
        std::string toHexString(const T& t, char digits=sizeof(T)*2) {
#ifdef FORMAT
            return std::format("{:#0" + std::to_string(digits) + "x}", t);
#endif
            std::stringstream ss;
            ss << "0x" << std::setfill('0') << std::setw(digits) << std::hex << t;
            return std::string(ss.str());
        }

        /**
         * @brief Convert a hexadecimal string (may be prefixed with 0x) to integer
         */
        template<std::integral T>
        T fromHexString(const std::string& s) {
            T t;
            std::stringstream ss;
            ss << std::hex << s;
            ss >> t;
            return t;
        }

        /**
         * @brief Convert an integer to octal string (prefixed with 0)
         * @param digits 
         *  Minimum number of digits. Defaults to the amount of digits required to represent the largest possible number of type T.
         *  If digits is smaller than the needed amount to represent t, the needed amount is used.
         */
        template<std::integral T>
        std::string toOctString(const T& t, char digits=sizeof(T)*4) {
#ifdef FORMAT
            // TODO test when possible
            return std::format("{:#0" + std::to_string(digits) + "o}", t);
#endif
            std::stringstream ss;
            ss << "0" << std::setfill('0') << std::setw(digits) << std::oct << t;
            return std::string(ss.str());
        }

        /**
         * @brief Convert an octal string (may be prefixed with 0) to integer
         */
        template<std::integral T>
        T fromOctString(const std::string& s) {
            T t;
            std::stringstream ss;
            ss << std::oct << s;
            ss >> t;
            return t;
        }

        /**
         * @brief Convert an integer to binary string (prefixed with 0b)
         */
        template<std::integral T>
        std::string toBinString(const T& t) {
#ifdef FORMAT
            // TODO test when possible
            return std::format("{:#0" + std::to_string(digits) + "b}", t);
#endif
            return std::string("0b") + std::bitset<sizeof(T)*8>(t).to_string();
        }

        /**
         * @brief Convert binary string (may be prefixed with 0b) to integer
         */
        template<std::integral T>
        T fromBinString(const std::string& s) {
            if (s.starts_with("0b")) {
                return static_cast<T>(std::bitset<sizeof(T)*8>(s, 2).to_ullong());
            }
            else {
                return static_cast<T>(std::bitset<sizeof(T)*8>(s).to_ullong());
            }
        }


        /**
         * @overload
         * @brief Construct a string where the elements from a forward range are in hexadecimal format
         * @returns [ 0x0001, 0x0002, ... ]
         */
        template<util::IntegralForwardRange T>
        std::string toHexString(const T& t) {
            std::string s = "[ ";
            for (auto it = t.begin(); it != t.end(); it++) {
                s += toHexString(*it) + ", ";
            }
            if (s.size() > 2) {
                s.erase(s.size() - 2);
            }
            s += " ]";
            return s;
        }
        /**
         * @overload
         * @brief Construct a string where the elements from a forward range are in octal format
         * @returns [ 00001, 00002, ... ]
         */
        template<util::IntegralForwardRange T>
        std::string toOctString(const T& t) {
            std::string s = "[ ";
            for (auto it = t.begin(); it != t.end(); it++) {
                s += toOctString(*it) + ", ";
            }
            if (s.size() > 2) {
                s.erase(s.size() - 2);
            }
            s += " ]";
            return s;
        }
        /**
         * @overload
         * @brief Construct a string where the elements from a forward range are in octal format
         * @returns [ 0b0001, 0b0010, ... ]
         */
        template<util::IntegralForwardRange T>
        std::string toBinString(const T& t) {
            std::string s = "[ ";
            for (auto it = t.begin(); it != t.end(); it++) {
                s += toBinString(*it) + ", ";
            }
            if (s.size() > 2) {
                s.erase(s.size() - 2);
            }
            s += " ]";
            return s;
        }
    /// @}

    /// gz::toString and gz::fromString overloads exist
    template<typename T>
    concept StringConvertible = ConvertibleToString<T> and ConstructibleFromString<T>;

} // namespace gz

/**
 * @file
 * @brief Contains utilities for type conversions to and from string
 */

namespace gz {
/**
 * @page string_conversion String conversion
 * @section sc_about About
 *  This library provides utility for string conversion, from and to `std::string`.
 *  The string utility is split into 3 files:
 *  - @ref to_string.hpp "`<gz-util/string/to_string.hpp>`" for converting types to strings
 *  - @ref from_string.hpp "`<gz-util/string/from_string.hpp>`" for converting strings to other types
 *  - @ref conversion.hpp "`<gz-util/string/conversion.hpp>`" for other string conversion features like from/to bin/oct/hex numbers, also includes the two previous files
 *
 *  There also three important concepts, ConvertibleToString, ConstructibleFromString and @ref StringConvertible which are
 *  used in the @ref Log "logger" and the @ref SettingsManager "settings manager" to log and store types.
 *
 *  If you want to use your own types with one of these, 
 *  you can easily @ref sc_overloads "write your own string conversion" function for your custom types.
 *  
 * @section sc_toString Converting to string
 *  You can use the `gz::toString()` function to turn certain types into strings.
 *  Concepts are used to determine the correct overload of the function.
 *
 *  The concept ConvertibleToString is satisfied for types that can be converted to string 
 *  using `gz::toString()`.
 *  @subsection sc_toStringImplemented Types convertible to string
 *   The toString() function is implemented for these types (non-exhaustive list of examples in braces)
 *   -# Any @ref util::Stringy "string-like type": eg. std::string, std::string_view { std::string, std::string_view }
 *   -# Any @ref util::CanConstructString "type that is accepted by the constructor of std::string()" { char, const char* }
 *   -# Any @ref util::WorksWithStdToString "type that works with std::to_string()" { int, double, bool ... }
 *   -# Any @ref util::HasToStringMember "type that has a `toString() const` or `to_string() const` member that returns a string"
 *   -# Any @ref util::ConvertibleToStringGlobal "type where a `std::string toString(const T&)` overload exists in global namespace
 *   -# Any of the following (the mentioned members have to satisfy one of 1-5)
 *     - Any @ref util::Vector2ConvertibleToString "type with t.x and t.y"
 *     - Any @ref util::Vector3ConvertibleToString "type with t.x, t.y, t.z"
 *     - Any @ref util::Vector4ConvertibleToString "type with t.x, t.y, t.z and t.w"
 *     - Any @ref util::Extent2DConvertibleToString "type with t.width, t.height"
 *     - Any @ref util::Extent3DConvertibleToString "type with t.width, t.height, t.depth"
 *   -# Any of 1-6, but "behind" a pointer
 *   -# Any @ref util::ForwardRangeConvertibleToString "type that has a forward_iterator" which references any one of 1-7 { std::vector<int>, std::list<float> }
 *   -# Any @ref util::PairConvertibleToString "type with t.first and t.second" members which satisfy one of 1-8 { std::pair<int, const char*> }
 *   -# Any @ref util::MapConvertibleToString "type that has a forward_iterator" which references 9 { std::map<unsigned long, std::vector<bool> }
 *  
 * @section sc_fromString Construct from string
 *  You can use the `gz::fromString()` function to create certain types from a string.
 *
 *  The concept ConstructibleFromString is satisfied for types that can be constructed from a string with `gz::fromString()`.
 *
 *  When constructing something from a string, there is of course the problem that errors occur at runtime when
 *  the string is unsuitable for construction. 
 *  In this case, the fromString functions from this library throw an exception (either InvalidArgument, or std::invalid_argument / std::out_of_range).
 *
 * @section sc_overloads Overloading the string conversion functions
 *  @subsection sc_ov_toString Overload for toString
 *   If you want your custom type to be convertible to string, you have different options.
 *   You can either add an `toString() const` member to your class 
 *   or overload `std::string toString(const T&)` in global or gz namespace.
 *   Example for a class called `Custom`:
 *   @code
 *    std::string toString(const Custom& c) {
 *        std::string s;
 *        ...
 *        return s;
 *    }
 *   @endcode
 *
 *  @subsection sc_ov_fromString Overload for fromString
 *   Writing an overload for fromString needs a little bit more boiler plate.
 *   Since fromString is a templated function, you need to declare it as such.
 *   The function declaration in this library uses a concept so that it is only
 *   declared for the types that are actully implemented.
 *   Example for a class called `Custom`:
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
 *  @subsection sc_troubleshooting Troubleshoting
 *   @subsubsection sc_t_1 My custom overloads are not recognized
 *    To satisfy the concept(s) ConvertibleToString/ConstructibleFromString/StringConvertible, any overload must be visible to the compiler when the concept is processed,
 *    so you have to declare it before including `string/to_string.hpp`/`string/from_string.hpp` (which may also be included by `string/conversion.hpp`, `settings_manager.hpp` and `log.hpp`).
 *    To ease troubleshooting the include order, `string/to_string.hpp`/`string_from_string.hpp` each define the macro `GZ_UTIL_STRING_CONCEPTS`,
 *    so you can place an assertion like this before declaring your overloads:
 *    @code
 *     #ifdef GZ_UTIL_STRING_CONCEPTS
 *         static_assert(false, "gz-util/string/conversion.hpp must not be included before this file!");
 *     #endif
 *    @endcode
 *   @subsubsection sc_t_2 I want to use the toString/fromString functions from this library in my custom overloads
 *    Separate the declaration from the definition:
 *    @code
 *     // file.hpp
 *     // do not include any file from <gz-util/string/...>
 *     // declare your overloads:
 *     class Custom {
 *         std::string toString() const;
 *     }
 *     // or
 *     std::string toString(const Custom& c); 
 *
 *     template<std::same_as<Custom> T>
 *     T fromString(const std::string&)
 *
 *     // file.cpp
 *     #include "file.hpp"
 *     #include <gz-util/string/conversion.hpp>
 *
 *     // define your functions
 *     std::string Custom::toString() const {
 *         ...
 *     }
 *     // or
 *     std::string toString(const Custom& c) {
 *         ...
 *     }
 *     
 *     template<>
 *     Custom fromString(const std::string& s) {
 *         ...
 *     }
 *    @endcode
 *
 *   @subsubsection sc_t_3 I want to write the toString() for my Vector types myself
 *    Define the macro `GZ_TO_STRING_NO_VECTORS` before including `<gz-util/string/to_string.hpp>`.
 *    This disables all overloads for Vector and Extent classes.
 *
 *  @todo Implement fromString for ranges that hold ConstructibleFromString types
 *
 * @section sc_int_types Converting integers to/from strings with different base
 *  The functions toHexString(), toOctString() and toBinString() can be used to get a
 *  string of an integers representation in 16 / 8 / 2 basis.
 *
 *  The functions fromHexString<T>(), fromOctString<T>() and fromBinString<T>() can be used to get an integer 
 *  from a string representation of an integer in 16 / 8 / 2 basis.
 *  These function can throw std::invalid_argument and std::out_of_range.
 *
 *  @note toHexString() and toOctString() do not work well with `(unsigned) char` (`(u)int8_t`).
 *
 *  
 */
} // namespace gz
