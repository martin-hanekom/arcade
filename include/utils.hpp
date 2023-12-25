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
inline T random(T low, T high)
{
    return low + static_cast<T>(std::rand()) / (static_cast<T>(RAND_MAX) / (high - low));
}

#endif