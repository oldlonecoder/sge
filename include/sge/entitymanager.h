//
// Created by oldlonecoder on 21-12-11.
//

//#ifndef SGE_ENTITYMANAGER_H
//#define SGE_ENTITYMANAGER_H

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
#include <sge/entity.h>
namespace sge
{
class entity_manager
{
    entity::collection _entities;
    entity::map        _entity_dictionary;
    entity::collection _pending_entities;
public:
    entity_manager() = default;
    ~entity_manager();
    
    void init();
    void update();
    
    entity::collection &entities() { return _entities; }
    entity::map &dictionary() { return _entity_dictionary; }
    
    void remove_dead_entities(entity::collection& e);
    
    
};

}
//#endif //SGE_ENTITYMANAGER_H
