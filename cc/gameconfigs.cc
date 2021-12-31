//
// Created by oldlonecoder on 21-12-21.
//

#include <sge/gameconfigs.h>
#include <fstream>
#include <signal.h>


void flush_logs()
{
    logger::clear([](rem& r){
        std::cout << r.cc() << "\n";
    });
}

void sig_int( int s )
{
    logger::info() << " interrupt signal by ctrl-c hit on keyboard. ";
    flush_logs();
    exit(3);
}

void sig_fault( int s)
{
    logger::info() << " segmentation fault signal.";
    flush_logs();
    exit(127);
}

void sig_abort( int s)
{
    logger::info() << " abort signal ";
    flush_logs();
    exit(127);
}

namespace sge
{


std::string configs_grammar = R"(
global      : id_t bloc.
bloc        : '{' +assign '}'.
assign      : ?resolution ?wallpaper ?framerate ?name.
resolution  : id_t ':' number_t ',' number_t ';'.
wallpaper   : id_t ':' '"' text_t '"'  ';'.
framerate   : id_t ':' number_t ';'.
name        : id_t ':' '"' text_t '"' ';'.
)";

game_configs::input_table game_configs::inputs_table=
    {
        {"resolution",  &game_configs::parse_resolution},
        {"framerate",   &game_configs::parse_framerate},
        {"wallpaper",   &game_configs::parse_wallpaper}
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



expect<> game_configs::init()
{
    
    vxio::grammar g;
    
    ::signal(SIGINT, sig_int);
    ::signal(SIGSEGV, sig_fault);
    ::signal(SIGABRT, sig_abort);
    
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
    
    vxio::parser parser;
    
    parser.set_bloc(nullptr).set_tokens_stream(&tokens).set_assembler([this](vxio::parser::context_t& ctx)->expect<>{
        return parse_context(ctx);
    });
    parser.parse("global");
    vxio::grammar::destroy_rules();
    return logger::warning(src_long_funcname) << " : implement...";
}

expect<> game_configs::parse_context(vxio::parser::context_t& ctx)
{
//    auto token = ctx.i_tokens.begin();
//    logger::debug(src_long_funcname) << "context::token:'" << (*token)->text() << "'=>\n";
//    auto it = game_configs::inputs_table.find((*token)->text());
//    auto [k,fnptr] = *it;
//    logger::debug(src_long_funcname) << "key:'" << k << "'; =>\n";
//    if(fnptr)
//        return (this->*fnptr)(ctx);
    
    return logger::fatal(src_long_funcname) << " yet to be implemented!!! :)";
}


expect<> game_configs::parse_resolution(vxio::parser::context_t& ctx)
{
//    auto token = ctx.i_tokens.begin();
//    logger::debug(src_long_funcname) << ":\nfirst token: " << (*token)->text();
//    ++token;
//    // ':'
//    ++token;
//    iostr str;
//    str = (*token)->text();
//    str >> _config_data.resolution.x;
//    ++token;
//    // ','
//    ++token;
//    str = (*token)->text();
//    str >> _config_data.resolution.y;
//    ++token;
//    // ';'
//    logger::debug() << "check:\n";
//    logger::debug() << "resolution: " << _config_data.resolution.x << ',' << _config_data.resolution.y << " ; end token : '" << (*token)->text() << "'\n";
    return rem::code::accepted;
}


expect<> game_configs::parse_framerate(vxio::parser::context_t& ctx)
{
//    auto token = ctx.i_tokens.begin();
//    logger::debug(src_long_funcname) << ":\nfirst token: " << (*token)->text();
//    ++token;
//    // ':'
//    ++token;
    return rem::code::implement;
}


expect<> game_configs::parse_wallpaper(vxio::parser::context_t& ctx)
{
   
    
    return rem::code::implement;
}

}