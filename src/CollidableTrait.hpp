#pragma once

#include <type_traits>

template<typename T, typename = void>
struct Collidable : std::false_type {};

template <typename T>
struct Collidable<T, decltype(std::declval<T>().position_, void())> : std::true_type {};
