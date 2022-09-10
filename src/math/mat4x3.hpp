#pragma once

#include "concepts.hpp"
#include "../container/iterator.hpp"

namespace gz {

	// Forward declarations
	template<Number T>
	class mat3x2;
	template<Number T>
	class mat3x3;
	template<Number T>
	class mat3x4;
	template<Number T>
	class mat4x2;
	template<Number T>
	class mat4x4;
	template<Number T>
	class rvec3;
	template<Number T>
	class vec3;
	template<Number T>
	class vec4;

	/**
	 * @brief Class containing 12 numbers
	 */
 	template<Number T>
	class mat4x3 {
	    public:
		// Constructors
			/// Default constructor
			constexpr mat4x3()
				 : x1_1(0), x1_2(0), x1_3(0), x2_1(0), x2_2(0), x2_3(0), x3_1(0), x3_2(0), x3_3(0), x4_1(0), x4_2(0), x4_3(0) {}
			/// Create from scalar, all components will have value n
			template<Number N>
			constexpr mat4x3(const N n)
				 : x1_1(static_cast<T>(n)), x1_2(static_cast<T>(n)), x1_3(static_cast<T>(n)), x2_1(static_cast<T>(n)), x2_2(static_cast<T>(n)), x2_3(static_cast<T>(n)), x3_1(static_cast<T>(n)), x3_2(static_cast<T>(n)), x3_3(static_cast<T>(n)), x4_1(static_cast<T>(n)), x4_2(static_cast<T>(n)), x4_3(static_cast<T>(n)) {}
			/// Create from scalars
			template<Number N0_0, Number N0_1, Number N0_2, Number N1_0, Number N1_1, Number N1_2, Number N2_0, Number N2_1, Number N2_2, Number N3_0, Number N3_1, Number N3_2>
			constexpr mat4x3(const N0_0 x1_1, const N0_1 x1_2, const N0_2 x1_3, const N1_0 x2_1, const N1_1 x2_2, const N1_2 x2_3, const N2_0 x3_1, const N2_1 x3_2, const N2_2 x3_3, const N3_0 x4_1, const N3_1 x4_2, const N3_2 x4_3)
				 : x1_1(static_cast<T>(x1_1)), x1_2(static_cast<T>(x1_2)), x1_3(static_cast<T>(x1_3)), x2_1(static_cast<T>(x2_1)), x2_2(static_cast<T>(x2_2)), x2_3(static_cast<T>(x2_3)), x3_1(static_cast<T>(x3_1)), x3_2(static_cast<T>(x3_2)), x3_3(static_cast<T>(x3_3)), x4_1(static_cast<T>(x4_1)), x4_2(static_cast<T>(x4_2)), x4_3(static_cast<T>(x4_3)) {}
			/// Create from row vectors
			template<RowVector3 V0, RowVector3 V1, RowVector3 V2, RowVector3 V3>
			constexpr mat4x3(const V0& v0, const V1& v1, const V2& v2, const V3& v3)
				 : x1_1(static_cast<T>(v0.x)), x1_2(static_cast<T>(v0.y)), x1_3(static_cast<T>(v0.z)), x2_1(static_cast<T>(v1.x)), x2_2(static_cast<T>(v1.y)), x2_3(static_cast<T>(v1.z)), x3_1(static_cast<T>(v2.x)), x3_2(static_cast<T>(v2.y)), x3_3(static_cast<T>(v2.z)), x4_1(static_cast<T>(v3.x)), x4_2(static_cast<T>(v3.y)), x4_3(static_cast<T>(v3.z)) {}
			/// Create from column vectors
			template<ColumnVector4 V0, ColumnVector4 V1, ColumnVector4 V2>
			constexpr mat4x3(const V0& v0, const V1& v1, const V2& v2)
				 : x1_1(static_cast<T>(v0.x)), x1_2(static_cast<T>(v1.x)), x1_3(static_cast<T>(v2.x)), x2_1(static_cast<T>(v0.y)), x2_2(static_cast<T>(v1.y)), x2_3(static_cast<T>(v2.y)), x3_1(static_cast<T>(v0.z)), x3_2(static_cast<T>(v1.z)), x3_3(static_cast<T>(v2.z)), x4_1(static_cast<T>(v0.w)), x4_2(static_cast<T>(v1.w)), x4_3(static_cast<T>(v2.w)) {}
		// Values
			T x1_1;
			T x1_2;
			T x1_3;
			T x2_1;
			T x2_2;
			T x2_3;
			T x3_1;
			T x3_2;
			T x3_3;
			T x4_1;
			T x4_2;
			T x4_3;
		// Assignment
			/// Component-wise assignment
			template<Number N>
			constexpr void operator=(const mat4x3<N>& other);
			/// Assignment from scalar
			template<Number N>
			constexpr void operator=(const N& other);
	// Arithmetic
		// Vectorial
			/// Component-wise +
			template<Mat4x3 M>
			constexpr mat4x3<T> operator+(const M& other) const;
			/// Component-wise -
			template<Mat4x3 M>
			constexpr mat4x3<T> operator-(const M& other) const;
			/// Component-wise %
			template<Mat4x3 M>
			constexpr mat4x3<T> operator%(const M& other) const;
			/// Component-wise *
			template<Mat4x3 M>
			constexpr mat4x3<T> compWiseMult(const M& other) const;
			/// Component-wise /
			template<Mat4x3 M>
			constexpr mat4x3<T> compWiseDiv(const M& other) const;
			/// Component-wise assignment +=
			template<Mat4x3 M>
			constexpr void operator+=(const M& other);
			/// Component-wise assignment -=
			template<Mat4x3 M>
			constexpr void operator-=(const M& other);
			/// Component-wise assignment %=
			template<Mat4x3 M>
			constexpr void operator%=(const M& other);
			/// Component-wise assignment *=
			template<Mat4x3 M>
			constexpr void compWiseAssMult(const M& other);
			/// Component-wise assignment /=
			template<Mat4x3 M>
			constexpr void compWiseAssDiv(const M& other);
		// Scalar
			/// Component-wise + with scalar
			template<Number N>
			constexpr mat4x3<T> operator+(const N& other) const;
			/// Component-wise - with scalar
			template<Number N>
			constexpr mat4x3<T> operator-(const N& other) const;
			/// Component-wise % with scalar
			template<Number N>
			constexpr mat4x3<T> operator%(const N& other) const;
			/// Component-wise * with scalar
			template<Number N>
			constexpr mat4x3<T> compWiseMult(const N& other) const;
			/// Component-wise / with scalar
			template<Number N>
			constexpr mat4x3<T> compWiseDiv(const N& other) const;
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
			/// Matrix multiplication with vec3 -> vec4
			template<ColumnVector3 C>
			constexpr vec4<T> operator*(const C& other) const;
			/// Matrix multiplication with mat3x2 -> mat4x2
			template<Mat3x2 M>
			constexpr mat4x2<T> operator*(const M& other) const;
			/// Matrix multiplication with mat3x3 -> mat4x3
			template<Mat3x3 M>
			constexpr mat4x3<T> operator*(const M& other) const;
			/// Matrix multiplication with mat3x4 -> mat4x4
			template<Mat3x4 M>
			constexpr mat4x4<T> operator*(const M& other) const;
	// Comparison
		// Vectorial
			/// Component-wise comparison == (and)
			template<Mat4x3 M>
			constexpr bool operator==(const M& other) const;
			/// Component-wise comparison < (and)
			template<Mat4x3 M>
			constexpr bool operator<(const M& other) const;
			/// Component-wise comparison > (and)
			template<Mat4x3 M>
			constexpr bool operator>(const M& other) const;
			/// Component-wise comparison != (and)
			template<Mat4x3 M>
			constexpr bool operator!=(const M& other) const;
			/// Component-wise comparison <= (and)
			template<Mat4x3 M>
			constexpr bool operator<=(const M& other) const;
			/// Component-wise comparison >= (and)
			template<Mat4x3 M>
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
			constexpr inline T dot(const mat4x3<N>& other) const;
	// Utility
			/// Get the ith element. i starts at 0
			constexpr T operator[](std::size_t i) const;
			/// Get the element at row and col. row and col start at 0
			constexpr T at(std::size_t row, std::size_t col) const;
			/// Get the ith row as column vector. i starts at 0
			constexpr rvec3<T> row(std::size_t i) const;
			/// Get the ith column as row vector. i starts at 0
			constexpr vec4<T> column(std::size_t i) const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> cbegin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> cend() const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> begin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> end() const;
	}; // mat4x3

	using mat4x3f = mat4x3<float>;
	using mat4x3d = mat4x3<double>;
	using mat4x3i = mat4x3<int>;
	using mat4x3u = mat4x3<unsigned int>;


	static_assert(Mat4x3<mat4x3<int>>, "mat4x3<int> does not satisfy the concept Mat4x3");
} // namespace gz
