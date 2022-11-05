#pragma once

#include "../concepts.hpp"

#include <string>
#include <string_view>
#include <ranges>

#define GZ_UTIL_STRING_CONCEPTS

/**
 * @brief Declaration of toString in global namespace, so that concepts can use it.
 */
template<gz::util::False T>
std::string toString(const T& s);

namespace gz::util {
    /**
     * @name 1) concepts for elementary types and custom toStrings()
     * @details
     *  Definition order matters, the earlier the concept, the "stronger" because later concepts must not also satisfy the previous ones.
     * @{
     */
        /// same as std::string, std::string_view or const char*
        template<typename T> 
        concept Stringy = util::IsInPack<T, std::string, std::string_view, const char*>;

        /// can construct std::string from T
        template<typename T> 
        concept CanConstructString = 
            !Stringy<T> && 
            requires(const T& t) {
                { std::string(t) } -> std::same_as<std::string>;
            };

        /// has .toString() const member
        template<typename T>
        concept HasToStringMember = 
            !Stringy<T> &&
            !CanConstructString<T> &&
            requires(const T& t) { { t.toString() }-> Stringy; };

        /// has .to_string() const member
        template<typename T>
        concept HasToStringMember2 = 
            !Stringy<T> &&
            !CanConstructString<T> &&
            !HasToStringMember<T> &&
            requires(const T& t) { { t.to_string() }-> Stringy; };

        /// works with std::to_string()
        template<typename T>
        concept WorksWithStdToString = 
            !Stringy<T> && 
            !CanConstructString<T> &&
            !HasToStringMember<T> && 
            !HasToStringMember2<T> &&
            requires(const T& t) { { std::to_string(t) } -> Stringy; };

        /// toString function overload exists in global namespace and returns std::string
        template<typename T>
        concept ConvertibleToStringGlobal = 
            !Stringy<T> && 
            !CanConstructString<T> &&
            !HasToStringMember<T> && 
            !HasToStringMember2<T> &&
            !WorksWithStdToString<T> &&
            requires(const T& t) { 
                { ::toString(t) } -> std::same_as<std::string>; 
            };

        template<typename T>
        concept _ToStringBasicNoPtr = 
            Stringy<T> || 
            CanConstructString<T> ||
            HasToStringMember<T> ||
            HasToStringMember2<T> ||
            WorksWithStdToString<T> ||
            ConvertibleToStringGlobal<T>;

#ifndef GZ_TO_STRING_NO_VECTORS
        // VECTOR
        /// Type having string-convertible x, y members and sizeof(T) == 2 * sizeof(x)
        template<typename T>
        concept Vector2ConvertibleToString = !_ToStringBasicNoPtr<T> && 
            requires(T t) { 
                { t.x } -> _ToStringBasicNoPtr; 
                { t.y } -> _ToStringBasicNoPtr; 
                requires sizeof(t.x) * 2 == sizeof(T);
            };
        /// Type having string-convertible x, y, z members and sizeof(T) == 3 * sizeof(x)
        template<typename T>
        concept Vector3ConvertibleToString = !_ToStringBasicNoPtr<T> && 
            requires(T t) { 
                { t.x } -> _ToStringBasicNoPtr; 
                { t.y } -> _ToStringBasicNoPtr; 
                { t.z } -> _ToStringBasicNoPtr; 
                requires sizeof(t.x) * 3 == sizeof(T);
            };
        /// Type having string-convertible x, y, z, w members and sizeof(T) == 4 * sizeof(x)
        template<typename T>
        concept Vector4ConvertibleToString = !_ToStringBasicNoPtr<T> && 
            requires(T t) { 
                { t.x } -> _ToStringBasicNoPtr; 
                { t.y } -> _ToStringBasicNoPtr; 
                { t.z } -> _ToStringBasicNoPtr; 
                { t.w } -> _ToStringBasicNoPtr; 
                requires sizeof(t.x) * 4 == sizeof(T);
            };

        /// Type having string-convertible width, height members and sizeof(T) == 2 * sizeof(width)
        template<typename T>
        concept Extent2DConvertibleToString = !_ToStringBasicNoPtr<T> && 
            requires(T t) { 
                { t.width } -> _ToStringBasicNoPtr; 
                { t.height } -> _ToStringBasicNoPtr; 
                requires sizeof(t.width) * 2 == sizeof(T);
            };
        /// Type having string-convertible width, height, depth members and sizeof(T) == 3 * sizeof(width)
        template<typename T>
        concept Extent3DConvertibleToString = !_ToStringBasicNoPtr<T> && 
            requires(T t) { 
                { t.width } -> _ToStringBasicNoPtr; 
                { t.height } -> _ToStringBasicNoPtr; 
                { t.depth } -> _ToStringBasicNoPtr; 
                requires sizeof(t.width) * 3 == sizeof(T);
            };
#endif 

        template<typename T>
        concept _ToStringBasicOrVectorNoPtr = 
            _ToStringBasicNoPtr<T> 
#ifndef GZ_TO_STRING_NO_VECTORS
            || Vector2ConvertibleToString<T> ||
            Vector3ConvertibleToString<T> ||
            Vector4ConvertibleToString<T> ||
            Extent2DConvertibleToString<T> ||
            Extent3DConvertibleToString<T>
#endif
            ;

        template<typename T>
        concept PtrToToStringBasicOrVector = 
            !_ToStringBasicOrVectorNoPtr<T> &&
            _ToStringBasicOrVectorNoPtr<std::remove_pointer_t<T>>;
    /// @}
}  // namespace gz::util


namespace gz {
    /**
     * @name 1) Converting a type to string
     * @details
     *  All toString functions for types that satisfy util::ToStringBasicNoPtr or util::PtrToToStringBasicType
     * @{
     */
        /**
         * @brief Return the string
         * @returns static_cast<std::string>(t)
         */
        template<util::Stringy T>
        inline std::string toString(const T& t) {
            return static_cast<std::string>(t);
        }

        /**
         * @brief Construct a string from a string like-type
         * @returns std::string(t)
         */
        template<util::CanConstructString T>
        inline std::string toString(const T& t) {
            return std::string(t);
        }

        /**
         * @overload
         * @brief Construct a string from a type having a toString() const member function
         * @returns t.toString()
         */
        template<util::HasToStringMember T>
        inline std::string toString(const T& t) {
            return t.toString();
        }

        /**
         * @overload
         * @brief Construct a string from a type having a to_string() const member function
         * @returns t.to_string()
         */
        template<util::HasToStringMember2 T>
        inline std::string toString(const T& t) {
            return t.to_string();
        }

        /**
         * @overload
         * @brief Construct a string from a number
         * @returns std::to_string(t)
         */
        template<util::WorksWithStdToString T>
        inline std::string toString(const T& t) requires (!std::same_as<T, bool>) {
            return std::to_string(t);
        }

        /**
         * @brief Construct a string from a boolean
         * @details
         *  Unlike std::to_string(bool), which returns 0 or 1, this function returns "true" or "false"
         * @returns "true" or "false"
         */
        template<std::same_as<bool> T>
        inline std::string toString(const T& b) {
            return b ? "true" : "false";
        }

        /**
         * @overload
         * @brief Construct a string from a type that has toString declared in global namespace
         */
        template<util::ConvertibleToStringGlobal T>
        inline std::string toString(const T& t) {
            return ::toString(t);
        }

#ifndef GZ_TO_STRING_NO_VECTORS
        /**
         * @overload
         * @brief Construct a string from a vector with x, y members
         * @returns ( x, y )
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
         * @returns ( x, y, z )
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
         * @returns ( x, y, z, w )
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
         * @brief Construct a string from a type having width and height members
         * @returns ( width, height )
         */
        template<util::Extent2DConvertibleToString T>
        inline std::string toString(const T& t) {
            std::string s = "( ";
            s += toString(t.width) + ", ";
            s += toString(t.height) + " ) ";
            return s;
        }

        /**
         * @overload
         * @brief Construct a string from a type having width and height members
         * @returns ( width, height, depth )
         */
        template<util::Extent3DConvertibleToString T>
        inline std::string toString(const T& t) {
            std::string s = "( ";
            s += toString(t.width) + ", ";
            s += toString(t.height) + ", ";
            s += toString(t.depth) + " ) ";
            return s;
        }
#endif

        /**
         * @overload
         * @brief Construct a string from the element the pointer points at
         * @returns *t
         */
        template<util::PtrToToStringBasicOrVector T>
        inline std::string toString(const T& t) {
            return toString(*t);        
        }

        /**
         * @overload
         * @brief Construct a string from the address of the void*
         * @returns toString(reinterpret_cast<uint64_t>(voidPtr))
         */
        inline std::string toString(const void* const voidPtr) {
            return toString(reinterpret_cast<uint64_t>(voidPtr));        
        }
}  // namespace gz



namespace gz::util {
    /**
     * @name 2) concepts for containers that hold toString() compatible types
     * @{
     */
        /// Everything that is convertible to string with toString at this point
        template<typename T>
        concept _ConvertibleToString = 
            requires (const T& t) {
                { gz::toString(t) } -> std::same_as<std::string>;
            };
            

        // CONTAINER
        /// Forward range having string-convertible elements
        template<typename T>
        concept ForwardRangeConvertibleToString = !_ConvertibleToString<T> and std::ranges::forward_range<T> and _ConvertibleToString<std::ranges::range_value_t<T>>;

        template<typename T>
        concept _TypeOrForwardRangeConvertibleToString = _ConvertibleToString<T> || ForwardRangeConvertibleToString<T>;

        /// Pair having string-convertible elements
        template<typename T>
        concept PairConvertibleToString = !ForwardRangeConvertibleToString<T> and requires(const T& p) { 
            requires _TypeOrForwardRangeConvertibleToString<decltype(p.first)>;
            requires _TypeOrForwardRangeConvertibleToString<decltype(p.second)>;
        };

        /// Container having string-convertible pairs
        template<typename T>
        concept MapConvertibleToString = !PairConvertibleToString<T> and !_TypeOrForwardRangeConvertibleToString<T> and
            std::ranges::forward_range<T> and PairConvertibleToString<std::ranges::range_reference_t<T>>;

        template<typename T>
        concept _ContainerTypeConvertibleToString = PairConvertibleToString<T> || ForwardRangeConvertibleToString<T> || MapConvertibleToString<T>;
    /// @}

}  // namespace gz::util



namespace gz {
    /**
     * @name 2) Converting a container to string
     * @details
     *  All toString functions for types that satisfy util::_ContainerTypeConvertibleToString
     * @{
     */
        /**
         * @overload
         * @brief Construct a string from a forward range
         * @returns [ x1, x2, ... ]
         */
        template<util::ForwardRangeConvertibleToString T>
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
         * @returns ( first, second )
         */
        template<util::PairConvertibleToString T>
        inline std::string toString(const T& t) {
            return "( " + toString(t.first) + ", " + toString(t.second) + " )";
        }

        /**
         * @overload
         * @brief Construct a string from a forward range holding a pair, eg a map
         * @returns { first: second, first: second, ... }
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
    /// @}

    /**
     * @brief Any type where gz::toString(t) exists
     */  
    template<typename T>
    concept ConvertibleToString =
        requires (const T& t) {
            { gz::toString(t) } -> std::same_as<std::string>;
        };
}  // namespace gz

/**
 * @file
 * @brief Contains functions to convert types to string
 */
