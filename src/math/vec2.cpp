#include "vec2.hpp"

#include "mat2x2.hpp"
#include "mat2x3.hpp"
#include "mat2x4.hpp"
#include "rvec2.hpp"
#include "rvec3.hpp"
#include "rvec4.hpp"

#include <cmath>
#include <algorithm>
#include <cstdint>

namespace gz {

	//
	// CLASS vec2
	//
	template<Number T>
	template<Number N>
	constexpr void vec2<T>::operator=(const vec2<N>& other) {
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);

	}
	template<Number T>
	template<Number N>
	constexpr void vec2<T>::operator=(const N& other) {
			x = static_cast<T>(other);
			y = static_cast<T>(other);

	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr vec2<T> vec2<T>::operator+(const C& other) const {
		return vec2<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y));
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr vec2<T> vec2<T>::operator-(const C& other) const {
		return vec2<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y));
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr vec2<T> vec2<T>::operator%(const C& other) const {
		return vec2<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y));
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr vec2<T> vec2<T>::compWiseMult(const C& other) const {
		return vec2<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y));
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr vec2<T> vec2<T>::compWiseDiv(const C& other) const {
		return vec2<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y));
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr void vec2<T>::operator+=(const C& other) {
			x += static_cast<T>(other.x);
			y += static_cast<T>(other.y);
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr void vec2<T>::operator-=(const C& other) {
			x -= static_cast<T>(other.x);
			y -= static_cast<T>(other.y);
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr void vec2<T>::operator%=(const C& other) {
			x %= static_cast<T>(other.x);
			y %= static_cast<T>(other.y);
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr void vec2<T>::compWiseAssMult(const C& other) {
			x *= static_cast<T>(other.x);
			y *= static_cast<T>(other.y);
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr void vec2<T>::compWiseAssDiv(const C& other) {
			x /= static_cast<T>(other.x);
			y /= static_cast<T>(other.y);
	}
	template<Number T>
	template<Number N>
	constexpr vec2<T> vec2<T>::operator+(const N& other) const {
		return vec2<T>(x + static_cast<T>(other), y + static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec2<T> vec2<T>::operator-(const N& other) const {
		return vec2<T>(x - static_cast<T>(other), y - static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec2<T> vec2<T>::operator%(const N& other) const {
		return vec2<T>(x % static_cast<T>(other), y % static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec2<T> vec2<T>::compWiseMult(const N& other) const {
		return vec2<T>(x * static_cast<T>(other), y * static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec2<T> vec2<T>::compWiseDiv(const N& other) const {
		return vec2<T>(x / static_cast<T>(other), y / static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr void vec2<T>::operator+=(const N& other) {
			x += static_cast<T>(other);
			y += static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec2<T>::operator-=(const N& other) {
			x -= static_cast<T>(other);
			y -= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec2<T>::operator%=(const N& other) {
			x %= static_cast<T>(other);
			y %= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec2<T>::compWiseAssMult(const N& other) {
			x *= static_cast<T>(other);
			y *= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec2<T>::compWiseAssDiv(const N& other) {
			x /= static_cast<T>(other);
			y /= static_cast<T>(other);
	}
	template<Number T>
	template<RowVector2 R>
	constexpr mat2x2<T> vec2<T>::operator*(const R& other) const {
		mat2x2<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		return new_;
	}
	template<Number T>
	template<RowVector3 R>
	constexpr mat2x3<T> vec2<T>::operator*(const R& other) const {
		mat2x3<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x1_3 = x * other.z;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		new_.x2_3 = y * other.z;
		return new_;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr mat2x4<T> vec2<T>::operator*(const R& other) const {
		mat2x4<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x1_3 = x * other.z;
		new_.x1_4 = x * other.w;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		new_.x2_3 = y * other.z;
		new_.x2_4 = y * other.w;
		return new_;
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr bool vec2<T>::operator==(const C& other) const {
		return x == other.x and y == other.y;
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr bool vec2<T>::operator<(const C& other) const {
		return x < other.x and y < other.y;
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr bool vec2<T>::operator>(const C& other) const {
		return x > other.x and y > other.y;
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr bool vec2<T>::operator!=(const C& other) const {
		return x == other.x and y == other.y;
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr bool vec2<T>::operator<=(const C& other) const {
		return x > other.x and y > other.y;
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr bool vec2<T>::operator>=(const C& other) const {
		return x < other.x and y < other.y;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec2<T>::operator==(const N& other) const {
		return x == other and y == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec2<T>::operator<(const N& other) const {
		return x < other and y < other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec2<T>::operator>(const N& other) const {
		return x > other and y > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec2<T>::operator!=(const N& other) const {
		return x == other and y == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec2<T>::operator<=(const N& other) const {
		return x > other and y > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec2<T>::operator>=(const N& other) const {
		return x < other and y < other;
	}
	template<Number T>
	constexpr inline float vec2<T>::abs() const {
		return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y));
	}
	template<Number T>
	constexpr inline float vec2<T>::ratio() const {
		return static_cast<float>(x) / y;
	}
	template<Number T>
	constexpr inline float vec2<T>::invereseRatio() const {
		return static_cast<float>(y) / x;
	}
	template<Number T>
	constexpr inline T vec2<T>::min() const {
		return *std::min_element(cbegin(), cend());
	}
	template<Number T>
	constexpr inline T vec2<T>::max() const {
		return *std::max_element(cbegin(), cend());
	}
	template<Number T>
	template<Number N>
	constexpr inline T vec2<T>::dot(const vec2<N>& other) const {
		return x * static_cast<T>(other.x) + y * static_cast<T>(other.y);
	}
	template<Number T>
	constexpr T vec2<T>::operator[](std::size_t i) const {
		return *(&x + sizeof(T) * i);
	}
	template<Number T>
	constexpr Iterator<T> vec2<T>::cbegin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> vec2<T>::cend() const {
		return Iterator(const_cast<T*>(&y + sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> vec2<T>::begin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> vec2<T>::end() const {
		return Iterator(const_cast<T*>(&y + sizeof(T)));
	}


} // namespace gz

#include "vec2.tpp"