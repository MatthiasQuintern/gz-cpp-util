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
	class rvec3;
	template<Number T>
	class rvec4;
	template<Number T>
	class vec2;

	/**
	 * @brief Class containing 2 numbers
	 */
 	template<Number T>
	class rvec2 {
	    public:
			/// just to satisfy concept RowVector
			using isRowVector = T;
		// Constructors
			/// Default constructor
			constexpr rvec2()
				 : x(0), y(0) {}
			/// Create from scalar, all components will have value n
			template<Number N>
			constexpr rvec2(const N n)
				 : x(static_cast<T>(n)), y(static_cast<T>(n)) {}
			/// Create from n n 
			template<Number N1, Number N2>
			constexpr rvec2(N1 n1, N2 n2)
				 : x(static_cast<T>(n1)), y(static_cast<T>(n2)) {}
			/// Create from vec2 
			template<Vector2 V1>
			constexpr rvec2(const V1& v1)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)) {}
		// Values
			T x;
			T y;
		// Assignment
			/// Component-wise assignment
			template<Number N>
			constexpr void operator=(const rvec2<N>& other);
			/// Assignment from scalar
			template<Number N>
			constexpr void operator=(const N& other);
	// Arithmetic
		// Vectorial
			/// Component-wise +
			template<RowVector2 R>
			constexpr rvec2<T> operator+(const R& other) const;
			/// Component-wise -
			template<RowVector2 R>
			constexpr rvec2<T> operator-(const R& other) const;
			/// Component-wise %
			template<RowVector2 R>
			constexpr rvec2<T> operator%(const R& other) const;
			/// Component-wise *
			template<RowVector2 R>
			constexpr rvec2<T> compWiseMult(const R& other) const;
			/// Component-wise /
			template<RowVector2 R>
			constexpr rvec2<T> compWiseDiv(const R& other) const;
			/// Component-wise assignment +=
			template<RowVector2 R>
			constexpr void operator+=(const R& other);
			/// Component-wise assignment -=
			template<RowVector2 R>
			constexpr void operator-=(const R& other);
			/// Component-wise assignment %=
			template<RowVector2 R>
			constexpr void operator%=(const R& other);
			/// Component-wise assignment *=
			template<RowVector2 R>
			constexpr void compWiseAssMult(const R& other);
			/// Component-wise assignment /=
			template<RowVector2 R>
			constexpr void compWiseAssDiv(const R& other);
		// Scalar
			/// Component-wise + with scalar
			template<Number N>
			constexpr rvec2<T> operator+(const N& other) const;
			/// Component-wise - with scalar
			template<Number N>
			constexpr rvec2<T> operator-(const N& other) const;
			/// Component-wise % with scalar
			template<Number N>
			constexpr rvec2<T> operator%(const N& other) const;
			/// Component-wise * with scalar
			template<Number N>
			constexpr rvec2<T> compWiseMult(const N& other) const;
			/// Component-wise / with scalar
			template<Number N>
			constexpr rvec2<T> compWiseDiv(const N& other) const;
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
			/// Matrix multiplication with mat2x2 -> rvec2
			template<Mat2x2 M>
			constexpr rvec2<T> operator*(const M& other) const;
			/// Matrix multiplication with mat2x3 -> rvec3
			template<Mat2x3 M>
			constexpr rvec3<T> operator*(const M& other) const;
			/// Matrix multiplication with mat2x4 -> rvec4
			template<Mat2x4 M>
			constexpr rvec4<T> operator*(const M& other) const;
	// Comparison
		// Vectorial
			/// Component-wise comparison == (and)
			template<RowVector2 R>
			constexpr bool operator==(const R& other) const;
			/// Component-wise comparison < (and)
			template<RowVector2 R>
			constexpr bool operator<(const R& other) const;
			/// Component-wise comparison > (and)
			template<RowVector2 R>
			constexpr bool operator>(const R& other) const;
			/// Component-wise comparison != (and)
			template<RowVector2 R>
			constexpr bool operator!=(const R& other) const;
			/// Component-wise comparison <= (and)
			template<RowVector2 R>
			constexpr bool operator<=(const R& other) const;
			/// Component-wise comparison >= (and)
			template<RowVector2 R>
			constexpr bool operator>=(const R& other) const;
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
			constexpr inline T dot(const rvec2<N>& other) const;
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
	}; // rvec2

	using rvec2f = rvec2<float>;
	using rvec2d = rvec2<double>;
	using rvec2i = rvec2<int>;
	using rvec2u = rvec2<unsigned int>;


	static_assert(RowVector2<rvec2<int>>, "rvec2<int> does not satisfy the concept RowVector2");
} // namespace gz
