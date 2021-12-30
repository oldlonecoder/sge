//
// Created by oldlonecoder on 21-12-11.
//

#include <sge/entity.h>



namespace sge
{

entity::entity(std::string tag_):vxio::object(),
_tag(std::move(tag_))
{

}
entity::~entity()
{
    if(_asset._type == asset::type::sprite_t)
        delete _asset.sprite;
    else
        delete _asset.texture;
    
}


bool entity::update(float dt_)
{
    //...
    return false;
}

void entity::render(sf::RenderTarget *target_)
{
    if(_asset._type == asset::type::sprite_t)
        target_->draw(*_asset.sprite);
    else
        target_->draw(*_asset.forme->_shape);
}

game_entities::~game_entities()
{
    for(auto* e: entities)
    {
        delete e;
    }
    entity_types.clear();
    entities.clear();
}

entity::collection &game_entities::operator[](const std::string& tag_name_)
{
    auto i = entity_types.find(tag_name_);
    if(i==entity_types.end())
    {
        logger::error() << "entity type '" << tag_name_ << "' does not exists";
        return entities; // returning full length entities.
    }
    auto& [k,c] = *i;
    return c;
}


game_entities &game_entities::operator<<(entity *e)
{

    entities.push_back(e);
    entities.back()->_id = entities.size();

    auto i = entity_types.find(e->_tag);
    if(i==entity_types.end())
        entity_types[e->_tag] = entity::collection{};
    entity::collection& col = entity_types[e->_tag]; // creates new
    col.push_back(e);
    return *this;
}

}
