#pragma once

#include<string>
#include <cmath>
#include <algorithm>

namespace gz {
	/**
	 * @brief Class containing 2 numbers
	 */
	template<typename T>
	class vec2 {
	    public:
		// Constructors
			/// Default constructor
			vec2() : x(0), y(0) {};
			/// Create a vec2 from n n 
			template<typename N0, typename N1>
			vec2(N0 n0, N1 n1) : x(static_cast<T>(n0)), y(static_cast<T>(n1)) {};
			/// Create a vec2 from vec2 
			template<typename V0>
			vec2(const vec2<V0>& v0) : x(static_cast<T>(v0.x)), y(static_cast<T>(v0.y)) {};
		// Values
			T x;
			T y;
		// Assignment
			/// component-wise assignment
			template<typename V>
			void operator=(const vec2<V>& other) {
				x = static_cast<T>(other.x);
				y = static_cast<T>(other.y);
			};

			template<typename N>
			void operator=(const N& other) {
				x = static_cast<T>(other);
				y = static_cast<T>(other);
			};

	// Arithmetic
		// Vectorial
			/// component-wise +
			template<typename V>
			vec2<T> operator+(const vec2<V>& other) const { return vec2<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y)); };
			/// component-wise -
			template<typename V>
			vec2<T> operator-(const vec2<V>& other) const { return vec2<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y)); };
			/// component-wise *
			template<typename V>
			vec2<T> operator*(const vec2<V>& other) const { return vec2<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y)); };
			/// component-wise /
			template<typename V>
			vec2<T> operator/(const vec2<V>& other) const { return vec2<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y)); };
			/// component-wise %
			template<typename V>
			vec2<T> operator%(const vec2<V>& other) const { return vec2<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y)); };

			/// component-wise assignment+=
			template<typename V>
			void operator+=(const vec2<V>& other) {
				x += static_cast<T>(other.x);
				y += static_cast<T>(other.y);
			};
			/// component-wise assignment-=
			template<typename V>
			void operator-=(const vec2<V>& other) {
				x -= static_cast<T>(other.x);
				y -= static_cast<T>(other.y);
			};
			/// component-wise assignment*=
			template<typename V>
			void operator*=(const vec2<V>& other) {
				x *= static_cast<T>(other.x);
				y *= static_cast<T>(other.y);
			};
			/// component-wise assignment/=
			template<typename V>
			void operator/=(const vec2<V>& other) {
				x /= static_cast<T>(other.x);
				y /= static_cast<T>(other.y);
			};
			/// component-wise assignment%=
			template<typename V>
			void operator%=(const vec2<V>& other) {
				x %= static_cast<T>(other.x);
				y %= static_cast<T>(other.y);
			};

		// Scalar
			/// component-wise +
			template<typename N>
			vec2<T> operator+(const N& other) const { return vec2<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y)); };
			/// component-wise -
			template<typename N>
			vec2<T> operator-(const N& other) const { return vec2<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y)); };
			/// component-wise *
			template<typename N>
			vec2<T> operator*(const N& other) const { return vec2<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y)); };
			/// component-wise /
			template<typename N>
			vec2<T> operator/(const N& other) const { return vec2<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y)); };
			/// component-wise %
			template<typename N>
			vec2<T> operator%(const N& other) const { return vec2<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y)); };

			/// component-wise assignment+=
			template<typename N>
			void operator+=(const N& other) {
				x += static_cast<T>(other.x);
				y += static_cast<T>(other.y);
			};
			/// component-wise assignment-=
			template<typename N>
			void operator-=(const N& other) {
				x -= static_cast<T>(other.x);
				y -= static_cast<T>(other.y);
			};
			/// component-wise assignment*=
			template<typename N>
			void operator*=(const N& other) {
				x *= static_cast<T>(other.x);
				y *= static_cast<T>(other.y);
			};
			/// component-wise assignment/=
			template<typename N>
			void operator/=(const N& other) {
				x /= static_cast<T>(other.x);
				y /= static_cast<T>(other.y);
			};
			/// component-wise assignment%=
			template<typename N>
			void operator%=(const N& other) {
				x %= static_cast<T>(other.x);
				y %= static_cast<T>(other.y);
			};

	// Comparison
		// Vectorial
			/// component-wise comparison == (and)
			template<typename N>
			bool operator==(const vec2<N>& other) const { return x == other.x and y == other.y; };
			/// component-wise comparison < (and)
			template<typename N>
			bool operator<(const vec2<N>& other) const { return x < other.x and y < other.y; };
			/// component-wise comparison > (and)
			template<typename N>
			bool operator>(const vec2<N>& other) const { return x > other.x and y > other.y; };

			/// component-wise comparison != (and)
			template<typename N>
			bool operator!=(const vec2<N>& other) const { return x == other.x and y == other.y; };
			/// component-wise comparison <= (and)
			template<typename N>
			bool operator<=(const vec2<N>& other) const { return x > other.x and y > other.y; };
			/// component-wise comparison >= (and)
			template<typename N>
			bool operator>=(const vec2<N>& other) const { return x < other.x and y < other.y; };

		// Scalar
			/// component-wise comparison == (and)
			template<typename N>
			bool operator==(const N& other) const { return x == other.x and y == other.y; };
			/// component-wise comparison < (and)
			template<typename N>
			bool operator<(const N& other) const { return x < other.x and y < other.y; };
			/// component-wise comparison > (and)
			template<typename N>
			bool operator>(const N& other) const { return x > other.x and y > other.y; };

			/// component-wise comparison != (and)
			template<typename N>
			bool operator!=(const N& other) const { return x == other.x and y == other.y; };
			/// component-wise comparison <= (and)
			template<typename N>
			bool operator<=(const N& other) const { return x > other.x and y > other.y; };
			/// component-wise comparison >= (and)
			template<typename N>
			bool operator>=(const N& other) const { return x < other.x and y < other.y; };
	// Functional
			/// Returns the absolute value of the vector
			inline float abs() const { return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y)); };/// Returns x/y
			inline float ratio() const { return static_cast<float>(x) / y; };/// Returns y/x
			inline float inverseRatio() const { return static_cast<float>(y) / x; };/// Returns the min of the components
			inline T min() const { return std::min_element(cbegin(), cend()); };
			/// Returns the max of the components
			inline T max() const { return std::max_element(cbegin(), cend()); };
			/// Scalar product
			template<typename V>
			inline vec2<T> dot(const vec2<V>& other) { return vec2<T>(x * static_cast<T>(other.x) + y * static_cast<T>(other.y)); };
	// Utility
			std::string to_string() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; };
			struct Iterator {
			    public:
			        using value_type = T;
			        Iterator() : ptr(nullptr) {};
			        Iterator(T* ptr) : ptr(ptr) {};
			        T& operator*() { return *ptr; };
			        Iterator& operator=(const Iterator& other) {
			            ptr = other.ptr;
			            return *this;
			        };
			        Iterator& operator++() { ptr += sizeof(T); return *this; };
			        Iterator operator++(int) { auto copy = *this; ptr += sizeof(T); return copy; };
			        friend int operator-(Iterator lhs, Iterator rhs) {
			            return lhs.ptr - rhs.ptr;
			        };
			        bool operator==(const Iterator& other) const { return ptr == other.ptr; };
			        // bool operator!=(const Iterator& other) const { return ptr != other.ptr; };
			    private:
			        T* ptr;
			};
			const Iterator cbegin() const { return Iterator(&x); };
			const Iterator cend() const { return Iterator(&y); };
			const Iterator begin() const { return Iterator(&x); };
			const Iterator end() const { return Iterator(&y); };

	}; // vec2

	/**
	 * @brief Class containing 3 numbers
	 */
	template<typename T>
	class vec3 {
	    public:
		// Constructors
			/// Default constructor
			vec3() : x(0), y(0), z(0) {};
			/// Create a vec3 from n n n 
			template<typename N0, typename N1, typename N2>
			vec3(N0 n0, N1 n1, N2 n2) : x(static_cast<T>(n0)), y(static_cast<T>(n1)), z(static_cast<T>(n2)) {};
			/// Create a vec3 from n vec2 
			template<typename N0, typename V0>
			vec3(N0 n0, const vec2<V0>& v0) : x(static_cast<T>(n0)), y(static_cast<T>(v0.x)), z(static_cast<T>(v0.y)) {};
			/// Create a vec3 from vec2 n 
			template<typename V0, typename N0>
			vec3(const vec2<V0>& v0, N0 n0) : x(static_cast<T>(v0.x)), y(static_cast<T>(v0.y)), z(static_cast<T>(n0)) {};
			/// Create a vec3 from vec3 
			template<typename V0>
			vec3(const vec3<V0>& v0) : x(static_cast<T>(v0.x)), y(static_cast<T>(v0.y)), z(static_cast<T>(v0.z)) {};
		// Values
			T x;
			T y;
			T z;
		// Assignment
			/// component-wise assignment
			template<typename V>
			void operator=(const vec3<V>& other) {
				x = static_cast<T>(other.x);
				y = static_cast<T>(other.y);
				z = static_cast<T>(other.z);
			};

			template<typename N>
			void operator=(const N& other) {
				x = static_cast<T>(other);
				y = static_cast<T>(other);
				z = static_cast<T>(other);
			};

	// Arithmetic
		// Vectorial
			/// component-wise +
			template<typename V>
			vec3<T> operator+(const vec3<V>& other) const { return vec3<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y), z + static_cast<T>(other.z)); };
			/// component-wise -
			template<typename V>
			vec3<T> operator-(const vec3<V>& other) const { return vec3<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y), z - static_cast<T>(other.z)); };
			/// component-wise *
			template<typename V>
			vec3<T> operator*(const vec3<V>& other) const { return vec3<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y), z * static_cast<T>(other.z)); };
			/// component-wise /
			template<typename V>
			vec3<T> operator/(const vec3<V>& other) const { return vec3<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y), z / static_cast<T>(other.z)); };
			/// component-wise %
			template<typename V>
			vec3<T> operator%(const vec3<V>& other) const { return vec3<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y), z % static_cast<T>(other.z)); };

			/// component-wise assignment+=
			template<typename V>
			void operator+=(const vec3<V>& other) {
				x += static_cast<T>(other.x);
				y += static_cast<T>(other.y);
				z += static_cast<T>(other.z);
			};
			/// component-wise assignment-=
			template<typename V>
			void operator-=(const vec3<V>& other) {
				x -= static_cast<T>(other.x);
				y -= static_cast<T>(other.y);
				z -= static_cast<T>(other.z);
			};
			/// component-wise assignment*=
			template<typename V>
			void operator*=(const vec3<V>& other) {
				x *= static_cast<T>(other.x);
				y *= static_cast<T>(other.y);
				z *= static_cast<T>(other.z);
			};
			/// component-wise assignment/=
			template<typename V>
			void operator/=(const vec3<V>& other) {
				x /= static_cast<T>(other.x);
				y /= static_cast<T>(other.y);
				z /= static_cast<T>(other.z);
			};
			/// component-wise assignment%=
			template<typename V>
			void operator%=(const vec3<V>& other) {
				x %= static_cast<T>(other.x);
				y %= static_cast<T>(other.y);
				z %= static_cast<T>(other.z);
			};

		// Scalar
			/// component-wise +
			template<typename N>
			vec3<T> operator+(const N& other) const { return vec3<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y), z + static_cast<T>(other.z)); };
			/// component-wise -
			template<typename N>
			vec3<T> operator-(const N& other) const { return vec3<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y), z - static_cast<T>(other.z)); };
			/// component-wise *
			template<typename N>
			vec3<T> operator*(const N& other) const { return vec3<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y), z * static_cast<T>(other.z)); };
			/// component-wise /
			template<typename N>
			vec3<T> operator/(const N& other) const { return vec3<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y), z / static_cast<T>(other.z)); };
			/// component-wise %
			template<typename N>
			vec3<T> operator%(const N& other) const { return vec3<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y), z % static_cast<T>(other.z)); };

			/// component-wise assignment+=
			template<typename N>
			void operator+=(const N& other) {
				x += static_cast<T>(other.x);
				y += static_cast<T>(other.y);
				z += static_cast<T>(other.z);
			};
			/// component-wise assignment-=
			template<typename N>
			void operator-=(const N& other) {
				x -= static_cast<T>(other.x);
				y -= static_cast<T>(other.y);
				z -= static_cast<T>(other.z);
			};
			/// component-wise assignment*=
			template<typename N>
			void operator*=(const N& other) {
				x *= static_cast<T>(other.x);
				y *= static_cast<T>(other.y);
				z *= static_cast<T>(other.z);
			};
			/// component-wise assignment/=
			template<typename N>
			void operator/=(const N& other) {
				x /= static_cast<T>(other.x);
				y /= static_cast<T>(other.y);
				z /= static_cast<T>(other.z);
			};
			/// component-wise assignment%=
			template<typename N>
			void operator%=(const N& other) {
				x %= static_cast<T>(other.x);
				y %= static_cast<T>(other.y);
				z %= static_cast<T>(other.z);
			};

	// Comparison
		// Vectorial
			/// component-wise comparison == (and)
			template<typename N>
			bool operator==(const vec3<N>& other) const { return x == other.x and y == other.y and z == other.z; };
			/// component-wise comparison < (and)
			template<typename N>
			bool operator<(const vec3<N>& other) const { return x < other.x and y < other.y and z < other.z; };
			/// component-wise comparison > (and)
			template<typename N>
			bool operator>(const vec3<N>& other) const { return x > other.x and y > other.y and z > other.z; };

			/// component-wise comparison != (and)
			template<typename N>
			bool operator!=(const vec3<N>& other) const { return x == other.x and y == other.y and z == other.z; };
			/// component-wise comparison <= (and)
			template<typename N>
			bool operator<=(const vec3<N>& other) const { return x > other.x and y > other.y and z > other.z; };
			/// component-wise comparison >= (and)
			template<typename N>
			bool operator>=(const vec3<N>& other) const { return x < other.x and y < other.y and z < other.z; };

		// Scalar
			/// component-wise comparison == (and)
			template<typename N>
			bool operator==(const N& other) const { return x == other.x and y == other.y and z == other.z; };
			/// component-wise comparison < (and)
			template<typename N>
			bool operator<(const N& other) const { return x < other.x and y < other.y and z < other.z; };
			/// component-wise comparison > (and)
			template<typename N>
			bool operator>(const N& other) const { return x > other.x and y > other.y and z > other.z; };

			/// component-wise comparison != (and)
			template<typename N>
			bool operator!=(const N& other) const { return x == other.x and y == other.y and z == other.z; };
			/// component-wise comparison <= (and)
			template<typename N>
			bool operator<=(const N& other) const { return x > other.x and y > other.y and z > other.z; };
			/// component-wise comparison >= (and)
			template<typename N>
			bool operator>=(const N& other) const { return x < other.x and y < other.y and z < other.z; };
	// Functional
			/// Returns the absolute value of the vector
			inline float abs() const { return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y) + static_cast<float>(z * z)); };/// Returns the min of the components
			inline T min() const { return std::min_element(cbegin(), cend()); };
			/// Returns the max of the components
			inline T max() const { return std::max_element(cbegin(), cend()); };
			/// Scalar product
			template<typename V>
			inline vec3<T> dot(const vec3<V>& other) { return vec3<T>(x * static_cast<T>(other.x) + y * static_cast<T>(other.y) + z * static_cast<T>(other.z)); };
	// Utility
			std::string to_string() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")"; };
			struct Iterator {
			    public:
			        using value_type = T;
			        Iterator() : ptr(nullptr) {};
			        Iterator(T* ptr) : ptr(ptr) {};
			        T& operator*() { return *ptr; };
			        Iterator& operator=(const Iterator& other) {
			            ptr = other.ptr;
			            return *this;
			        };
			        Iterator& operator++() { ptr += sizeof(T); return *this; };
			        Iterator operator++(int) { auto copy = *this; ptr += sizeof(T); return copy; };
			        friend int operator-(Iterator lhs, Iterator rhs) {
			            return lhs.ptr - rhs.ptr;
			        };
			        bool operator==(const Iterator& other) const { return ptr == other.ptr; };
			        // bool operator!=(const Iterator& other) const { return ptr != other.ptr; };
			    private:
			        T* ptr;
			};
			const Iterator cbegin() const { return Iterator(&x); };
			const Iterator cend() const { return Iterator(&z); };
			const Iterator begin() const { return Iterator(&x); };
			const Iterator end() const { return Iterator(&z); };

	}; // vec3

	/**
	 * @brief Class containing 4 numbers
	 */
	template<typename T>
	class vec4 {
	    public:
		// Constructors
			/// Default constructor
			vec4() : x(0), y(0), z(0), w(0) {};
			/// Create a vec4 from n n n n 
			template<typename N0, typename N1, typename N2, typename N3>
			vec4(N0 n0, N1 n1, N2 n2, N3 n3) : x(static_cast<T>(n0)), y(static_cast<T>(n1)), z(static_cast<T>(n2)), w(static_cast<T>(n3)) {};
			/// Create a vec4 from n n vec2 
			template<typename N0, typename N1, typename V0>
			vec4(N0 n0, N1 n1, const vec2<V0>& v0) : x(static_cast<T>(n0)), y(static_cast<T>(n1)), z(static_cast<T>(v0.x)), w(static_cast<T>(v0.y)) {};
			/// Create a vec4 from n vec2 n 
			template<typename N0, typename V0, typename N1>
			vec4(N0 n0, const vec2<V0>& v0, N1 n1) : x(static_cast<T>(n0)), y(static_cast<T>(v0.x)), z(static_cast<T>(v0.y)), w(static_cast<T>(n1)) {};
			/// Create a vec4 from n vec3 
			template<typename N0, typename V0>
			vec4(N0 n0, const vec3<V0>& v0) : x(static_cast<T>(n0)), y(static_cast<T>(v0.x)), z(static_cast<T>(v0.y)), w(static_cast<T>(v0.z)) {};
			/// Create a vec4 from vec2 n n 
			template<typename V0, typename N0, typename N1>
			vec4(const vec2<V0>& v0, N0 n0, N1 n1) : x(static_cast<T>(v0.x)), y(static_cast<T>(v0.y)), z(static_cast<T>(n0)), w(static_cast<T>(n1)) {};
			/// Create a vec4 from vec2 vec2 
			template<typename V0, typename V1>
			vec4(const vec2<V0>& v0, const vec2<V1>& v1) : x(static_cast<T>(v0.x)), y(static_cast<T>(v0.y)), z(static_cast<T>(v1.x)), w(static_cast<T>(v1.y)) {};
			/// Create a vec4 from vec3 n 
			template<typename V0, typename N0>
			vec4(const vec3<V0>& v0, N0 n0) : x(static_cast<T>(v0.x)), y(static_cast<T>(v0.y)), z(static_cast<T>(v0.z)), w(static_cast<T>(n0)) {};
			/// Create a vec4 from vec4 
			template<typename V0>
			vec4(const vec4<V0>& v0) : x(static_cast<T>(v0.x)), y(static_cast<T>(v0.y)), z(static_cast<T>(v0.z)), w(static_cast<T>(v0.w)) {};
		// Values
			T x;
			T y;
			T z;
			T w;
		// Assignment
			/// component-wise assignment
			template<typename V>
			void operator=(const vec4<V>& other) {
				x = static_cast<T>(other.x);
				y = static_cast<T>(other.y);
				z = static_cast<T>(other.z);
				w = static_cast<T>(other.w);
			};

			template<typename N>
			void operator=(const N& other) {
				x = static_cast<T>(other);
				y = static_cast<T>(other);
				z = static_cast<T>(other);
				w = static_cast<T>(other);
			};

	// Arithmetic
		// Vectorial
			/// component-wise +
			template<typename V>
			vec4<T> operator+(const vec4<V>& other) const { return vec4<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y), z + static_cast<T>(other.z), w + static_cast<T>(other.w)); };
			/// component-wise -
			template<typename V>
			vec4<T> operator-(const vec4<V>& other) const { return vec4<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y), z - static_cast<T>(other.z), w - static_cast<T>(other.w)); };
			/// component-wise *
			template<typename V>
			vec4<T> operator*(const vec4<V>& other) const { return vec4<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y), z * static_cast<T>(other.z), w * static_cast<T>(other.w)); };
			/// component-wise /
			template<typename V>
			vec4<T> operator/(const vec4<V>& other) const { return vec4<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y), z / static_cast<T>(other.z), w / static_cast<T>(other.w)); };
			/// component-wise %
			template<typename V>
			vec4<T> operator%(const vec4<V>& other) const { return vec4<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y), z % static_cast<T>(other.z), w % static_cast<T>(other.w)); };

			/// component-wise assignment+=
			template<typename V>
			void operator+=(const vec4<V>& other) {
				x += static_cast<T>(other.x);
				y += static_cast<T>(other.y);
				z += static_cast<T>(other.z);
				w += static_cast<T>(other.w);
			};
			/// component-wise assignment-=
			template<typename V>
			void operator-=(const vec4<V>& other) {
				x -= static_cast<T>(other.x);
				y -= static_cast<T>(other.y);
				z -= static_cast<T>(other.z);
				w -= static_cast<T>(other.w);
			};
			/// component-wise assignment*=
			template<typename V>
			void operator*=(const vec4<V>& other) {
				x *= static_cast<T>(other.x);
				y *= static_cast<T>(other.y);
				z *= static_cast<T>(other.z);
				w *= static_cast<T>(other.w);
			};
			/// component-wise assignment/=
			template<typename V>
			void operator/=(const vec4<V>& other) {
				x /= static_cast<T>(other.x);
				y /= static_cast<T>(other.y);
				z /= static_cast<T>(other.z);
				w /= static_cast<T>(other.w);
			};
			/// component-wise assignment%=
			template<typename V>
			void operator%=(const vec4<V>& other) {
				x %= static_cast<T>(other.x);
				y %= static_cast<T>(other.y);
				z %= static_cast<T>(other.z);
				w %= static_cast<T>(other.w);
			};

		// Scalar
			/// component-wise +
			template<typename N>
			vec4<T> operator+(const N& other) const { return vec4<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y), z + static_cast<T>(other.z), w + static_cast<T>(other.w)); };
			/// component-wise -
			template<typename N>
			vec4<T> operator-(const N& other) const { return vec4<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y), z - static_cast<T>(other.z), w - static_cast<T>(other.w)); };
			/// component-wise *
			template<typename N>
			vec4<T> operator*(const N& other) const { return vec4<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y), z * static_cast<T>(other.z), w * static_cast<T>(other.w)); };
			/// component-wise /
			template<typename N>
			vec4<T> operator/(const N& other) const { return vec4<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y), z / static_cast<T>(other.z), w / static_cast<T>(other.w)); };
			/// component-wise %
			template<typename N>
			vec4<T> operator%(const N& other) const { return vec4<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y), z % static_cast<T>(other.z), w % static_cast<T>(other.w)); };

			/// component-wise assignment+=
			template<typename N>
			void operator+=(const N& other) {
				x += static_cast<T>(other.x);
				y += static_cast<T>(other.y);
				z += static_cast<T>(other.z);
				w += static_cast<T>(other.w);
			};
			/// component-wise assignment-=
			template<typename N>
			void operator-=(const N& other) {
				x -= static_cast<T>(other.x);
				y -= static_cast<T>(other.y);
				z -= static_cast<T>(other.z);
				w -= static_cast<T>(other.w);
			};
			/// component-wise assignment*=
			template<typename N>
			void operator*=(const N& other) {
				x *= static_cast<T>(other.x);
				y *= static_cast<T>(other.y);
				z *= static_cast<T>(other.z);
				w *= static_cast<T>(other.w);
			};
			/// component-wise assignment/=
			template<typename N>
			void operator/=(const N& other) {
				x /= static_cast<T>(other.x);
				y /= static_cast<T>(other.y);
				z /= static_cast<T>(other.z);
				w /= static_cast<T>(other.w);
			};
			/// component-wise assignment%=
			template<typename N>
			void operator%=(const N& other) {
				x %= static_cast<T>(other.x);
				y %= static_cast<T>(other.y);
				z %= static_cast<T>(other.z);
				w %= static_cast<T>(other.w);
			};

	// Comparison
		// Vectorial
			/// component-wise comparison == (and)
			template<typename N>
			bool operator==(const vec4<N>& other) const { return x == other.x and y == other.y and z == other.z and w == other.w; };
			/// component-wise comparison < (and)
			template<typename N>
			bool operator<(const vec4<N>& other) const { return x < other.x and y < other.y and z < other.z and w < other.w; };
			/// component-wise comparison > (and)
			template<typename N>
			bool operator>(const vec4<N>& other) const { return x > other.x and y > other.y and z > other.z and w > other.w; };

			/// component-wise comparison != (and)
			template<typename N>
			bool operator!=(const vec4<N>& other) const { return x == other.x and y == other.y and z == other.z and w == other.w; };
			/// component-wise comparison <= (and)
			template<typename N>
			bool operator<=(const vec4<N>& other) const { return x > other.x and y > other.y and z > other.z and w > other.w; };
			/// component-wise comparison >= (and)
			template<typename N>
			bool operator>=(const vec4<N>& other) const { return x < other.x and y < other.y and z < other.z and w < other.w; };

		// Scalar
			/// component-wise comparison == (and)
			template<typename N>
			bool operator==(const N& other) const { return x == other.x and y == other.y and z == other.z and w == other.w; };
			/// component-wise comparison < (and)
			template<typename N>
			bool operator<(const N& other) const { return x < other.x and y < other.y and z < other.z and w < other.w; };
			/// component-wise comparison > (and)
			template<typename N>
			bool operator>(const N& other) const { return x > other.x and y > other.y and z > other.z and w > other.w; };

			/// component-wise comparison != (and)
			template<typename N>
			bool operator!=(const N& other) const { return x == other.x and y == other.y and z == other.z and w == other.w; };
			/// component-wise comparison <= (and)
			template<typename N>
			bool operator<=(const N& other) const { return x > other.x and y > other.y and z > other.z and w > other.w; };
			/// component-wise comparison >= (and)
			template<typename N>
			bool operator>=(const N& other) const { return x < other.x and y < other.y and z < other.z and w < other.w; };
	// Functional
			/// Returns the absolute value of the vector
			inline float abs() const { return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y) + static_cast<float>(z * z) + static_cast<float>(w * w)); };/// Returns the min of the components
			inline T min() const { return std::min_element(cbegin(), cend()); };
			/// Returns the max of the components
			inline T max() const { return std::max_element(cbegin(), cend()); };
			/// Scalar product
			template<typename V>
			inline vec4<T> dot(const vec4<V>& other) { return vec4<T>(x * static_cast<T>(other.x) + y * static_cast<T>(other.y) + z * static_cast<T>(other.z) + w * static_cast<T>(other.w)); };
	// Utility
			std::string to_string() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")"; };
			struct Iterator {
			    public:
			        using value_type = T;
			        Iterator() : ptr(nullptr) {};
			        Iterator(T* ptr) : ptr(ptr) {};
			        T& operator*() { return *ptr; };
			        Iterator& operator=(const Iterator& other) {
			            ptr = other.ptr;
			            return *this;
			        };
			        Iterator& operator++() { ptr += sizeof(T); return *this; };
			        Iterator operator++(int) { auto copy = *this; ptr += sizeof(T); return copy; };
			        friend int operator-(Iterator lhs, Iterator rhs) {
			            return lhs.ptr - rhs.ptr;
			        };
			        bool operator==(const Iterator& other) const { return ptr == other.ptr; };
			        // bool operator!=(const Iterator& other) const { return ptr != other.ptr; };
			    private:
			        T* ptr;
			};
			const Iterator cbegin() const { return Iterator(&x); };
			const Iterator cend() const { return Iterator(&w); };
			const Iterator begin() const { return Iterator(&x); };
			const Iterator end() const { return Iterator(&w); };

	}; // vec4

	using vec2f = vec2<float>;
	using vec2d = vec2<double>;
	using vec2i = vec2<int>;
	using vec2u = vec2<unsigned int>;

	using vec3f = vec3<float>;
	using vec3d = vec3<double>;
	using vec3i = vec3<int>;
	using vec3u = vec3<unsigned int>;

	using vec4f = vec4<float>;
	using vec4d = vec4<double>;
	using vec4i = vec4<int>;
	using vec4u = vec4<unsigned int>;

} // namespace gz
