//
// Created by oldlonecoder on 21-12-11.
//

//#ifndef SGE_COMPONENT_H
//#define SGE_COMPONENT_H

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
#include <SFML/Graphics.hpp>
#include <sge/vec2.h>
#include <map>


namespace sge
{
struct transform
{
    vec2 speed;
    float     angle  = 0.f;
    float     radius = 0.f;
    sf::Transformable* _d = nullptr;
    transform() = default;
    transform(float angle_, float radius_);
    
    ~transform() = default;
    
    transform &operator=(transform &&) = default;
    transform &operator=(const transform &) = default;
    
};

struct shape
{
    using collection = std::vector<shape *>;
    
    enum class type:int8_t
    {
        circle,
        rectangle,
        invalid
    }_type=shape::type::invalid;
    
    union
    {
        sf::CircleShape    *_circle=nullptr;
        sf::RectangleShape *_rec;
    };
    sf::Shape* _shape = nullptr;
    //transform          smdsa; ///< shape movement direction speed angle
    
    shape(float radius_, int pts_, const sf::Color &fill, const sf::Color& outline_, float thck_);
    shape() = default;
    ~shape();
    
};


/*!
 * @brief entity asset data.
 */
struct asset
{
    using collection = std::vector<asset*>;
    using map = std::map<std::string, asset*>;
    enum class type : int8_t
    {
        shape_t,
        sprite_t
        //...
    }_type = asset::type::sprite_t;
    
    sf::Texture *texture = nullptr;
    
    union
    {
        shape       *forme = nullptr;
        sf::Sprite  *sprite;
    };
    
    float width = 0.f;
    float height = 0.f;
    
    std::string   id = "unset";
    sf::Color outline = sf::Color::White;
    sf::Color fill;
    float thickness = 0.5f;
};



/*!
 * @brief life params of entities.
 */
struct lifespan
{
    int remaining = 0;
    int total = 0;
    float length = 0,f; ///< Longevity in seconds.
};


struct input
{

};

}

//#endif //SGE_COMPONENT_H
