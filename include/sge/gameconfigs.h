//
// Created by oldlonecoder on 21-12-21.
//

//#ifndef SGE_GAMECONFIGS_H
//#define SGE_GAMECONFIGS_H

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
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vxio/util/logger.h>
#include <vxio/util/expect.h>
#include <sge/entity.h>
         // tokens stream,
#include <vxio/interpret/compiler/grammar.h> // rules.
#include <vxio/lexer/lexer.h>



namespace sge
{

class game_configs
{
    vxio::lexer lex;
    vxio::token_data::collection tokens;
    vxio::token_data::iterator cc;
    
    std::string cfg_path;
    std::string game_name;
    using in_fn = expect<>(game_configs::*)();
    using input_table = std::map<std::string, game_configs::in_fn>;
    
    game_configs::in_fn in_fnptr = nullptr;
    static game_configs::input_table inputs_table;
    bool next_token();
    friend class game;
    
public:
    /*!
     * @brief config data struct that can grow as well into the derived game_configs class
     */
    struct data
    {
        sf::Vector2i resolution;
        std::string  scene0_background;
        int          framerate;
        
        std::string assets_path;
        
        
    };
    
    game_configs() {} ;
    virtual ~game_configs();
    game_configs(std::string name_, std::string config_path_="/usr/local/games");
    
    
    game_configs& operator=(game_configs&&) noexcept;
    game_configs& operator=(const game_configs&);
    
    virtual expect<> in_res();
    virtual expect<> in_framerate();
    virtual expect<> in_wallpaper();
    
    virtual expect<> in_expect(vxio::type::T token_type);
    
    virtual game_configs::data& configs_data() { return _config_data; }
    virtual expect<> load_ini_sourcefile();
    
private:
    data _config_data;
};

}

//#endif //SGE_GAMECONFIGS_H
