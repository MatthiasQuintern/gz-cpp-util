#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>


namespace gz::util {

//
// Type conversion
//
    enum Type {
        UINT, INT, DOUBLE, FLOAT, STRING, BOOL,
    };

    bool isInt(std::string& s);
    bool isInt(std::string_view& s);
    int getInt(std::string& s, int fallback=0);
    inline int getInt(std::string&& s, int fallback=0) { return getInt(s, fallback); }
    /**
     * @todo Find a way to convert string_view to int without creating a string from it
     */
    inline int getInt(std::string_view s, int fallback=0) { return getInt(std::string(s), fallback); }

    bool isUInt(std::string& s);
    bool isUInt(std::string_view& s);
    unsigned int getUnsignedInt(std::string& s, unsigned int fallback=0);
    inline unsigned int getUnsignedInt(std::string&& s, unsigned int fallback=0) { return getUnsignedInt(s, fallback); }
    inline unsigned int getUnsignedInt(std::string_view s, unsigned int fallback=0) { return getUnsignedInt(std::string(s), fallback); }

    double getDouble(std::string& s, double fallback=0);
    inline double getDouble(std::string&& s, double fallback=0) { return getDouble(s, fallback); }
    inline double getDouble(std::string_view s, double fallback=0) { return getDouble(std::string(s), fallback); }

    bool isFloat(std::string& s);
    bool isFloat(std::string_view& s);
    float getFloat(std::string& s, float fallback=0);
    inline float getFloat(std::string&& s, float fallback=0) { return getDouble(s, fallback); }
    inline float getFloat(std::string_view s, float fallback=0) { return getDouble(std::string(s), fallback); }

    bool getBool(std::string& s, bool fallback=false);
    inline bool getBool(std::string&& s, bool fallback=false) { return getBool(s, fallback); }
    inline bool getBool(std::string_view s, bool fallback=false) { return getBool(std::string(s), fallback); }

    /**
     * @brief Returns the string or fallback if string is empty.
     */
    std::string getString(std::string s, std::string fallback="none");
    /**
     * @brief Converts the given string to the requested type and puts returns it in a variant
     * @details
     *  Tries to convert the string to the specified type.
     *  If that fails a default value is returned. 
     *  This is either 1 for int or double or "none" for strings.
     *
     * @param value String which should be converted
     * @param type Datatype: 0 = int, 1 = double, 2 = string (default when wrong numer is given)
     *
     * @returns Variant containing the value in the given datatype.
     * @warning Make sure to use the correct type when extracting the value from the returned variant!
     */
    std::variant<std::string, int, double, bool> getVariant(std::string value, Type type=STRING, bool bFallback=false, int iFallback=0, double dFallback=0, const char* sFallback="none");

//
// INDEX UTILITY
//
    template<std::unsigned_integral I, std::unsigned_integral S>
    inline void incrementIndex(I& i, const S containerSize) {
        if (i < containerSize - 1) { i++; }
        else { i = 0; }
    }
    template<std::unsigned_integral I, std::unsigned_integral S>
    inline void decrementIndex(I& i, const S containerSize) {
        if (i > 0) { i--; }
        else { i = containerSize - 1; }
    }
    template<std::unsigned_integral I, std::unsigned_integral S>
    inline I getIncrementedIndex(const I i, const S containerSize) {
        if (i < containerSize - 1) { return i + 1; }
        else { return 0; }
    }
    template<std::unsigned_integral I, std::unsigned_integral S>
    inline I getDecrementedIndex(const I i, const S containerSize) {
        if (i > 0) { return i - 1; }
        else { return containerSize - 1; }
    }
    /// Make wrap incices around: i = size + 2 -> i = 2, i = -2 -> i = size - 2
    template<std::integral I, std::unsigned_integral S>
    size_t getValidIndex(const I i, const S containerSize) {
        if (i < 0) { 
            return containerSize - (-i) % containerSize - 1;
        }
        else if (i >= static_cast<int>(containerSize)) {
            return i % containerSize;
        }
        return i;
    }

//
// STRING
//
    std::vector<std::string> splitStringInVector(std::string& s, char separator = '|');

    /**
     * @name Map with string type as key, works with strings, string_view and char*
     * @{
     */
    struct string_hash
    {
        using hash_type = std::hash<std::string_view>;
        using is_transparent = void;

        size_t operator()(const char* str) const        { return hash_type{}(str); }
        size_t operator()(std::string_view str) const   { return hash_type{}(str); }
        size_t operator()(std::string const& str) const { return hash_type{}(str); }
    };
    template<typename T>
    using string_map = std::unordered_map<std::string, T, util::string_hash, std::equal_to<>>;

} // namespace gz::util

#undef umap

/**
 * @file 
 * @brief Various utilites
 */
