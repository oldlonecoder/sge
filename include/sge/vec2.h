//
// Created by oldlonecoder on 21-12-11.
//

//#ifndef GE_APP_VEC2_H
//#define GE_APP_VEC2_H

/**********************************************************************************************************************************
    Copyright 2021 Serge Lussier (oldlonecoder), lussier.serge@gmail.com
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software
    and associated documentation files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*************************************************************************************************************************************/


#pragma once

namespace sge
{

class vec2
{
public:
    float x = 0.f;
    float y = 0.f;
    
    vec2() = default;
    vec2(float x_, float y_) : x(x_), y(y_)
    {}
    
    vec2(vec2 &&rhs)
          noexcept;
    vec2(const vec2 &rhs)
          noexcept;
    
    ~vec2() = default;
    
    vec2 &operator=(const vec2 &rhs);
    vec2 &operator=(vec2 &&rhs)
    noexcept;
    
    vec2 operator+(const vec2 &rhs) const;
    vec2 &operator+=(const vec2 &rhs);
    vec2 operator-(const vec2 &rhs) const;
    vec2 &operator-=(const vec2 &rhs);
    vec2 operator*(const vec2 &rhs) const;
    vec2 &operator*=(const vec2 &rhs);
    vec2 operator/(const vec2 &rhs) const;
    vec2 &operator/=(const vec2 &rhs);
    vec2 operator*(float scale_);
    vec2 operator/(float sc) const;
    [[nodiscard]] float dot(const vec2 &rhs) const;
    [[nodiscard]] float length() const;
    
    vec2 operator~() const;
    
    bool operator<(const vec2 &rhs) const;
    bool operator>(const vec2 &rhs) const;
    bool operator<=(const vec2 &rhs) const;
    bool operator>=(const vec2 &rhs) const;
    bool operator==(const vec2 &rhs) const;
    
};

}

//#endif //GE_APP_VEC2_H
