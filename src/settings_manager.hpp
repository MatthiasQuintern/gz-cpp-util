#pragma once

#include "file_io.hpp"
#include "exceptions.hpp"
#include "util/string_conversion.hpp"
#include "util/string.hpp"

#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <set>
#include <typeinfo>
#include <unordered_map>
#include <variant>

namespace gz {
    
    enum SettingsManagerAllowedValueTypes {
        SM_RANGE, SM_LIST,
    };

    /**
     * @brief Information about the allowed values
     * @details
     *  If type is
     *  - SM_RANGE -> allowedValues must be an integer [ low, high, step ], the allowed value can then be in [ low, high ) but must be low + n*step
     *  - SM_LIST -> allowedValues is a list strings, which are the allowed values
     */
    struct SettingsManagerAllowedValues {
        SettingsManagerAllowedValueTypes type;
        std::vector<std::variant<std::string, int>> allowedValues;
    };

    /**
     * @brief Creation info for SettingsManager
     */
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
        /**
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
        util::unordered_string_map<SettingsManagerAllowedValues> allowedValues;
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
     *   The strings are converted using from_string(T), which is either user defined for custom types or @ref from_string "this library".
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
            SettingsManager(SettingsManagerCreateInfo& createInfo);
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
            template<StringConvertible T>
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
            template<StringConvertible T>
            const T& getOr(const std::string& key, const T& fallback);

            /**
             * @brief Same as get, but returns a copy of value and not a const reference
             */
            const std::string getCopy(const std::string& key) const;

            /**
             * @brief Same as get<T>, but returns a copy of value and not a const reference
             */
            template<StringConvertible T>
            const T getCopy(const std::string& key);

            /**
             * @brief Same as getOr, but returns a copy of value and not a const reference
             */
            const std::string getCopyOr(const std::string& key, const std::string& fallback);

            /**
             * @brief Same as getOr<T>, but returns a copy of value and not a const reference
             */
            template<StringConvertible T>
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
             * @throws Exception if an exception occurs during a potential @red sm_callback "callback function"
             */
            void set(const std::string& key, const std::string& value);

            /**
             * @brief Set the value of key to value
             * @throws InvalidArgument if value is @ref sm_validity "invalid"
             * @throws InvalidType if T is not a registered type
             * @throws Exception if an exception occurs during a potential @red sm_callback "callback function"
             */
            template<StringConvertible T>
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
            std::string to_string() const {
                return to_string(settings);
            };

        /**
         * @name Restricting values
         */
            /**
             * @ingroup sm_allowed_values
             * @brief Check if a value is allowed for key
             */
            bool isValueAllowed(const std::string& key, const std::string& value) const noexcept;

            /**
             * @ingroup sm_allowed_values
             * @brief Set the allowed values for a key
             * @details
             *  If the current value for key is now invalid, it will be removed.
             *  values struct is no longer valid after this function
             * @throws InvalidArgument if the values struct is invalid
             */
            void setAllowedValues(const std::string& key, SettingsManagerAllowedValues& values);

            /**
             * @ingroup sm_allowed_values
             * @brief Remove allowed values for key. All values are allowed afterwards
             */
            void removeAllowedValues(const std::string& key) noexcept;
        /**
         * @}
         */

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
            template<StringConvertible T>
            inline bool isRegisteredType();
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
            /**
             * @brief Check if allowed values struct is valid.
             * @details
             *  If type is SM_RANGE and allowedValues only has 2 values (lowest and highest value), the third (step) value=1 is appended
             * @throws InvalidArgument if it is not valid
             */
            void isAllowedValueStructValid(SettingsManagerAllowedValues& av) const;
            util::unordered_string_map<SettingsManagerAllowedValues> allowedValues;
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

    template<StringConvertible... CacheTypes>
    SettingsManager<CacheTypes...>::SettingsManager(SettingsManagerCreateInfo& createInfo) {
        insertFallbacks = createInfo.insertFallbacks;
        writeFileOnExit = createInfo.writeFileOnExit;
        throwExceptionWhenNewValueNotAllowed = createInfo.throwExceptionWhenNewValueNotAllowed;

        allowedValues = std::move(createInfo.allowedValues);
        settings = std::move(createInfo.initialValues);

        filepath = createInfo.filepath;
        if (createInfo.readFileOnCreation) {
            readFromFile(false);
        }

        // erase invalid initalValues 
        for (auto it = settings.begin(); it != settings.end(); it++) {
            if (!isValueAllowed(it->first, it->second)) {
                it = settings.erase(it);
            }
        }

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
        std::cout << "initCache: type " << typeid(CacheType1).name() << "\n";
    }

    template<StringConvertible... CacheTypes>
    template<StringConvertible T>
    inline bool SettingsManager<CacheTypes...>::isRegisteredType() {
        return cacheTypes.contains(typeid(T).name());
    }

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
    template<StringConvertible T>
    const T& SettingsManager<CacheTypes...>::get(const std::string& key) {
        if (!isRegisteredType<T>()) {
            throw InvalidType("Invalid type: '" + std::string(typeid(T).name()) + "'", "SettingsManager::get");
        }
        if (!settings.contains(key)) {
            throw InvalidArgument("Invalid key: '" + key + "'", "SettingsManager::get");
        }
        // if not cached -> cache
        if (!settingsCache[typeid(T).name()].contains(key)) {
            try {
                settingsCache[typeid(T).name()][key] = from_string<T>(settings[key]);
            }
            catch (...) {
                throw InvalidType("Could not convert value '" + settings[key] + "' to type '" + typeid(T).name() + "'. Key: '" + key + "'", "SettingsManager::get");
            }
        }
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
    template<StringConvertible T>
    const T& SettingsManager<CacheTypes...>::getOr(const std::string& key, const T& fallback) {
        if (!isRegisteredType<T>()) {
            throw InvalidType("Invalid type: '" + std::string(typeid(T).name()) + "'", "SettingsManager::getOr");
        }
        if (settings.contains(key)) {
            return get<T>(key);
        }
        else {
            if (insertFallbacks) {
                try {
                    settings[key] = to_string(fallback);
                }
                catch (...) {
                    throw InvalidType("Can not convert fallback value to string. Key: '" + key + "'", "SettingsManager::getOr");
                }
                settingsCache[typeid(T).name()][key] = fallback;
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
    template<StringConvertible T>
    const T SettingsManager<CacheTypes...>::getCopy(const std::string& key) {
        return get<T>(key);
    }
    // COPY OR FALLBACK
    template<StringConvertible... CacheTypes>
    const std::string SettingsManager<CacheTypes...>::getCopyOr(const std::string& key, const std::string& fallback) {
        return getOr(key, fallback);
    }
    template<StringConvertible... CacheTypes>
    template<StringConvertible T>
    const T SettingsManager<CacheTypes...>::getCopyOr(const std::string& key, const T& fallback) {
        return getOr<T>(key, fallback);
    }

//
// SET 
//
    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::set(const std::string& key, const std::string& value) {
        // check if new value is allowed
        if (!isValueAllowed(key, value)) {
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
    template<StringConvertible T>
    void SettingsManager<CacheTypes...>::set(const std::string& key, const T& value) {
        if (!isRegisteredType<T>()) {
            throw InvalidType("Invalid type: '" + std::string(typeid(T).name()) + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">");
        }
        // convert to string
        std::string s;
        try {
            s = to_string(value);
        }
        catch (std::exception& e) {
            throw InvalidArgument("Could not convert value to string, an exception occured: '" + std::string(e.what()) + "'. Key: '" + key + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">");
        }
        catch (...) {
            throw InvalidArgument("Could not convert value to string, an exception occured. Key: '" + key + "'", "SettingsManager::set<" + std::string(typeid(T).name()) + ">");
        }
        // check if new value is allowed
        if (!isValueAllowed(key, s)) {
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
                settingsCallbackFunctions[key](value);
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
   template<StringConvertible... CacheTypes>
    bool SettingsManager<CacheTypes...>::isValueAllowed(const std::string& key, const std::string& value) const noexcept {
        if (!allowedValues.contains(key)) {
            return true;
        }
        switch (allowedValues.at(key).type) {
            case SM_LIST:
                for (auto it = allowedValues.at(key).allowedValues.begin(); it != allowedValues.at(key).allowedValues.end(); it++) {
                    if (std::get<std::string>(*it) == value) {
                        return true;
                    }
                }
                break;
            case SM_RANGE:
                int intVal;
                try {
                    intVal = std::stoi(value);
                }
                catch (std::invalid_argument) {
                    return false;
                }
                catch (std::out_of_range) {
                    return false;
                }
                bool valid = true;
                // intVal >= lowest 
                valid &= intVal >= std::get<int>(allowedValues.at(key).allowedValues[0]);
                // intVal < highest 
                valid &= intVal < std::get<int>(allowedValues.at(key).allowedValues[1]);
                // intVal == lowest + n * step
                valid &= (intVal - std::get<int>(allowedValues.at(key).allowedValues[0])) % std::get<int>(allowedValues.at(key).allowedValues[2]) == 0;
                return valid;
                break;
        } // switch
    }

    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::initAllowedValues() {
        for (auto& [key, av] : allowedValues) {
            isAllowedValueStructValid(av);
        } // for
    }

    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::isAllowedValueStructValid(SettingsManagerAllowedValues& av) const {
        switch (av.type) {
            case SM_LIST:
                if (av.allowedValues.empty()) {
                    throw InvalidArgument("Allowed value vector needs to have at least one element, but is empty.", "SettingsManager::isAllowedValueStructValid");
                }
                for (size_t i = 0; i < av.allowedValues.size(); i++) {
                    try {
                            std::get<std::string>(av.allowedValues[i]);
                        }
                    catch (std::bad_variant_access& e) {
                        throw InvalidType("AllowedValueType is SM_LIST but allowedValues[" + std::to_string(i) + "] is not of type <std::string>.", "SettingsManager::isAllowedValueStructValid");
                    }
                }
                break;
            case SM_RANGE:
                if (av.allowedValues.size() == 2) {
                    av.allowedValues.push_back(1);
                }
                else if (av.allowedValues.size() != 3) {
                    throw InvalidArgument("AllowedValueType is SM_RANGE but allowedValues does not have size 2 or 3.", "SettingsManager::isAllowedValueStructValid");
                }
                try {
                    std::get<int>(av.allowedValues[0]);
                    std::get<int>(av.allowedValues[1]);
                    std::get<int>(av.allowedValues[2]);
                }
                catch (std::bad_variant_access& e) {
                    throw InvalidType("AllowedValueType is SM_RANGE but at least one value in allowedValues is not of type <int>.", "SettingsManager::isAllowedValueStructValid");
                }
                break;
        }  // switch
    }


    template<StringConvertible... CacheTypes>
    void SettingsManager<CacheTypes...>::setAllowedValues(const std::string& key, SettingsManagerAllowedValues& av) {
        isAllowedValueStructValid(av);
        allowedValues[key] = std::move(av);
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
        std::unordered_map<std::string, std::string> map = readKeyValueFile(filepath);
        settings.insert(map.begin(), map.end());
        if (checkValidity) {
            // insert only valid values
            for (auto it = map.begin(); it != map.end(); it++) {
                if (isValueAllowed(it->first, it->second)) {
                    settings.insert(*it);
                }
            }
        } 
        else {
            settings.insert(map.begin(), map.end());
        }
    }
}

