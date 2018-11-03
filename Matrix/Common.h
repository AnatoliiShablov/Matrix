#pragma once

#include <complex>
#include <cstdint>
#include <type_traits>


template<typename T>
struct extract_type {
	using type = void;
};

template<template<typename ...> class C, typename V>
struct extract_type<C<V>> {
	using type = V;
};

template<typename T>
using extract_type_t = typename extract_type<T>::type;

namespace {
	template<class>
	struct sfinae_true : std::true_type {
	};

	template<class T>
	static auto test_unit(int) -> sfinae_true<decltype(T::unit())>;

	template<class>
	static auto test_unit(long) -> std::false_type;
}

template<class T>
struct has_unit : decltype(test_unit<T>(0)) {
};

template<typename T>
inline constexpr bool has_unit_v = has_unit<T>::value;

template<typename T>
T unit() {
	if constexpr (std::is_integral_v<T>) {
		return static_cast<T>(1);
	} else if constexpr (std::is_floating_point_v<T>) {
		return static_cast<T>(1.);
	} else if constexpr (std::is_same_v<T, std::complex<extract_type_t<T>>>) {
		return {unit<extract_type_t<T>>(), 0};
	} else if constexpr (has_unit_v<T>) {
		return T::unit();
	}
	return {};
}

