//
// Created by oldlonecoder on 21-12-11.
//

#include <sge/vec2.h>
#include <cmath>
namespace sge
{
vec2::vec2(vec2 &&rhs)
noexcept
{
x = rhs.x;
y = rhs.y;
}
vec2::vec2(const vec2 &rhs)
noexcept
{
x = rhs.x;
y = rhs.y;
}
vec2 &vec2::operator=(const vec2 &rhs)
{
    x = rhs.x;
    y = rhs.y;
    
    return *this;
}
vec2 &vec2::operator=(vec2 &&rhs)
noexcept
{
x = rhs.x;
y = rhs.y;
return *this;
}
vec2 vec2::operator+(const vec2 &rhs) const
{
    return {x + rhs.x, y + rhs.y};
}
vec2 &vec2::operator+=(const vec2 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

vec2 vec2::operator-(const vec2 &rhs) const
{
    return {x - rhs.x, y - rhs.y};
}
vec2 &vec2::operator-=(const vec2 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

vec2 vec2::operator*(const vec2 &rhs) const
{
    return {x * rhs.x, y * rhs.y};
}
vec2 &vec2::operator*=(const vec2 &rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    
    return *this;
}
vec2 vec2::operator/(const vec2 &rhs) const
{
    return {x / rhs.x, y / rhs.y};
}
vec2 &vec2::operator/=(const vec2 &rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    
    return *this;
}

float vec2::dot(const vec2 &rhs) const
{
    return x * rhs.x + y * rhs.y;
}
vec2 vec2::operator*(float scale_)
{
    return {x * scale_, y * scale_};
}
float vec2::length() const
{
    return sqrtf(x * x + y * y);
}

/*!
 * @brief Normalisation
 * @return vec2 normalis&eacute;
 */
vec2 vec2::operator~() const
{
    float l = sqrtf(x * x + y * y);
    return {x / l, y / l};
}

bool vec2::operator<(const vec2 &rhs) const
{
    return (x * x + y * y) < (rhs.x * rhs.x + rhs.y * rhs.y);
}

bool vec2::operator>(const vec2 &rhs) const
{
    return (x * x + y * y) > (rhs.x * rhs.x + rhs.y * rhs.y);
}

bool vec2::operator<=(const vec2 &rhs) const
{
    return (x * x + y * y) <= (rhs.x * rhs.x + rhs.y * rhs.y);
}

bool vec2::operator>=(const vec2 &rhs) const
{
    return (x * x + y * y) >= (rhs.x * rhs.x + rhs.y * rhs.y);
}

bool vec2::operator==(const vec2 &rhs) const
{
    return (x * x + y * y) == (rhs.x * rhs.x + rhs.y * rhs.y);
}
vec2 vec2::operator/(float sc) const
{
    return {x / sc, y / sc};
}
}