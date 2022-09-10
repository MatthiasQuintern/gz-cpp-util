#pragma once

#include "concepts.hpp"
#include "../container/iterator.hpp"

namespace gz {

	// Forward declarations
	template<Number T>
	class mat2x2;
	template<Number T>
	class mat2x3;
	template<Number T>
	class mat2x4;
	template<Number T>
	class rvec2;
	template<Number T>
	class rvec3;
	template<Number T>
	class rvec4;

	/**
	 * @brief Class containing 2 numbers
	 */
 	template<Number T>
	class vec2 {
	    public:
			/// just to satisfy concept ColumnVector
			using isColumnVector = T;
		// Constructors
			/// Default constructor
			constexpr vec2()
				 : x(0), y(0) {}
			/// Create from scalar, all components will have value n
			template<Number N>
			constexpr vec2(const N n)
				 : x(static_cast<T>(n)), y(static_cast<T>(n)) {}
			/// Create from n n 
			template<Number N1, Number N2>
			constexpr vec2(N1 n1, N2 n2)
				 : x(static_cast<T>(n1)), y(static_cast<T>(n2)) {}
			/// Create from vec2 
			template<Vector2 V1>
			constexpr vec2(const V1& v1)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)) {}
		// Values
			T x;
			T y;
		// Assignment
			/// Component-wise assignment
			template<Number N>
			constexpr void operator=(const vec2<N>& other);
			/// Assignment from scalar
			template<Number N>
			constexpr void operator=(const N& other);
	// Arithmetic
		// Vectorial
			/// Component-wise +
			template<ColumnVector2 C>
			constexpr vec2<T> operator+(const C& other) const;
			/// Component-wise -
			template<ColumnVector2 C>
			constexpr vec2<T> operator-(const C& other) const;
			/// Component-wise %
			template<ColumnVector2 C>
			constexpr vec2<T> operator%(const C& other) const;
			/// Component-wise *
			template<ColumnVector2 C>
			constexpr vec2<T> compWiseMult(const C& other) const;
			/// Component-wise /
			template<ColumnVector2 C>
			constexpr vec2<T> compWiseDiv(const C& other) const;
			/// Component-wise assignment +=
			template<ColumnVector2 C>
			constexpr void operator+=(const C& other);
			/// Component-wise assignment -=
			template<ColumnVector2 C>
			constexpr void operator-=(const C& other);
			/// Component-wise assignment %=
			template<ColumnVector2 C>
			constexpr void operator%=(const C& other);
			/// Component-wise assignment *=
			template<ColumnVector2 C>
			constexpr void compWiseAssMult(const C& other);
			/// Component-wise assignment /=
			template<ColumnVector2 C>
			constexpr void compWiseAssDiv(const C& other);
		// Scalar
			/// Component-wise + with scalar
			template<Number N>
			constexpr vec2<T> operator+(const N& other) const;
			/// Component-wise - with scalar
			template<Number N>
			constexpr vec2<T> operator-(const N& other) const;
			/// Component-wise % with scalar
			template<Number N>
			constexpr vec2<T> operator%(const N& other) const;
			/// Component-wise * with scalar
			template<Number N>
			constexpr vec2<T> compWiseMult(const N& other) const;
			/// Component-wise / with scalar
			template<Number N>
			constexpr vec2<T> compWiseDiv(const N& other) const;
			/// Component-wise assignment += from scalar
			template<Number N>
			constexpr void operator+=(const N& other);
			/// Component-wise assignment -= from scalar
			template<Number N>
			constexpr void operator-=(const N& other);
			/// Component-wise assignment %= from scalar
			template<Number N>
			constexpr void operator%=(const N& other);
			/// Component-wise assignment *= from scalar
			template<Number N>
			constexpr void compWiseAssMult(const N& other);
			/// Component-wise assignment /= from scalar
			template<Number N>
			constexpr void compWiseAssDiv(const N& other);
		// Matrix Multiplication
			/// Matrix multiplication with rvec2 -> mat2x2
			template<RowVector2 R>
			constexpr mat2x2<T> operator*(const R& other) const;
			/// Matrix multiplication with rvec3 -> mat2x3
			template<RowVector3 R>
			constexpr mat2x3<T> operator*(const R& other) const;
			/// Matrix multiplication with rvec4 -> mat2x4
			template<RowVector4 R>
			constexpr mat2x4<T> operator*(const R& other) const;
	// Comparison
		// Vectorial
			/// Component-wise comparison == (and)
			template<ColumnVector2 C>
			constexpr bool operator==(const C& other) const;
			/// Component-wise comparison < (and)
			template<ColumnVector2 C>
			constexpr bool operator<(const C& other) const;
			/// Component-wise comparison > (and)
			template<ColumnVector2 C>
			constexpr bool operator>(const C& other) const;
			/// Component-wise comparison != (and)
			template<ColumnVector2 C>
			constexpr bool operator!=(const C& other) const;
			/// Component-wise comparison <= (and)
			template<ColumnVector2 C>
			constexpr bool operator<=(const C& other) const;
			/// Component-wise comparison >= (and)
			template<ColumnVector2 C>
			constexpr bool operator>=(const C& other) const;
		// Scalar
			/// Component-wise comparison == (and)
			template<Number N>
			constexpr bool operator==(const N& other) const;
			/// Component-wise comparison < (and)
			template<Number N>
			constexpr bool operator<(const N& other) const;
			/// Component-wise comparison > (and)
			template<Number N>
			constexpr bool operator>(const N& other) const;
			/// Component-wise comparison != (and)
			template<Number N>
			constexpr bool operator!=(const N& other) const;
			/// Component-wise comparison <= (and)
			template<Number N>
			constexpr bool operator<=(const N& other) const;
			/// Component-wise comparison >= (and)
			template<Number N>
			constexpr bool operator>=(const N& other) const;
	// Functional
			/// Returns the absolute value of the vector (sqrt of scalar product with itself)
			constexpr inline float abs() const;
			/// Returns x/y
			constexpr inline float ratio() const;
			/// Returns y/x
			constexpr inline float invereseRatio() const;
			/// Returns the min of the components
			constexpr inline T min() const;
			/// Returns the max of the components
			constexpr inline T max() const;
			/// Scalar product (x1 * other.x1 +  x2 * other.x2 ...)
			template<Number N>
			constexpr inline T dot(const vec2<N>& other) const;
	// Utility
			/// Get the ith element. i starts at 0
			constexpr T operator[](std::size_t i) const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> cbegin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> cend() const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> begin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> end() const;
	}; // vec2

	using vec2f = vec2<float>;
	using vec2d = vec2<double>;
	using vec2i = vec2<int>;
	using vec2u = vec2<unsigned int>;


	static_assert(ColumnVector2<vec2<int>>, "vec2<int> does not satisfy the concept ColumnVector2");
} // namespace gz
