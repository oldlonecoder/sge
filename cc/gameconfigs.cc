//
// Created by oldlonecoder on 21-12-21.
//

#include <sge/gameconfigs.h>
#include <fstream>

namespace sge
{


std::string configs_grammar = R"(
global      : id_t bloc.
bloc        : '{' +attr_id '}'.
attr_id     : ?resolution ?wallpaper ?framerate ?name.
resolution  : id_t ':' number_t ',' number_t ';'.
wallpaper   : id_t ':'  text_t ';'.
framerate   : id_t ':'  number_t ';'.
name        : id_t ':' text_t ';'.
)";

game_configs::input_table game_configs::inputs_table;
//    {
//        {"resolution",  &game_configs::in_res},
//        {"framerate",   &game_configs::in_framerate},
//        {"wallpaper",   &game_configs::in_wallpaper}
//        //... more common rules and config elements to come...
//    };


game_configs::~game_configs()
{

}


game_configs::game_configs(std::string name_, std::string config_path_):
cfg_path(std::move(config_path_)), game_name(std::move(name_))
{
    cfg_path += '/';
    cfg_path += game_name;
    cfg_path += '/';
}





expect<> game_configs::init()
{
    
    vxio::grammar g;
    g.text() = configs_grammar;
    g.build();
    g.dump();
    if(expect<> R; !(R = load_sge_sourcefile()))
        return R;
    return compile();
}



expect<> game_configs::load_sge_sourcefile()
{
    iostr filename = cfg_path + game_name + ".sge"; // "/usr/local/games/virtualspace/virtualspace.sge"
    logger::debug() << "sge file path:" << filename() << ":\n";
//
    std::ifstream f;
    char c;
    f.open(filename(),std::fstream::in|std::fstream::binary);
    if (!f.good())
    {
        auto err = logger::error() << vxio::color::Red4 << strerror(errno) << ".\n";
        std::cout << err.cc();
        return rem::code::rejected;
    }
    while (!f.eof())
    {
        f.get(c);
        data_stream += c;
    }
    f.close();

    logger::debug() << "sge source contents:\n" << data_stream << ":\n";
    return rem::code::accepted;
}



game_configs &game_configs::operator=(game_configs && rhs) noexcept
{
    cfg_path = std::move(rhs.cfg_path);
    game_name = std::move(rhs.game_name);
    _config_data = std::move(rhs._config_data);
    tokens       = std::move(rhs.tokens);
    return *this;
}
game_configs &game_configs::operator=(const game_configs &rhs)
{
    cfg_path = rhs.cfg_path;
    game_name = rhs.game_name;
    _config_data = rhs._config_data;
    tokens       = rhs.tokens;
    return *this;
}
expect<> game_configs::compile()
{
    
    lex.config() = {
        data_stream.c_str(),
        &tokens
    };
    if(lex() != rem::code::accepted)
        return logger::error() << " lexical analysis error in sge source file.";
    
    logger::debug() << "lexer done! -> tokens count: " << tokens.size() << ":\n";
    
    lex.dump_tokens([](const vxio::token_data& token){
       logger::debug() << token.details(true);
    });

    
    return logger::warning(src_long_funcname) << " : implement...";
}

}