#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

static const sf::Vector2f nullVector {0.0f, 0.0f};

inline void setOriginMiddle(sf::Text& text)
{
    sf::FloatRect bounds {text.getLocalBounds()};
    text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

inline float toRadians(float degrees)
{
    return degrees * M_PI / 180.0f;
}

inline float toDegrees(float radians)
{
    return radians * 180.0f / M_PI;
}

inline constexpr float radius(int health)
{
    constexpr int ratio {5};
    constexpr int offset {5};
    return ratio * health + offset;
}

template<class T>
inline sf::Vector2<T> polarVector(float radius, float angle, bool degrees = false)
{
    if (degrees)
    {
        angle = toRadians(angle);
    }

    return sf::Vector2<T>(radius * cos(angle), radius * sin(angle));
}

template<class T>
inline float vectorAbs(sf::Vector2<T> vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

template<class T>
inline float vectorAngle(sf::Vector2<T> vector)
{
    static const sf::Vector2<T> unit {1, 0};
    static const float unitAbs {vectorAbs(unit)};
    float angle {acosf((vector.x * unit.x + vector.y * unit.y) / (vectorAbs(vector) * unitAbs))}; 
    return angle * copysignf(1.0f, vector.y);
}

template<class T>
inline sf::Vector2<T> unitVector(sf::Vector2<T> vector)
{
    float const abs {vectorAbs(vector)};

    if (abs == 0)
    {
        return {0, 0};
    }

    return vector / vectorAbs(vector);
}

template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline T random(T const low, T const high)
{
    return low + static_cast<T>(std::rand()) % (high - low);
}

template<typename T, std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
inline T random(T const low, T const high)
{
    return low + static_cast<T>(std::rand()) / (static_cast<T>(RAND_MAX) / (high - low));
}

template<typename T>
inline sf::Vector2<T> randomVector2(T const low, T const high)
{
    return sf::Vector2<T>(random<T>(low, high), random<T>(low, high));
}

template<class T>
inline T distanceSquared(sf::Vector2<T> a, sf::Vector2<T> b)
{
    T x {a.x - b.x};
    T y {a.y - b.y};
    return x * x + y * y;
}

#endif