#pragma once

#include "SDL/SDL.h"
#include <cmath>

struct Vector2 {
    Sint16 x, y;

    Vector2 operator+(const Vector2& other) const {
        return {static_cast<Sint16>(x + other.x), static_cast<Sint16>(y + other.y)};
    }

    Vector2 operator-(const Vector2& other) const {
        return {static_cast<Sint16>(x - other.x), static_cast<Sint16>(y - other.y)};
    }

    Vector2 operator*(float scalar) const {
        return {static_cast<Sint16>(x * scalar), static_cast<Sint16>(y * scalar)};
    }

    Vector2& operator+=(const Vector2& other) {
        x = static_cast<Sint16>(x + other.x);
        y = static_cast<Sint16>(y + other.y);
        return *this;
    }

    float magnitude() const {
        return std::sqrt(static_cast<float>(x * x + y * y));
    }

    Vector2 normalized() const {
        float mag = magnitude();
        return {static_cast<Sint16>(x / mag), static_cast<Sint16>(y / mag)};
    }
};