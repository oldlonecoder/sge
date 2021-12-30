//
// Created by oldlonecoder on 21-12-11.
//

//#ifndef SGE_SGE_H
//#define SGE_SGE_H

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

#include <sge/gameconfigs.h>


namespace sge
{
static constexpr float deg2rad = 0.017245f;

class game
{
    
    
    sf::RenderWindow*   _window = nullptr;
    sf::Event       _event;
    sf::Clock       _clock;
    bool            _pause = false;
    bool            _running = false;
    std::string _assets_location;
    std::string _name;
    game_entities   _game_entities;
    static game_configs _configs;
    iostr::word::list_t _words;
public:
    game() = default;
    game(std::string gane_name_);
    ~game();
    
    static game_configs& configs();
    
    expect<rem::code> load_configs();
    
    void init();
    void update(float st_);
    void movements();
    sf::Event::EventType process_key_inputs();
    void process_mouse_inputs();
    void render();
    void ennemy_spawner();
    void collisions();
    void run();
    
};

}

//#endif //SGE_SGE_H
