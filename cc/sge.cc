//
// Created by oldlonecoder on 21-12-11.
//

#include <sge/sge.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <map>

namespace sge
{

game_configs game::_configs;

game::~game()
{
    delete _window;
}
game::game(std::string game_name_)
{
    game::_configs = game_configs(std::move(game_name_));
}

void game::init()
{
    rem::init();
    if(!_configs.load_ini_sourcefile())
    {
        return ;
    }
    
    //_window = new sf::RenderWindow(sf::VideoMode(_configs._config_data.resolution.x, _configs._config_data.resolution.y), "SGE (Simple Game Engine Version 0.01", sf::Style::Titlebar | sf::Style::Close);
//    _window->setFramerateLimit(_configs._config_data.framerate);
//    entity *scene0 = new entity("scene0");
//    asset &a = scene0->asset_data();
//    iostr assets = _configs.cfg_path;
//    a.height  = static_cast<float>(_configs._config_data.resolution.y);
//    a.width   = static_cast<float>(_configs._config_data.resolution.x);
//    a.texture = new sf::Texture;
//    a.texture->loadFromFile((assets + "/scenes/nebula.jpg")());
//    sf::Vector2u sz = a.texture->getSize();
//    std::cout << " size of the texture after loading:" << sz.x << " , " << sz.y << ";\n";
//
//    a.sprite = new sf::Sprite(*a.texture);
//    a.sprite->setScale(a.width / 1920.f, a.height / 1080.f);
//    a.sprite->setPosition(0.f, 0.f);
//    //...
//    _game_entities << scene0;
}

void game::update(float dt_)
{
    std::cout << __PRETTY_FUNCTION__ << " timelap:" << dt_ << " sec\r" << std::flush;
}

void game::movements()
{

}

sf::Event::EventType game::process_key_inputs()
{
    switch(_event.key.code)
    {
        case sf::Keyboard::Escape:return sf::Event::Closed;
        default:break;
    }
    return sf::Event::EventType::Count;
}

void game::render()
{
    auto c = _game_entities["backgr"];
    for(auto *e: c)
    {
        e->render(_window);
    }
    _window->display();
}

void game::ennemy_spawner()
{

}

void game::collisions()
{

}

void game::run()
{
    //...
    while(_window->isOpen())
    {
        while(_window->pollEvent(_event))
        {
            feedback:
            switch(_event.type)
            {
                case sf::Event::Closed: // stop all game loops...
                    _window->close();
                    return;
                case sf::Event::KeyPressed:_event.type = process_key_inputs();
                    goto feedback;
                default:break;
            }
        }
        update(_clock.restart().asSeconds());
        render();
        
    }
}
void game::process_mouse_inputs()
{

}

game_configs &game::configs()
{
    return game::_configs;
}

expect<rem::code> game::load_configs()
{
    return rem::code::accepted;
}

}