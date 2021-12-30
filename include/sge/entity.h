//
// Created by oldlonecoder on 21-12-11.
//

//#ifndef SGE_ENTITY_H
//#define SGE_ENTITY_H

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

#include <vxio/util/logger.h>
#include <vxio/util/object.h>
#include <sge/component.h>
#include <map>

#pragma once
namespace sge
{

/*!
 * @brief Base entity class.
 */
class entity : public vxio::object
{
protected:
    std::string _tag;  ///< entity type tag string.
    std::size_t _id     = 0;
    bool        _active = false;
    transform   _smdsa;
    asset       _asset; ///< image/sprite/texture/anim.
    
    entity() = default;
    
    friend class game_entities;
    
    enum type: uint8_t {
        Static,
        Obstacle,
        Scene,
        Player,
        Enemy,
        Defense,
        Weapon
        
        //...
    }_class = entity::type::Obstacle;
    
public:
    using collection = std::vector<entity*>;
    using map        = std::map<std::string, entity::collection>;
protected:
    float            _collision = 0.f; ///< collision radius;
    lifespan         _life; ///< {remaining: 0, total: 0, length: 0.0f} by default
public:
    entity(std::string tag_);
    ~entity() override;
    void destroy(){ _active = false; } ///< Delayed destroy;
    virtual bool update(float dt_); ///< false == do not render...
    virtual asset& asset_data() { return _asset; }
    virtual transform& transform_data() { return _smdsa; }
    virtual void render(sf::RenderTarget* target_);
};


class game_entities : public vxio::object
{
    entity::collection entities;
    entity::map        entity_types;
public:
    
    game_entities() = default;
    ~game_entities() override;
    
    entity::collection& operator[](const std::string& tag_name_);
    game_entities&      operator << (entity* e);
    
};

}

//#endif //SGE_ENTITY_H
