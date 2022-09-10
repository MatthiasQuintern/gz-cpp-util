#pragma once

#include "concepts.hpp"
#include "../container/iterator.hpp"

namespace gz {

	// Forward declarations
	template<Number T>
	class mat4x2;
	template<Number T>
	class mat4x3;
	template<Number T>
	class mat4x4;
	template<Number T>
	class rvec2;
	template<Number T>
	class rvec3;
	template<Number T>
	class rvec4;

	/**
	 * @brief Class containing 4 numbers
	 */
 	template<Number T>
	class vec4 {
	    public:
			/// just to satisfy concept ColumnVector
			using isColumnVector = T;
		// Constructors
			/// Default constructor
			constexpr vec4()
				 : x(0), y(0), z(0), w(0) {}
			/// Create from scalar, all components will have value n
			template<Number N>
			constexpr vec4(const N n)
				 : x(static_cast<T>(n)), y(static_cast<T>(n)), z(static_cast<T>(n)), w(static_cast<T>(n)) {}
			/// Create from n n n n 
			template<Number N1, Number N2, Number N3, Number N4>
			constexpr vec4(N1 n1, N2 n2, N3 n3, N4 n4)
				 : x(static_cast<T>(n1)), y(static_cast<T>(n2)), z(static_cast<T>(n3)), w(static_cast<T>(n4)) {}
			/// Create from n n vec2 
			template<Number N1, Number N2, Vector4 V1>
			constexpr vec4(N1 n1, N2 n2, const V1& v1)
				 : x(static_cast<T>(n1)), y(static_cast<T>(n2)), z(static_cast<T>(v1.x)), w(static_cast<T>(v1.y)) {}
			/// Create from n vec2 n 
			template<Number N1, Vector4 V1, Number N2>
			constexpr vec4(N1 n1, const V1& v1, N2 n2)
				 : x(static_cast<T>(n1)), y(static_cast<T>(v1.x)), z(static_cast<T>(v1.y)), w(static_cast<T>(n2)) {}
			/// Create from n vec3 
			template<Number N1, Vector4 V1>
			constexpr vec4(N1 n1, const V1& v1)
				 : x(static_cast<T>(n1)), y(static_cast<T>(v1.x)), z(static_cast<T>(v1.y)), w(static_cast<T>(v1.z)) {}
			/// Create from vec2 n n 
			template<Vector4 V1, Number N1, Number N2>
			constexpr vec4(const V1& v1, N1 n1, N2 n2)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)), z(static_cast<T>(n1)), w(static_cast<T>(n2)) {}
			/// Create from vec2 vec2 
			template<Vector4 V1, Vector4 V2>
			constexpr vec4(const V1& v1, const V2& v2)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)), z(static_cast<T>(v2.x)), w(static_cast<T>(v2.y)) {}
			/// Create from vec3 n 
			template<Vector4 V1, Number N1>
			constexpr vec4(const V1& v1, N1 n1)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)), z(static_cast<T>(v1.z)), w(static_cast<T>(n1)) {}
			/// Create from vec4 
			template<Vector4 V1>
			constexpr vec4(const V1& v1)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)), z(static_cast<T>(v1.z)), w(static_cast<T>(v1.w)) {}
		// Values
			T x;
			T y;
			T z;
			T w;
		// Assignment
			/// Component-wise assignment
			template<Number N>
			constexpr void operator=(const vec4<N>& other);
			/// Assignment from scalar
			template<Number N>
			constexpr void operator=(const N& other);
	// Arithmetic
		// Vectorial
			/// Component-wise +
			template<ColumnVector4 C>
			constexpr vec4<T> operator+(const C& other) const;
			/// Component-wise -
			template<ColumnVector4 C>
			constexpr vec4<T> operator-(const C& other) const;
			/// Component-wise %
			template<ColumnVector4 C>
			constexpr vec4<T> operator%(const C& other) const;
			/// Component-wise *
			template<ColumnVector4 C>
			constexpr vec4<T> compWiseMult(const C& other) const;
			/// Component-wise /
			template<ColumnVector4 C>
			constexpr vec4<T> compWiseDiv(const C& other) const;
			/// Component-wise assignment +=
			template<ColumnVector4 C>
			constexpr void operator+=(const C& other);
			/// Component-wise assignment -=
			template<ColumnVector4 C>
			constexpr void operator-=(const C& other);
			/// Component-wise assignment %=
			template<ColumnVector4 C>
			constexpr void operator%=(const C& other);
			/// Component-wise assignment *=
			template<ColumnVector4 C>
			constexpr void compWiseAssMult(const C& other);
			/// Component-wise assignment /=
			template<ColumnVector4 C>
			constexpr void compWiseAssDiv(const C& other);
		// Scalar
			/// Component-wise + with scalar
			template<Number N>
			constexpr vec4<T> operator+(const N& other) const;
			/// Component-wise - with scalar
			template<Number N>
			constexpr vec4<T> operator-(const N& other) const;
			/// Component-wise % with scalar
			template<Number N>
			constexpr vec4<T> operator%(const N& other) const;
			/// Component-wise * with scalar
			template<Number N>
			constexpr vec4<T> compWiseMult(const N& other) const;
			/// Component-wise / with scalar
			template<Number N>
			constexpr vec4<T> compWiseDiv(const N& other) const;
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
			/// Matrix multiplication with rvec2 -> mat4x2
			template<RowVector2 R>
			constexpr mat4x2<T> operator*(const R& other) const;
			/// Matrix multiplication with rvec3 -> mat4x3
			template<RowVector3 R>
			constexpr mat4x3<T> operator*(const R& other) const;
			/// Matrix multiplication with rvec4 -> mat4x4
			template<RowVector4 R>
			constexpr mat4x4<T> operator*(const R& other) const;
	// Comparison
		// Vectorial
			/// Component-wise comparison == (and)
			template<ColumnVector4 C>
			constexpr bool operator==(const C& other) const;
			/// Component-wise comparison < (and)
			template<ColumnVector4 C>
			constexpr bool operator<(const C& other) const;
			/// Component-wise comparison > (and)
			template<ColumnVector4 C>
			constexpr bool operator>(const C& other) const;
			/// Component-wise comparison != (and)
			template<ColumnVector4 C>
			constexpr bool operator!=(const C& other) const;
			/// Component-wise comparison <= (and)
			template<ColumnVector4 C>
			constexpr bool operator<=(const C& other) const;
			/// Component-wise comparison >= (and)
			template<ColumnVector4 C>
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
			/// Returns the min of the components
			constexpr inline T min() const;
			/// Returns the max of the components
			constexpr inline T max() const;
			/// Scalar product (x1 * other.x1 +  x2 * other.x2 ...)
			template<Number N>
			constexpr inline T dot(const vec4<N>& other) const;
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
	}; // vec4

	using vec4f = vec4<float>;
	using vec4d = vec4<double>;
	using vec4i = vec4<int>;
	using vec4u = vec4<unsigned int>;


	static_assert(ColumnVector4<vec4<int>>, "vec4<int> does not satisfy the concept ColumnVector4");
} // namespace gz
