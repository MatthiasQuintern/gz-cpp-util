#pragma once

#include "concepts.hpp"
#include "../container/iterator.hpp"

namespace gz {

	// Forward declarations
	template<Number T>
	class mat2x2;
	template<Number T>
	class mat2x4;
	template<Number T>
	class mat3x2;
	template<Number T>
	class mat3x3;
	template<Number T>
	class mat3x4;
	template<Number T>
	class rvec3;
	template<Number T>
	class vec2;
	template<Number T>
	class vec3;

	/**
	 * @brief Class containing 6 numbers
	 */
 	template<Number T>
	class mat2x3 {
	    public:
		// Constructors
			/// Default constructor
			constexpr mat2x3()
				 : x1_1(0), x1_2(0), x1_3(0), x2_1(0), x2_2(0), x2_3(0) {}
			/// Create from scalar, all components will have value n
			template<Number N>
			constexpr mat2x3(const N n)
				 : x1_1(static_cast<T>(n)), x1_2(static_cast<T>(n)), x1_3(static_cast<T>(n)), x2_1(static_cast<T>(n)), x2_2(static_cast<T>(n)), x2_3(static_cast<T>(n)) {}
			/// Create from scalars
			template<Number N0_0, Number N0_1, Number N0_2, Number N1_0, Number N1_1, Number N1_2>
			constexpr mat2x3(const N0_0 x1_1, const N0_1 x1_2, const N0_2 x1_3, const N1_0 x2_1, const N1_1 x2_2, const N1_2 x2_3)
				 : x1_1(static_cast<T>(x1_1)), x1_2(static_cast<T>(x1_2)), x1_3(static_cast<T>(x1_3)), x2_1(static_cast<T>(x2_1)), x2_2(static_cast<T>(x2_2)), x2_3(static_cast<T>(x2_3)) {}
			/// Create from row vectors
			template<RowVector3 V0, RowVector3 V1>
			constexpr mat2x3(const V0& v0, const V1& v1)
				 : x1_1(static_cast<T>(v0.x)), x1_2(static_cast<T>(v0.y)), x1_3(static_cast<T>(v0.z)), x2_1(static_cast<T>(v1.x)), x2_2(static_cast<T>(v1.y)), x2_3(static_cast<T>(v1.z)) {}
			/// Create from column vectors
			template<ColumnVector2 V0, ColumnVector2 V1, ColumnVector2 V2>
			constexpr mat2x3(const V0& v0, const V1& v1, const V2& v2)
				 : x1_1(static_cast<T>(v0.x)), x1_2(static_cast<T>(v1.x)), x1_3(static_cast<T>(v2.x)), x2_1(static_cast<T>(v0.y)), x2_2(static_cast<T>(v1.y)), x2_3(static_cast<T>(v2.y)) {}
		// Values
			T x1_1;
			T x1_2;
			T x1_3;
			T x2_1;
			T x2_2;
			T x2_3;
		// Assignment
			/// Component-wise assignment
			template<Number N>
			constexpr void operator=(const mat2x3<N>& other);
			/// Assignment from scalar
			template<Number N>
			constexpr void operator=(const N& other);
	// Arithmetic
		// Vectorial
			/// Component-wise +
			template<Mat2x3 M>
			constexpr mat2x3<T> operator+(const M& other) const;
			/// Component-wise -
			template<Mat2x3 M>
			constexpr mat2x3<T> operator-(const M& other) const;
			/// Component-wise %
			template<Mat2x3 M>
			constexpr mat2x3<T> operator%(const M& other) const;
			/// Component-wise *
			template<Mat2x3 M>
			constexpr mat2x3<T> compWiseMult(const M& other) const;
			/// Component-wise /
			template<Mat2x3 M>
			constexpr mat2x3<T> compWiseDiv(const M& other) const;
			/// Component-wise assignment +=
			template<Mat2x3 M>
			constexpr void operator+=(const M& other);
			/// Component-wise assignment -=
			template<Mat2x3 M>
			constexpr void operator-=(const M& other);
			/// Component-wise assignment %=
			template<Mat2x3 M>
			constexpr void operator%=(const M& other);
			/// Component-wise assignment *=
			template<Mat2x3 M>
			constexpr void compWiseAssMult(const M& other);
			/// Component-wise assignment /=
			template<Mat2x3 M>
			constexpr void compWiseAssDiv(const M& other);
		// Scalar
			/// Component-wise + with scalar
			template<Number N>
			constexpr mat2x3<T> operator+(const N& other) const;
			/// Component-wise - with scalar
			template<Number N>
			constexpr mat2x3<T> operator-(const N& other) const;
			/// Component-wise % with scalar
			template<Number N>
			constexpr mat2x3<T> operator%(const N& other) const;
			/// Component-wise * with scalar
			template<Number N>
			constexpr mat2x3<T> compWiseMult(const N& other) const;
			/// Component-wise / with scalar
			template<Number N>
			constexpr mat2x3<T> compWiseDiv(const N& other) const;
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
			/// Matrix multiplication with vec3 -> vec2
			template<ColumnVector3 C>
			constexpr vec2<T> operator*(const C& other) const;
			/// Matrix multiplication with mat3x2 -> mat2x2
			template<Mat3x2 M>
			constexpr mat2x2<T> operator*(const M& other) const;
			/// Matrix multiplication with mat3x3 -> mat2x3
			template<Mat3x3 M>
			constexpr mat2x3<T> operator*(const M& other) const;
			/// Matrix multiplication with mat3x4 -> mat2x4
			template<Mat3x4 M>
			constexpr mat2x4<T> operator*(const M& other) const;
	// Comparison
		// Vectorial
			/// Component-wise comparison == (and)
			template<Mat2x3 M>
			constexpr bool operator==(const M& other) const;
			/// Component-wise comparison < (and)
			template<Mat2x3 M>
			constexpr bool operator<(const M& other) const;
			/// Component-wise comparison > (and)
			template<Mat2x3 M>
			constexpr bool operator>(const M& other) const;
			/// Component-wise comparison != (and)
			template<Mat2x3 M>
			constexpr bool operator!=(const M& other) const;
			/// Component-wise comparison <= (and)
			template<Mat2x3 M>
			constexpr bool operator<=(const M& other) const;
			/// Component-wise comparison >= (and)
			template<Mat2x3 M>
			constexpr bool operator>=(const M& other) const;
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
			/// Returns the min of the components
			constexpr inline T min() const;
			/// Returns the max of the components
			constexpr inline T max() const;
			/// Scalar product (x1 * other.x1 +  x2 * other.x2 ...)
			template<Number N>
			constexpr inline T dot(const mat2x3<N>& other) const;
	// Utility
			/// Get the ith element. i starts at 0
			constexpr T operator[](std::size_t i) const;
			/// Get the element at row and col. row and col start at 0
			constexpr T at(std::size_t row, std::size_t col) const;
			/// Get the ith row as column vector. i starts at 0
			constexpr rvec3<T> row(std::size_t i) const;
			/// Get the ith column as row vector. i starts at 0
			constexpr vec2<T> column(std::size_t i) const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> cbegin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> cend() const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> begin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> end() const;
	}; // mat2x3

	using mat2x3f = mat2x3<float>;
	using mat2x3d = mat2x3<double>;
	using mat2x3i = mat2x3<int>;
	using mat2x3u = mat2x3<unsigned int>;


	static_assert(Mat2x3<mat2x3<int>>, "mat2x3<int> does not satisfy the concept Mat2x3");
} // namespace gz
