//
// Created by oldlonecoder on 21-12-11.
//

#include <sge/entitymanager.h>


namespace sge
{

entity_manager::~entity_manager()
{

}
void entity_manager::init()
{

}
void entity_manager::update()
{
    for(auto& [tag, e] : _entity_dictionary)
    {
        remove_dead_entities(e);
    }
}


void entity_manager::remove_dead_entities(entity::collection& e)
{

}

}