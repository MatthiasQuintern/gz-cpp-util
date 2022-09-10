#include "vec3.hpp"

#include "mat3x2.hpp"
#include "mat3x3.hpp"
#include "mat3x4.hpp"
#include "rvec2.hpp"
#include "rvec3.hpp"
#include "rvec4.hpp"

#include <cmath>
#include <algorithm>
#include <cstdint>

namespace gz {

	//
	// CLASS vec3
	//
	template<Number T>
	template<Number N>
	constexpr void vec3<T>::operator=(const vec3<N>& other) {
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);

	}
	template<Number T>
	template<Number N>
	constexpr void vec3<T>::operator=(const N& other) {
			x = static_cast<T>(other);
			y = static_cast<T>(other);
			z = static_cast<T>(other);

	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr vec3<T> vec3<T>::operator+(const C& other) const {
		return vec3<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y), z + static_cast<T>(other.z));
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr vec3<T> vec3<T>::operator-(const C& other) const {
		return vec3<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y), z - static_cast<T>(other.z));
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr vec3<T> vec3<T>::operator%(const C& other) const {
		return vec3<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y), z % static_cast<T>(other.z));
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr vec3<T> vec3<T>::compWiseMult(const C& other) const {
		return vec3<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y), z * static_cast<T>(other.z));
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr vec3<T> vec3<T>::compWiseDiv(const C& other) const {
		return vec3<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y), z / static_cast<T>(other.z));
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr void vec3<T>::operator+=(const C& other) {
			x += static_cast<T>(other.x);
			y += static_cast<T>(other.y);
			z += static_cast<T>(other.z);
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr void vec3<T>::operator-=(const C& other) {
			x -= static_cast<T>(other.x);
			y -= static_cast<T>(other.y);
			z -= static_cast<T>(other.z);
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr void vec3<T>::operator%=(const C& other) {
			x %= static_cast<T>(other.x);
			y %= static_cast<T>(other.y);
			z %= static_cast<T>(other.z);
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr void vec3<T>::compWiseAssMult(const C& other) {
			x *= static_cast<T>(other.x);
			y *= static_cast<T>(other.y);
			z *= static_cast<T>(other.z);
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr void vec3<T>::compWiseAssDiv(const C& other) {
			x /= static_cast<T>(other.x);
			y /= static_cast<T>(other.y);
			z /= static_cast<T>(other.z);
	}
	template<Number T>
	template<Number N>
	constexpr vec3<T> vec3<T>::operator+(const N& other) const {
		return vec3<T>(x + static_cast<T>(other), y + static_cast<T>(other), z + static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec3<T> vec3<T>::operator-(const N& other) const {
		return vec3<T>(x - static_cast<T>(other), y - static_cast<T>(other), z - static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec3<T> vec3<T>::operator%(const N& other) const {
		return vec3<T>(x % static_cast<T>(other), y % static_cast<T>(other), z % static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec3<T> vec3<T>::compWiseMult(const N& other) const {
		return vec3<T>(x * static_cast<T>(other), y * static_cast<T>(other), z * static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec3<T> vec3<T>::compWiseDiv(const N& other) const {
		return vec3<T>(x / static_cast<T>(other), y / static_cast<T>(other), z / static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr void vec3<T>::operator+=(const N& other) {
			x += static_cast<T>(other);
			y += static_cast<T>(other);
			z += static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec3<T>::operator-=(const N& other) {
			x -= static_cast<T>(other);
			y -= static_cast<T>(other);
			z -= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec3<T>::operator%=(const N& other) {
			x %= static_cast<T>(other);
			y %= static_cast<T>(other);
			z %= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec3<T>::compWiseAssMult(const N& other) {
			x *= static_cast<T>(other);
			y *= static_cast<T>(other);
			z *= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec3<T>::compWiseAssDiv(const N& other) {
			x /= static_cast<T>(other);
			y /= static_cast<T>(other);
			z /= static_cast<T>(other);
	}
	template<Number T>
	template<RowVector2 R>
	constexpr mat3x2<T> vec3<T>::operator*(const R& other) const {
		mat3x2<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		new_.x3_1 = z * other.x;
		new_.x3_2 = z * other.y;
		return new_;
	}
	template<Number T>
	template<RowVector3 R>
	constexpr mat3x3<T> vec3<T>::operator*(const R& other) const {
		mat3x3<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x1_3 = x * other.z;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		new_.x2_3 = y * other.z;
		new_.x3_1 = z * other.x;
		new_.x3_2 = z * other.y;
		new_.x3_3 = z * other.z;
		return new_;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr mat3x4<T> vec3<T>::operator*(const R& other) const {
		mat3x4<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x1_3 = x * other.z;
		new_.x1_4 = x * other.w;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		new_.x2_3 = y * other.z;
		new_.x2_4 = y * other.w;
		new_.x3_1 = z * other.x;
		new_.x3_2 = z * other.y;
		new_.x3_3 = z * other.z;
		new_.x3_4 = z * other.w;
		return new_;
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr bool vec3<T>::operator==(const C& other) const {
		return x == other.x and y == other.y and z == other.z;
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr bool vec3<T>::operator<(const C& other) const {
		return x < other.x and y < other.y and z < other.z;
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr bool vec3<T>::operator>(const C& other) const {
		return x > other.x and y > other.y and z > other.z;
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr bool vec3<T>::operator!=(const C& other) const {
		return x == other.x and y == other.y and z == other.z;
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr bool vec3<T>::operator<=(const C& other) const {
		return x > other.x and y > other.y and z > other.z;
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr bool vec3<T>::operator>=(const C& other) const {
		return x < other.x and y < other.y and z < other.z;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec3<T>::operator==(const N& other) const {
		return x == other and y == other and z == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec3<T>::operator<(const N& other) const {
		return x < other and y < other and z < other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec3<T>::operator>(const N& other) const {
		return x > other and y > other and z > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec3<T>::operator!=(const N& other) const {
		return x == other and y == other and z == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec3<T>::operator<=(const N& other) const {
		return x > other and y > other and z > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec3<T>::operator>=(const N& other) const {
		return x < other and y < other and z < other;
	}
	template<Number T>
	constexpr inline float vec3<T>::abs() const {
		return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y) + static_cast<float>(z * z));
	}
	template<Number T>
	constexpr inline T vec3<T>::min() const {
		return *std::min_element(cbegin(), cend());
	}
	template<Number T>
	constexpr inline T vec3<T>::max() const {
		return *std::max_element(cbegin(), cend());
	}
	template<Number T>
	template<Number N>
	constexpr inline T vec3<T>::dot(const vec3<N>& other) const {
		return x * static_cast<T>(other.x) + y * static_cast<T>(other.y) + z * static_cast<T>(other.z);
	}
	template<Number T>
	constexpr T vec3<T>::operator[](std::size_t i) const {
		return *(&x + sizeof(T) * i);
	}
	template<Number T>
	constexpr Iterator<T> vec3<T>::cbegin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> vec3<T>::cend() const {
		return Iterator(const_cast<T*>(&z + sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> vec3<T>::begin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> vec3<T>::end() const {
		return Iterator(const_cast<T*>(&z + sizeof(T)));
	}


} // namespace gz

#include "vec3.tpp"