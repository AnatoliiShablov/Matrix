#pragma once

#include <cstdint>
#include <type_traits>

template<typename T>
T unit() {
	if constexpr (std::is_integral_v<T>) {
		return static_cast<T>(1);
	} else if constexpr (std::is_floating_point_v<T>) {
		return static_cast<T>(1.);
	}
	return {};
}
