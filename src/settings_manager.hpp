#pragma once

#include "file_io.hpp"
#include "exceptions.hpp"
#include "string/conversion.hpp"
#include "string/utility.hpp"
#include "concepts.hpp"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <set>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <variant>

namespace gz {

    template<typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template<typename T>
    concept NotNumber = !Number<T>;

    /* template<typename T, typename... PackTypes> */
    /* concept IntegralInPack = std::integral<T> && util::IsInPack<T, PackTypes...>; */

    /* template<typename T, typename... PackTypes> */
    /* concept FloatingPointInPack = std::floating_point<T> && util::IsInPack<T, PackTypes...>; */

    template<typename T, typename... PackTypes>
    concept NumberInPack = Number<T> && util::IsInPack<T, PackTypes...>;

    template<typename T, typename... PackTypes>
    concept NotNumberInPack = NotNumber<T> && util::IsInPack<T, PackTypes...>;


    
    enum SettingsManagerAllowedValueTypes {
        SM_RANGE, SM_LIST,
    };

    /**
     * @brief Information about the allowed values
     * @details
     *  If type is
     *  - SM_RANGE -> allowedValues must contain two numbers [min, max]
     *  - SM_LIST -> allowedValues must contain strings, which are the allowed values
     */
    template<StringConvertible... CacheTypes>
    struct SettingsManagerAllowedValues {
        SettingsManagerAllowedValueTypes type;
        std::variant<std::vector<std::string>, std::vector<CacheTypes>... > allowedValues;
    };
    /**
     * @brief Check if struct is valid.
     * @throws InvalidType if:
     *  - the type contained in the variant allowedValues is not T
     *  - type is SM_RANGE but T is not an integral or floating point type
     *  
     * @throws InvalidArgument if: 
     *  - vector contained in allowedValues is empty
     *  - type is SM_RANGE but allowedValues is not of size 2
     *  - type is SM_RANGE but allowedValues[0] >= allowedValues[1]
     */
    template<Number T, StringConvertible... CacheTypes>
    void hasCorrectFormat(SettingsManagerAllowedValues<CacheTypes...>& ab);
    template<NotNumber T, StringConvertible... CacheTypes>
    void hasCorrectFormat(SettingsManagerAllowedValues<CacheTypes...>& av);
    /* template<std::integral T, StringConvertible... CacheTypes> */
    /* void hasCorrectFormat(SettingsManagerAllowedValues<CacheTypes...>& ab); */

    /**
     * @brief Creation info for SettingsManager
     */
    template<StringConvertible... CacheTypes>
    struct SettingsManagerCreateInfo {
        /**
         * @brief (Optional) Path to the file containing the settings
         */
        std::string filepath;
        /**
         * @brief (Optional) Map containing default values.
         * @details
         *  Values loaded from a file will overwrite these.
         */
        util::unordered_string_map<std::string> initialValues;
        /**
         * @brief Wether to insert a fallback, when no value is present
         * @details
         *  If true, fallback value for key will be added if key does not have a value.
         *  This applies when calling SettingsManager::getOr or SettingsManager::getCopyOr
         */
        bool insertFallbacks = false;
        /**
         * @brief Wether to load values from filepath when creating the SettingsManager
         */
        bool readFileOnCreation = false;
        /**
         * @brief Wether to write the values to filepath when destroying the SettingsManager
         */
        bool writeFileOnExit = false;
        /*
         * @brief A map containing SettingsMangerAllowedValues to restrict values
         * @details
         *  If allowedValues contains key, its value must be allowed by SettingsMangerAllowedValues struct.
         *  If it is not allowed, any operation that tries to set an invalid value will throw InvalidArgument or be ignored:
         *  - in constructor: always ignored
         *  - in SettingsManager::readFileOnCreation: always ignored
         *  - in SettingsManager::setAllowedValues: always ignored
         *  - in SettingsManager::set: depends on throwExceptionWhenNewValueNotAllowed
         * @see sm_validity 
         */
        /* util::unordered_string_map<SettingsManagerAllowedValues<CacheTypes...>> allowedValues; */
        /**
         * @brief Wether to throw an exception when trying to set an invalid value
         */  
        bool throwExceptionWhenNewValueNotAllowed = true;
    };

    using SettingsCallbackFunction = std::function<void(const std::string&)>;

    /**
     * @brief 
     * @details
     *  @section sm_about About
     *   The SettingsManager is basically a map with extra features. 
     *   It stores key-value pairs in a map. Both key and value are strings, but other types can also be stored. 
     *
     *  @section sm_validity Restricting values
     *   SettingsManager can restrict the values for a given keys to a range of numbers, or a list of possible strings.
     *   This can be done by providing @ref SettingsMangerAllowedValues::allowedValues "a map containing information on the allowed values" in the create info.
     *   The settings manager will then never return an invalid value, but it might still throw errors if there is no value set.
     *
     *  @section sm_cache Storing other types
     *   While all values are internally strings, SettingsManager can also store different types.
     *   The types must satisfy the concept StringConvertible = ConstructibleFromString and ConvertibleToString.
     *   
     *   If a value is requested using get<T>(), the value will be converted to T and returned. 
     *   Additionaly, the converted type is cached so that the conversion can be skipped if it is requested again.
     *   The user must instantiate the SettingsManager with all the cache-types beforehand, only those can be retrieved using get.
     *
     *   The strings are converted using fromString(T), which is either user defined for custom types or @ref fromString "this library".
     *   There is of course no guarantee that the conversion works, the @ref sm_getters "getters" will throw an exception if it doesnt.
     *
     *  @section sm_callback Callback functions
     *   You can @ref SettingsManager::addCallbackFunction "add a callback function" for each key that gets called when a setting gets changed.
     */
    template<StringConvertible... CacheTypes>
    class SettingsManager {
        public:
            /**
             * @brief Create a SettingsManager
             * @details
             *  The maps from createInfo are no longer valid after this function.
             */
            SettingsManager(SettingsManagerCreateInfo<CacheTypes...>& createInfo);
            ~SettingsManager();
            SettingsManager(const SettingsManager&) = delete;
            SettingsManager& operator=(const SettingsManager&) = delete;

        /**
         * @name Retrieve values
         * @{
         */
            /**
             * @brief Get a reference to a value 
             * @param key The key to the value
             * @returns The value belonging to key
             * @throws InvalidArgument if key is not present
             */
            const std::string& get(const std::string& key) const;
            /**
             * @brief Get a reference to the value coverted to T
             * @param key The key to the setting
             * @returns The setting belonging to key, constructed by getTypeFromString<T>()
             * @throws InvalidArgument if key is not present
             * @throws InvalidType if T is not a registered type
             * @throws InvalidType if type T can not be constructed from value (string)
             */
            template<util::IsInPack<CacheTypes...> T>
            const T& get(const std::string& key);

            /**
             * @brief Get a reference to the value, or return the fallback if the setting is not present
             * @param key The key to the value
             * @param fallback A fallback to return if the key is not present
             * @returns The value belonging to key, constructed by getTypeFromString<T>()
             * @throws InvalidArgument if key is not present
             */
            const std::string& getOr(const std::string& key, const std::string& fallback);

            /**
             * @brief Get a reference to the value coverted to T, or return the fallback if the setting is not present
             * @param key The key to the value
             * @param fallback A fallback to return if the key is not present
             * @returns The value belonging to key, constructed by getTypeFromString<T>()
             * @throws InvalidArgument if key is not present
             * @throws InvalidType if T is not a registered type
             * @throws InvalidType if type T can not be constructed from value (string)
             * @throws InvalidType if the fallback can not be converted to string
             */
            template<util::IsInPack<CacheTypes...> T>
            const T& getOr(const std::string& key, const T& fallback) requires std::copy_constructible<T>;

            /**
             * @brief Same as get, but returns a copy of value and not a const reference
             */
            const std::string getCopy(const std::string& key) const;

            /**
             * @brief Same as get<T>, but returns a copy of value and not a const reference
             */
            template<util::IsInPack<CacheTypes...> T>
            const T getCopy(const std::string& key);

            /**
             * @brief Same as getOr, but returns a copy of value and not a const reference
             */
            const std::string getCopyOr(const std::string& key, const std::string& fallback);

            /**
             * @brief Same as getOr<T>, but returns a copy of value and not a const reference
             */
            template<util::IsInPack<CacheTypes...> T>
            const T getCopyOr(const std::string& key, const T& fallback);

        /**
         * @}
         */


        /**
         * @name Set values
         */
            /**
             * @brief Set the value of key to value
             * @throws InvalidArgument if value is @ref sm_validity "invalid"
             * @throws Exception if an exception occurs during a potential @ref sm_callback "callback function"
             */
            void set(const std::string& key, const std::string& value);

            /**
             * @brief Set the value of key to value
             * @throws InvalidArgument if value is @ref sm_validity "invalid"
             * @throws InvalidType if T is not a registered type
             * @throws Exception if an exception occurs during a potential @ref sm_callback "callback function"
             */
            template<util::IsInPack<CacheTypes...> T>
            void set(const std::string& key, const T& value);
        /**
         * @}
         */

        /**
         * @name Callback functions
         */
            /**
             * @brief Add a callback function that gets called when the the value to key is changed with set
             */
            void addCallbackFunction(const std::string& key, SettingsCallbackFunction callbackFunction);
            /**
             * @brief Remove the callback function for key
             */
            void removeCallbackFunction(const std::string& key);
        /**
         * @}
         */

        /**
         * @name File operations
         * @{
         */
            void writeToFile() const;
            /**
             * @brief Read the contents from the provided @ref SettingsManagerCreateInfo::filepath "filepath"
             * @param checkValidity if true, inserts only files that are @ref sm_validity "valid"
             */
            void readFromFile(bool checkValidity=true);
        /**
         * @}
         */
            std::string toString() const {
                return gz::toString(settings);
            };

        /**
         * @name Restricting values
         */
            /**
             * @ingroup sm_allowed_values
             * @brief Check if a value is allowed for key
             */
            template<NumberInPack<std::string, CacheTypes...> T>
            bool isValueAllowed(const std::string& key, const T& value) const noexcept;
            /* template<IntegralInPack<std::string, CacheTypes...> T> */
            /* bool isValueAllowed(const std::string& key, const T& value) const noexcept; */
            template<NotNumberInPack<std::string, CacheTypes...> T>
            bool isValueAllowed(const std::string& key, const T& value) const noexcept;

            /**
             * @ingroup sm_allowed_values
             * @brief Set the allowed values for a key
             * @param key The key where the allowedValues should be applied
             * @param type The type containing information on the values in allowedValues
             * @param allowedValues Vector containing:
             *  - a list of allowed values if type=SM_LIST
             *  - [min, max] if type=SM_RANGE
             *
             * @details
             *  If the current value for key is now invalid, it will be removed.
             *  allowedValues vector is no longer valid after this function
             * @throws InvalidArgument if call is @ref SettingsMangerAllowedValues::hasCorrectFormat "invalid"
             */
            template<util::IsInPack<CacheTypes...> T>
            void setAllowedValues(const std::string& key, std::vector<T>& allowedValues, SettingsManagerAllowedValueTypes type=SM_LIST);
            template<util::IsInPack<CacheTypes...> T>
            void setAllowedValues(const std::string& key, std::vector<T>&& allowedValues, SettingsManagerAllowedValueTypes type=SM_LIST) { setAllowedValues<T>(key, allowedValues, type); };

            /**
             * @ingroup sm_allowed_values
             * @brief Remove allowed values for key. All values are allowed afterwards
             */
            void removeAllowedValues(const std::string& key) noexcept;
        /**
         * @}
         */
            /**
             * @brief Get a const reference to the underlying map
             */
            const util::unordered_string_map<std::string>& getSettingsMap() const { return settings; };

        private:
        /**
         * @ingroup sm_cache
         * @{
         */
            /**
             * @brief Recursive initialitation of the cache
             * @details
             *  The cache is initialized by placing the the typename in the cacheTypes set.
             *  It will not actually be added as cache type.
             *  The "Void" type template parameter is needed because the exit for the recursion must also have a template signature.
             *  When calling this, use initCache<void, CacheTypes...>().
             */
            template<std::same_as<void> Void, StringConvertible CacheType1, StringConvertible... CacheTypesOther>
            void initCache();
            /**
             * @brief End for the recursive cache initialization
             *
             */
            template<std::same_as<void> Void>
            void initCache() {};
            std::set<std::string> cacheTypes;
            util::unordered_string_map<util::unordered_string_map<std::variant<std::monostate, CacheTypes...>>> settingsCache;
            /* template<StringConvertible T> */
            /* inline bool isRegisteredType(); */
        /**
         * @}
         */
        /**
         * @name Restricting values
         * @see sm_validity
         * @{
         */
            // Allowed Values
            /**
             * @brief Make sure the allowedValues map is valid
             * @throws InvalidArgument if any of the initial allowedValues structs is invalid
             */
            void initAllowedValues();
            util::unordered_string_map<SettingsManagerAllowedValues<CacheTypes...>> allowedValues;
            bool throwExceptionWhenNewValueNotAllowed;
        /**
         * @}
         */

            util::unordered_string_map<std::string> settings;
            util::unordered_string_map<SettingsCallbackFunction> settingsCallbackFunctions;

            // Settings
            /**
             * @brief Add fallback to values if key is not present when using getOr
             */
            bool insertFallbacks;
            bool writeFileOnExit;
            std::string filepath;
    };
}

namespace gz {
    /* template<StringConvertible... CacheTypes, NumberInPack<std::string, CacheTypes...> T> */
    /* template<std::integral T, StringConvertible... CacheTypes> */
    /* void hasCorrectFormat(SettingsManagerAllowedValues<CacheTypes...>& av) { */
    /*     const std::vector<T>* v = nullptr; */
    /*     try { */
    /*         v = &std::get<std::vector<T>>(av.allowedValues); */
    /*     } */
    /*     catch (std::bad_variant_access& e) { */
    /*         throw InvalidType("allowedValues variant does not contain type T", "SettingsManagerAllowedValues::hasCorrectFormat"); */
    /*     } */
    /*     switch (av.type) { */
    /*         case SM_LIST: */
    /*             if (v->empty()) { */
    /*                 throw InvalidArgument("Allowed value vector needs to have at least one element when AllowedValueType is SM_LIST, but is empty.", "SettingsManagerAllowedValues::hasCorrectFormat"); */
    /*             } */
    /*             break; */
    /*         case SM_RANGE: */
    /*             static_assert(std::floating_point<T> || std::integral<T>, "Type must be integral or floating point when using SM_RANGE."); */
    /*             std::size_t size = std::get<std::vector<int>>(av.allowedValues).size(); */
    /*             if (size == 2) { */
    /*                 v->push_back(static_cast<T>(1)); */
    /*             } */
    /*             else if (size != 3) { */
    /*                 throw InvalidArgument("AllowedValueType is SM_RANGE with integral type but allowedValues does not have size 2 or 3.", "SettingsManagerAllowedValues::hasCorrectFormat"); */
    /*             } */
    /*             // check min < max */
    /*             if (v[0] >= v[1]) { */
    /*                 throw InvalidArgument("AllowedValueType is SM_RANGE but allowedValues[0] is larger than allowedValues[1].", "SettingsManagerAllowedValues::hasCorrectFormat"); */
    /*             } */
    /*             break; */
    /*     }  // switch */
    /* } */

    template<Number T, StringConvertible... CacheTypes>
    void hasCorrectFormat(SettingsManagerAllowedValues<CacheTypes...>& av) {
        static_assert(util::IsInPack<T, CacheTypes...>, "T must be be in pack CacheTypes");
        const std::vector<T>* v = nullptr;
        try {
            v = &std::get<std::vector<T>>(av.allowedValues);
        }
        catch (std::bad_variant_access& e) {
            throw InvalidType("allowedValues variant does not contain type T", "SettingsManagerAllowedValues::hasCorrectFormat");
        }
        switch (av.type) {
            case SM_LIST:
                if (v->empty()) {
                    throw InvalidArgument("Allowed value vector needs to have at least one element when AllowedValueType is SM_LIST, but is empty.", "SettingsManagerAllowedValues::hasCorrectFormat");
                }
                break;
            case SM_RANGE:
                static_assert(std::floating_point<T> || std::integral<T>, "Type must be integral or floating point when using SM_RANGE.");
                std::size_t size = v->size();
                if (size != 2) {
                    throw InvalidArgument("AllowedValueType is SM_RANGE with floating point type but allowedValues does not have size 2.", "SettingsManagerAllowedValues::hasCorrectFormat");
                }
                // check min <= max
                if (v->at(0) > v->at(1)) {
                    /* throw InvalidArgument("AllowedValueType is SM_RANGE but allowedValues[0] >= allowedValues[1].", "SettingsManagerAllowedValues::hasCorrectFormat"); */
                    throw InvalidArgument("AllowedValueType is SM_RANGE but allowedValues[0]=" + toString(v->at(0)) + " > " + toString(v->at(1)) + "=allowedValues[1].", "SettingsManagerAllowedValues::hasCorrectFormat");
                }
                break;
        }  // switch
    }

    /* template<StringConvertible... CacheTypes, NotNumberInPack<std::string, CacheTypes...> T> */
    template<NotNumber T, StringConvertible... CacheTypes>
    void hasCorrectFormat(SettingsManagerAllowedValues<CacheTypes...>& av) {
        static_assert(util::IsInPack<T, CacheTypes...>, "T must be be in pack CacheTypes");
        const std::vector<T>* v = nullptr;
        try {
            v = &std::get<std::vector<T>>(av.allowedValues);
        }
        catch (std::bad_variant_access& e) {
            throw InvalidType("allowedValues variant does not contain type T", "SettingsManagerAllowedValues::hasCorrectFormat");
        }
        switch (av.type) {
            case SM_LIST:
                if (v->empty()) {
                    throw InvalidArgument("Allowed value vector needs to have at least one element when AllowedValueType is SM_LIST, but is empty.", "SettingsManagerAllowedValues::hasCorrectFormat");
                }
                break;
            case SM_RANGE:
                throw InvalidArgument("Type must be integral or floating point when using SM_RANGE, but is <" + std::string(typeid(T).name()) + ">");
                break;
        }  // switch
    }


// 
// SETTINGS MANAGER 
//
    template<StringConvertible... CacheTypes>
    SettingsManager<CacheTypes...>::SettingsManager(SettingsManagerCreateInfo<CacheTypes...>& createInfo) {
        insertFallbacks = createInfo.insertFallbacks;
        writeFileOnExit = createInfo.writeFileOnExit;
        throwExceptionWhenNewValueNotAllowed = createInfo.throwExceptionWhenNewValueNotAllowed;

        /* allowedValues = std::move(createInfo.allowedValues); */
        settings = std::move(createInfo.initialValues);

        filepath = createInfo.filepath;
        if (createInfo.readFileOnCreation) {
            readFromFile(false);
        }

        // erase invalid initalValues 
        /* for (auto it = settings.begin(); it != settings.end(); it++) { */
        /*     if (!isValueAllowed<std::string>(it->first, it->second)) { */
        /*         it = settings.erase(it); */
        /*     } */
        /* } */

        initCache<void, CacheTypes...>();
    }

    template<StringConvertible... CacheTypes>
    SettingsManager<CacheTypes...>::~SettingsManager() {
        if (writeFileOnExit) {
            writeToFile();
        }
    }

    template<StringConvertible... CacheTypes>
    template<std::same_as<void> Void, StringConvertible CacheType1, StringConvertible... CacheTypesOther>
    void SettingsManager<CacheTypes...>::initCache() {
        cacheTypes.insert(typeid(CacheType1).name());
        initCache<void, CacheTypesOther...>();
    }

    /* template<StringConvertible... CacheTypes> */
    /* template<StringConvertible T> */
    /* inline bool SettingsManager<CacheTypes...>::isRegisteredType() { */
    /*     return cacheTypes.contains(typeid(T).name()); */
    /* } */

//
// GET
//
    // REFERENCE
    template<StringConvertible... CacheTypes>
    const std::string& SettingsManager<CacheTypes...>::get(const std::string& key) const {
        if (!settings.contains(key)) {
            throw InvalidArgument("Invalid key: " + key + "'", "SettingsManager::get");
        }
        return settings.at(key);
    }

    template<StringConvertible... CacheTypes>
    template<util::IsInPack<CacheTypes...> T>
    const T& SettingsManager<CacheTypes...>::get(const std::string& key) {
        static_assert(util::IsInPack<T, CacheTypes...>, "Type T is not in parameter pack CacheTypes...");
        /* if (!isRegisteredType<T>()) { */
        /*     throw InvalidType("Invalid type: '" + std::string(typeid(T).name()) + "'", "SettingsManager::get"); */
        /* } */
        if (!settings.contains(key)) {
            throw InvalidArgument("Invalid key: '" + key + "'", "SettingsManager::get");
        }
        // if not cached -> cache
        if (!settingsCache[typeid(T).name()].contains(key)) {
            try {
                /* settingsCache[typeid(T).name()][key].emplace(fromString<T>(settings[key])); */
                /* settingsCache[typeid(T).name()][key](fromString<T>(settings[key])); */
                settingsCache[typeid(T).name()][key] = std::variant<std::monostate, CacheTypes...>(fromString<T>(settings[key]));
            }
            catch (...) {
                throw InvalidType("Could not convert value '" + settings[key] + "' to type '" + std::string(typeid(T).name()) + "'. Key: '" + key + "'", "SettingsManager::get");
            }
        }
        /* std::cout << "get<" << typeid(T).name() << ">\n"; */
        return std::get<T>(settingsCache[typeid(T).name()][key]);
    }

    
    // REFERENCE OR FALLBACK
    template<StringConvertible... CacheTypes>
    const std::string& SettingsManager<CacheTypes...>::getOr(const std::string& key, const std::string& fallback) {
        if (settings.contains(key)) {
            return get(key);
        }
        else {
            if (insertFallbacks) {
                settings[key] = fallback;
            }
            return fallback;
        }
    }

    template<StringConvertible... CacheTypes>
    template<util::IsInPack<CacheTypes...> T>
    const T& SettingsManager<CacheTypes...>::getOr(const std::string& key, const T& fallback) requires std::copy_constructible<T> {
        /* if (!isRegisteredType<T>()) { */
        /*     throw InvalidType("Invalid type: '" + std::string(typeid(T).name()) + "'", "SettingsManager::getOr"); */
        /* } */
        if (settings.contains(key)) {
            return get<T>(key);
        }
        else {
            if (insertFallbacks) {
                try {
                    settings[key] = gz::toString(fallback);
                }
                catch (...) {
                    throw InvalidType("Can not convert fallback value to string. Key: '" + key + "'", "SettingsManager::getOr");
                }
                /* static_assert(CanInsertTIntoVariant<T, std::monostate, CacheTypes...>, "ERROR: Can not insert T into variant with monostate, CacheTypes..."); */
                /* settingsCache[typeid(T).name()][key].emplace(fallback); */
                settingsCache[typeid(T).name()][key] = std::variant<std::monostate, CacheTypes...>(T(fallback));
            }
            return fallback;
        }
    }

    // COPY
    template<StringConvertible... CacheTypes>
    const std::string SettingsManager<CacheTypes...>::getCopy(const std::string& key) const {
        return get(key);
    }
    template<StringConvertible... CacheTypes>
    template<util::IsInPack<CacheTypes...> T>
    const T SettingsManager<CacheTypes...>::getCopy(const std::string& key) {
        return get<T>(key);
    }
    // COPY OR FALLBACK
    template<StringConvertible... CacheTypes>
    const std::string SettingsManager<CacheTypes...>::getCopyOr(const std::string& key, const std::string& fallback) {
        return getOr(key, fallback);
    }
    template<StringConvertible... CacheTypes>
    template<util::IsInPack<CacheTypes...> T>
    const T SettingsManager<CacheTypes...>::getCopyOr(const std::string& key, const T& fallback) {
        return getOr<T>(key, fallback);
    }

//
// SET 
//
    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::set(const std::string& key, const std::string& value) {
        // check if new value is allowed
        if (!isValueAllowed<std::string>(key, value)) {
            if (throwExceptionWhenNewValueNotAllowed) {
                throw InvalidArgument("Value '" + value + "' is not allowed. Key: '" + key + "'", "SettingsManager::set");
            }
            else {
                return;
            }
        }
        // remove old value from cache
        for (auto& [type, cache] : settingsCache) {
            if (cache.contains(key)) {
                cache.erase(key);
            }
        }
        settings[key] = value;
        // Call the callback, if any
        if (settingsCallbackFunctions.contains(key)) {
            try {
                settingsCallbackFunctions[key](value);
            }
            catch (std::exception& e) {
                throw Exception("An exception occured in the callback for changing a value: '" + std::string(e.what()) + "'. Key: '" + key + "'", "SettingsManager::set");
            }
            catch (...) {
                throw Exception("An exception occured in the callback for changing a value. Key: '" + key + "'", "SettingsManager::set");
            }
        }
    }

    template<StringConvertible... CacheTypes>
    template<util::IsInPack<CacheTypes...> T>
    void SettingsManager<CacheTypes...>::set(const std::string& key, const T& value) {
        /* if (!isRegisteredType<T>()) { */
        /*     throw InvalidType("Invalid type: '" + std::string(typeid(T).name()) + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">"); */
        /* } */
        // convert to string
        std::string s;
        try {
            s = gz::toString(value);
        }
        catch (std::exception& e) {
            throw InvalidArgument("Could not convert value to string, an exception occured: '" + std::string(e.what()) + "'. Key: '" + key + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">");
        }
        catch (...) {
            throw InvalidArgument("Could not convert value to string, an exception occured. Key: '" + key + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">");
        }
        // check if new value is allowed
        if (!isValueAllowed<T>(key, value)) {
            if (throwExceptionWhenNewValueNotAllowed) {
                throw InvalidArgument("Value '" + s + "' is not allowed. Key: '" + key + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">");
            }
            else {
                return;
            }
        }
        // remove old value from cache
        for (auto& [type, cache] : settingsCache) {
            if (cache.contains(key)) {
                cache.erase(key);
            }
        }
        // add new value
        settings[key] = std::move(s);
        settingsCache[typeid(T).name()][key] = value;
        // Call the callback, if any
        if (settingsCallbackFunctions.contains(key)) {
            try {
                settingsCallbackFunctions[key](s);
            }
            catch (std::exception& e) {
                throw Exception("An exception occured in the callback for changing a value: '" + std::string(e.what()) + "'. Key: '" + key + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">");
            }
            catch (...) {
                throw Exception("An exception occured in the callback for changing a value. Key: '" + key + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">");
            }
        }
    }

//
// ALLOWED VALUES
//
    /* template<StringConvertible... CacheTypes> */
    /* template<IntegralInPack<std::string, CacheTypes...> T> */
    /* bool SettingsManager<CacheTypes...>::isValueAllowed(const std::string& key, const T& value) const noexcept { */
    /*     if (!allowedValues.contains(key)) { */
    /*         return true; */
    /*     } */
    /*     const std::vector<T>* av = nullptr; */
    /*     try { */
    /*         av = &std::get<std::vector<T>>(allowedValues.at(key).allowedValues); */
    /*     } */
    /*     catch (std::bad_variant_access&) { */
    /*         return false; */
    /*     } */

    /*     switch (allowedValues.at(key).type) { */
    /*         case SM_LIST: { */
    /*             for (auto it = av->begin(); it != av->end(); it++) { */
    /*                 if (*it == value) { */
    /*                     return true; */
    /*                 } */
    /*             } */
    /*         } */
    /*         break; */
    /*         case SM_RANGE: { */
    /*             bool valid = true; */
    /*             // value >= lowest */ 
    /*             valid &= value >= av->at(0); */
    /*             // value < highest */ 
    /*             valid &= value < av->at(1); */
    /*             // value == lowest + n * step */
    /*             valid &= (value - av->at(0)) % av->at(2) == 0; */
    /*             return valid; */
    /*         } */
    /*         break; */
    /*     } // switch */
    /*     return false; */
    /* } */

    template<StringConvertible... CacheTypes>
    template<NumberInPack<std::string, CacheTypes...> T>
    bool SettingsManager<CacheTypes...>::isValueAllowed(const std::string& key, const T& value) const noexcept {
        if (!allowedValues.contains(key)) {
            return true;
        }
        const std::vector<T>* av = nullptr;
        try {
            av = &std::get<std::vector<T>>(allowedValues.at(key).allowedValues);
        }
        catch (std::bad_variant_access&) {
            return false;
        }

        switch (allowedValues.at(key).type) {
            case SM_LIST: {
                for (auto it = av->begin(); it != av->end(); it++) {
                    if (*it == value) {
                        return true;
                    }
                }
            }
            break;
            case SM_RANGE: {
                bool valid = true;
                // value >= lowest 
                valid &= value >= av->at(0);
                // value <= highest 
                valid &= value <= av->at(1);
                return valid;
            }
            break;
        } // switch
        return false;
    }
    template<StringConvertible... CacheTypes>
    template<NotNumberInPack<std::string, CacheTypes...> T>
    bool SettingsManager<CacheTypes...>::isValueAllowed(const std::string& key, const T& value) const noexcept {
        if (!allowedValues.contains(key)) {
            return true;
        }
        const std::vector<T>* av = nullptr;
        try {
            av = &std::get<std::vector<T>>(allowedValues.at(key).allowedValues);
        }
        catch (std::bad_variant_access&) {
            return false;
        }
        switch (allowedValues.at(key).type) {
            case SM_LIST: {
                for (auto it = av->begin(); it != av->end(); it++) {
                    if (*it == value) {
                        return true;
                    }
                }
            }
            break;
            case SM_RANGE: {
                return false;
            }
            break;
        } // switch
        return false;
    }

    template<StringConvertible... CacheTypes>
    template<util::IsInPack<CacheTypes...> T>
    void SettingsManager<CacheTypes...>::setAllowedValues(const std::string& key, std::vector<T>& allowed_vector, SettingsManagerAllowedValueTypes type) {
        /* std::cout << "setAllowedValues: " << typeid(std::vector<T>).name() << " - " << typeid(T).name() << "\n"; */
        SettingsManagerAllowedValues<CacheTypes...> av;
        av.type = type;
        av.allowedValues = std::variant<std::vector<std::string>, std::vector<CacheTypes>...>(std::move(allowed_vector));
        hasCorrectFormat<T>(av);
        allowedValues[key] = std::move(av);
        // erase the current value if it is no longer allowed
        if (settingsCache[typeid(T).name()].contains(key)) {
            /* std::cout << "setAllowedValues <" << typeid(T).name() << ">\n"; */
            if (!isValueAllowed<T>(key, std::get<T>(settingsCache[typeid(T).name()].at(key)))) {
                settings.erase(key);
                settingsCache[typeid(T).name()].erase(key);
            }
        }
        else if (settings.contains(key)) {
            try {
                if (!isValueAllowed<T>(key, fromString<T>(settings.at(key)))) {
                    settings.erase(key);
                }
            }
            catch (...) {
                settings.erase(key);
            }
        }
    }

    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::removeAllowedValues(const std::string& key) noexcept {
        allowedValues.erase(key);
    }
//
// CALLBACKS
//
    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::addCallbackFunction(const std::string& key, SettingsCallbackFunction callbackFunction) {
        settingsCallbackFunctions[key] = callbackFunction;
    }
    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::removeCallbackFunction(const std::string& key) {
        settingsCallbackFunctions.erase(key);
    }

// 
// FILE IO
//
    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::writeToFile() const {
        if (filepath.empty()) {
            throw InvalidArgument("filename is not set", "writeToFile");
        }
        writeKeyValueFile(filepath, settings);
    }

    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::readFromFile(bool checkValidity) {
        if (filepath.empty()) {
            throw InvalidArgument("filename is not set", "readFromFile");
        }
        std::unordered_map<std::string, std::string> map = readKeyValueFile<std::unordered_map<std::string, std::string>>(filepath);
        settings.insert(map.begin(), map.end());
        if (checkValidity) {
            // insert only valid values
            for (auto it = map.begin(); it != map.end(); it++) {
                if (isValueAllowed<std::string>(it->first, it->second)) {
                    settings.insert(*it);
                }
            }
        } 
        else {
            settings.insert(map.begin(), map.end());
        }
    }
}

