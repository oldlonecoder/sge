//
// Created by oldlonecoder on 21-12-21.
//

#include <sge/gameconfigs.h>
#include <fstream>

namespace sge
{

game_configs::input_table game_configs::inputs_table=
    {
        {"resolution",  &game_configs::in_res},
        {"framerate",   &game_configs::in_framerate},
        {"wallpaper",   &game_configs::in_wallpaper}
        //... more common rules and config elements to come...
    };


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


expect<> game_configs::in_res()
{
    logger::debug(src_long_funcname) << "resolution element:\n" << cc->mark() << '\n';
    // expect tokens: number_t ',' number_t ';'
    if(!next_token())
        return logger::error() << " unexpected end of file in window resolution config.";
    if(!cc->is_number())
        return logger::error() << " expected numeric value in window resolution config: \n" << cc->mark();
    iostr text = cc->text();
    text >> _config_data.resolution.x;
    logger::debug() << "resolution.x = " << _config_data.resolution.x;

    if(!next_token())
        return logger::error() << " unexpected end of file in window resolution config.";
    logger::debug() << "resolution:  next token: \n" << cc->mark() << "\n";
    
    if(!cc->is_punctuation() || (cc->c != vxio::mnemonic::k_comma))
        return logger::error() << " expected comma separator ( ',' ) in window resolution config : \n" << cc->mark();
    if(!next_token())
        return logger::error() << " unexpected end of file in window resolution config.";
    
    logger::debug() << "resolution:  next token: \n" << cc->mark() << "\n";
    if(!cc->is_number())
        return logger::error() << " expected numeric value in window resolution config:\n";
    text = cc->text();
    text >> _config_data.resolution.y;
    logger::debug() << "resolution.y = " << _config_data.resolution.y;
    if(!next_token())
        return logger::warning() << " unexpected end of file, expected end of statement punctuation  ( ';' ), in window resolution config:\n";
    
    logger::debug() << "resolution:  next token: \n" << cc->mark() << "\n";
    if(cc->c != vxio::mnemonic::k_semicolon)
        logger::warning() << " expected end of statement punctuation  ( ';' ) in window resolution config:\n" << cc->mark();
    logger::debug() << " resolution parameters data completed!:) \n";
    return rem::code::accepted;
}


expect<> game_configs::in_framerate()
{
    logger::debug(src_long_funcname) << ":\n";
    if(!next_token())
        return logger::error() << " unexpected end of file in framerate config.";

    logger::debug() << "framerate:  next token: \n" << cc->mark() << "\n";
    if(!cc->is_number())
        return logger::error() << " expected numeric value in framerate config:\n" << cc->mark() << "\n aborted";
    
    iostr text = cc->text();
    text >> _config_data.framerate;
    logger::debug() << "framerate = " << _config_data.framerate;
    if(!next_token())
        return logger::warning() << " unexpected end of file, expected end of statement punctuation  ( ';' ), in framerate config:\n";
    
    return rem::code::accepted;
}
/*!
 * @brief get the wallpaper background path/filename
 * @return rem::code
 *
 * @todo maybe call one function instead of repeating next_token/in_expect specifically for a string delimited token.
 */
expect<> game_configs::in_wallpaper()
{
    logger::debug() << "scene0::wallpaper configs:" << '\n';
    auto R = in_expect(vxio::type::text_t);
    if(!R)
        return R;
    if(cc->c != vxio::mnemonic::k_dquote)
        return logger::error() << " expected quote's delimiter for text, got\n" << cc->mark();
    R = in_expect(vxio::type::text_t);
    if(!R)
        return R;
    
    _config_data.scene0_background = cc->text();
    
    logger::debug() << "scene0::wallpaper (file) :'" << _config_data.scene0_background << "'\n";

    R = in_expect(vxio::type::text_t);
    if(!R)
        return R;
    if(cc->c != vxio::mnemonic::k_dquote) // pas suppose
        return logger::error() << " expected quote's delimiter for text, got\n" << cc->mark();
    
    R = in_expect(vxio::type::punc_t);
    if(!R)
        return R;
    
    if(cc->c != vxio::mnemonic::k_semicolon)
        logger::warning() << " expected end of statement punctuation  ( ';' ) in scene0 config:\n" << cc->mark();
    
    logger::debug() << " scene0 parameters data completed!:) \n";
    
    return rem::code::accepted;
}

expect<> game_configs::load_ini_sourcefile()
{
    iostr filename = cfg_path + game_name + ".ini"; // "usr/local/games/virtualspace/virtualspace.ini"
    logger::debug() << "ini file path:" << filename() << ":\n";
    iostr data_stream;
    
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
    lex.config() = {
        data_stream.c_str(),
        &tokens
    };
    logger::debug() << "ini source contents:\n" << data_stream() << ":\n";
    if(lex() != rem::code::accepted)
    {
        // internal error...
        logger::error() << "unrecognized error in config file.\n tokens: " << tokens.size() << "\n";
        lex.dump_tokens([](const vxio::token_data& token)
        {
            logger::info() << token.details(true) << "\n";
        });
        
        return rem::code::rejected;
    }
    
    logger::debug() << "lexer done! -> tokens count: " << tokens.size() << ":\n";
    cc=tokens.begin();
    
    while(cc != tokens.end())
    {
        expect<> e;
        logger::debug() << "token: \n" << cc->mark() << "  -->\n";
        
        auto i = game_configs::inputs_table.find(cc->text());
        if(i == game_configs::inputs_table.end())
        {
            logger::error() << "error: in config file:\n" << cc->details(true) << "\nrejected.\n";
            return rem::code::rejected;
        }
        auto [k,fnptr] = *i;
        logger::debug() << "element: '" << k << "' :\n";
        if(fnptr)
        {
            if(!(e = (this->*fnptr)()))
            {
                std::cerr << " error: on key = '" << k << "'\n";
                return e;
            }
        }
        else
            std::cerr << k << ": oops\n";
        ++cc;
    }
    return rem::code::accepted;
}


bool game_configs::next_token()
{
    ++cc;
    return cc != tokens.end();
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
expect<> game_configs::in_expect(vxio::type::T token_type)
{
    if(!next_token())
        return logger::error() << " unexpected end of file while loading game configs.";
    
    logger::debug() << "next token: " << cc->details(true);

    if(cc->t != token_type)
        return logger::error() << "expected " << vxio::type::name(token_type)  << " token, got :\n" << cc->details(true) << "\n";
    
    return rem::code::accepted;
}

}