#include "rvec2.hpp"

#include "mat2x2.hpp"
#include "mat2x3.hpp"
#include "mat2x4.hpp"
#include "rvec3.hpp"
#include "rvec4.hpp"
#include "vec2.hpp"

#include <cmath>
#include <algorithm>
#include <cstdint>

namespace gz {

	//
	// CLASS rvec2
	//
	template<Number T>
	template<Number N>
	constexpr void rvec2<T>::operator=(const rvec2<N>& other) {
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);

	}
	template<Number T>
	template<Number N>
	constexpr void rvec2<T>::operator=(const N& other) {
			x = static_cast<T>(other);
			y = static_cast<T>(other);

	}
	template<Number T>
	template<RowVector2 R>
	constexpr rvec2<T> rvec2<T>::operator+(const R& other) const {
		return rvec2<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y));
	}
	template<Number T>
	template<RowVector2 R>
	constexpr rvec2<T> rvec2<T>::operator-(const R& other) const {
		return rvec2<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y));
	}
	template<Number T>
	template<RowVector2 R>
	constexpr rvec2<T> rvec2<T>::operator%(const R& other) const {
		return rvec2<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y));
	}
	template<Number T>
	template<RowVector2 R>
	constexpr rvec2<T> rvec2<T>::compWiseMult(const R& other) const {
		return rvec2<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y));
	}
	template<Number T>
	template<RowVector2 R>
	constexpr rvec2<T> rvec2<T>::compWiseDiv(const R& other) const {
		return rvec2<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y));
	}
	template<Number T>
	template<RowVector2 R>
	constexpr void rvec2<T>::operator+=(const R& other) {
			x += static_cast<T>(other.x);
			y += static_cast<T>(other.y);
	}
	template<Number T>
	template<RowVector2 R>
	constexpr void rvec2<T>::operator-=(const R& other) {
			x -= static_cast<T>(other.x);
			y -= static_cast<T>(other.y);
	}
	template<Number T>
	template<RowVector2 R>
	constexpr void rvec2<T>::operator%=(const R& other) {
			x %= static_cast<T>(other.x);
			y %= static_cast<T>(other.y);
	}
	template<Number T>
	template<RowVector2 R>
	constexpr void rvec2<T>::compWiseAssMult(const R& other) {
			x *= static_cast<T>(other.x);
			y *= static_cast<T>(other.y);
	}
	template<Number T>
	template<RowVector2 R>
	constexpr void rvec2<T>::compWiseAssDiv(const R& other) {
			x /= static_cast<T>(other.x);
			y /= static_cast<T>(other.y);
	}
	template<Number T>
	template<Number N>
	constexpr rvec2<T> rvec2<T>::operator+(const N& other) const {
		return rvec2<T>(x + static_cast<T>(other), y + static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr rvec2<T> rvec2<T>::operator-(const N& other) const {
		return rvec2<T>(x - static_cast<T>(other), y - static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr rvec2<T> rvec2<T>::operator%(const N& other) const {
		return rvec2<T>(x % static_cast<T>(other), y % static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr rvec2<T> rvec2<T>::compWiseMult(const N& other) const {
		return rvec2<T>(x * static_cast<T>(other), y * static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr rvec2<T> rvec2<T>::compWiseDiv(const N& other) const {
		return rvec2<T>(x / static_cast<T>(other), y / static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr void rvec2<T>::operator+=(const N& other) {
			x += static_cast<T>(other);
			y += static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void rvec2<T>::operator-=(const N& other) {
			x -= static_cast<T>(other);
			y -= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void rvec2<T>::operator%=(const N& other) {
			x %= static_cast<T>(other);
			y %= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void rvec2<T>::compWiseAssMult(const N& other) {
			x *= static_cast<T>(other);
			y *= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void rvec2<T>::compWiseAssDiv(const N& other) {
			x /= static_cast<T>(other);
			y /= static_cast<T>(other);
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr rvec2<T> rvec2<T>::operator*(const M& other) const {
		rvec2<T> new_;
		new_.x = x * other.x1_1 + y * other.x2_1;
		new_.y = x * other.x1_2 + y * other.x2_2;
		return new_;
	}
	template<Number T>
	template<Mat2x3 M>
	constexpr rvec3<T> rvec2<T>::operator*(const M& other) const {
		rvec3<T> new_;
		new_.x = x * other.x1_1 + y * other.x2_1;
		new_.y = x * other.x1_2 + y * other.x2_2;
		new_.z = x * other.x1_3 + y * other.x2_3;
		return new_;
	}
	template<Number T>
	template<Mat2x4 M>
	constexpr rvec4<T> rvec2<T>::operator*(const M& other) const {
		rvec4<T> new_;
		new_.x = x * other.x1_1 + y * other.x2_1;
		new_.y = x * other.x1_2 + y * other.x2_2;
		new_.z = x * other.x1_3 + y * other.x2_3;
		new_.w = x * other.x1_4 + y * other.x2_4;
		return new_;
	}
	template<Number T>
	template<RowVector2 R>
	constexpr bool rvec2<T>::operator==(const R& other) const {
		return x == other.x and y == other.y;
	}
	template<Number T>
	template<RowVector2 R>
	constexpr bool rvec2<T>::operator<(const R& other) const {
		return x < other.x and y < other.y;
	}
	template<Number T>
	template<RowVector2 R>
	constexpr bool rvec2<T>::operator>(const R& other) const {
		return x > other.x and y > other.y;
	}
	template<Number T>
	template<RowVector2 R>
	constexpr bool rvec2<T>::operator!=(const R& other) const {
		return x == other.x and y == other.y;
	}
	template<Number T>
	template<RowVector2 R>
	constexpr bool rvec2<T>::operator<=(const R& other) const {
		return x > other.x and y > other.y;
	}
	template<Number T>
	template<RowVector2 R>
	constexpr bool rvec2<T>::operator>=(const R& other) const {
		return x < other.x and y < other.y;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec2<T>::operator==(const N& other) const {
		return x == other and y == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec2<T>::operator<(const N& other) const {
		return x < other and y < other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec2<T>::operator>(const N& other) const {
		return x > other and y > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec2<T>::operator!=(const N& other) const {
		return x == other and y == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec2<T>::operator<=(const N& other) const {
		return x > other and y > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec2<T>::operator>=(const N& other) const {
		return x < other and y < other;
	}
	template<Number T>
	constexpr inline float rvec2<T>::abs() const {
		return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y));
	}
	template<Number T>
	constexpr inline float rvec2<T>::ratio() const {
		return static_cast<float>(x) / y;
	}
	template<Number T>
	constexpr inline float rvec2<T>::invereseRatio() const {
		return static_cast<float>(y) / x;
	}
	template<Number T>
	constexpr inline T rvec2<T>::min() const {
		return *std::min_element(cbegin(), cend());
	}
	template<Number T>
	constexpr inline T rvec2<T>::max() const {
		return *std::max_element(cbegin(), cend());
	}
	template<Number T>
	template<Number N>
	constexpr inline T rvec2<T>::dot(const rvec2<N>& other) const {
		return x * static_cast<T>(other.x) + y * static_cast<T>(other.y);
	}
	template<Number T>
	constexpr T rvec2<T>::operator[](std::size_t i) const {
		return *(&x + sizeof(T) * i);
	}
	template<Number T>
	constexpr Iterator<T> rvec2<T>::cbegin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> rvec2<T>::cend() const {
		return Iterator(const_cast<T*>(&y + sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> rvec2<T>::begin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> rvec2<T>::end() const {
		return Iterator(const_cast<T*>(&y + sizeof(T)));
	}


} // namespace gz

#include "rvec2.tpp"