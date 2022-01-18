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
    logger::fatal() << " segmentation fault signal.";
    flush_logs();
    exit(127);
}

void sig_abort( int s)
{
    logger::error() << " abort signal ";
    flush_logs();
    exit(127);
}

namespace sge
{


std::string configs_grammar = R"(
game      : id_t bloc.
bloc        : '{' +assign '}'.
assign      : id_t ':' '"' text_t '"'  ';'  | id_t ':' number_t ',' number_t ';' |  id_t ':' number_t ';'.
)";

game_configs::input_table game_configs::inputs_table=
    {
        {"resolution",  &game_configs::assemble_resolution},
        {"framerate",   &game_configs::assemble_framerate},
        {"wallpaper",   &game_configs::assemble_wallpaper},
        {"{",           &game_configs::assemble_bloc},
        {"game",      &game_configs::assemble_global},
        {"name",      &game_configs::assign_name},
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
    
    parser.set_bloc(nullptr)
    .set_tokens_stream(&tokens)
    .set_assembler([this](vxio::parser::context_t& ctx)->rem::code{
        return assemble(ctx);
    });

    logger::info(src_funcname) << " compiling sge source configs :";
    rem::code code = parser.parse("global");
    logger::info(src_long_funcname) << " compile result:" << code << rem::code::endl << "destroying vxio resources:";

    vxio::grammar::destroy_rules();
    return logger::warning(src_long_funcname) << " : really not yet fully implement...";
}

rem::code game_configs::assemble(vxio::parser::context_t& ctx)
{
    auto token = ctx.begin_cache();
    logger::debug(src_funcname) << "context " << ctx.status() << "'=>\n";
    auto it = game_configs::inputs_table.find((*token)->text());
    if(it == game_configs::inputs_table.end())
    {
        logger::fatal(src_funcname) << " gameconfigs has no such handle for token " << (*ctx.token_ptr)->text();
        abort();
    }
    auto [k,fnptr] = *it;
    logger::debug(src_funcname) << "key:'" << k << "':\n";
    if(fnptr)
        return (this->*fnptr)(ctx);
    
    logger::fatal(src_long_funcname) << " '" << k << "'  has yet to be implemented!!! :)";
    abort();
    return rem::code::rejected;
}


rem::code game_configs::assemble_resolution(vxio::parser::context_t& ctx)
{
    ctx.begin_cache();
    logger::debug(src_funcname) << ":\nfirst token: " << (*ctx.token_ptr)->text();
    
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    //:
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    iostr str;
    str = (*ctx.token_ptr)->text();
    str >> _config_data.resolution.x;
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    // ','
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }

    str = (*ctx.token_ptr)->text();
    str >> _config_data.resolution.y;
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    // ';'
    logger::debug() << "check:\n";
    logger::info() << "gameconfigs::resolution = {" << _config_data.resolution.x << ',' << _config_data.resolution.y << " } - end token is '" << (*ctx.token_ptr)->text() << "'\n";
    return rem::code::accepted;
}


rem::code game_configs::assemble_framerate(vxio::parser::context_t& ctx)
{
    ctx.begin_cache();
    logger::debug(src_funcname) << ":\nfirst token: " << (*ctx.token_ptr)->text();
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    // ':'
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    iostr str;
    str = (*ctx.token_ptr)->text();
    str >> _config_data.framerate;
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    // ';'
    logger::debug() << "check:\n";
    logger::info() << "framerate: " << _config_data.framerate << ".\n ==> end token : '" << (*ctx.token_ptr)->text();
    return rem::code::accepted;
}


rem::code game_configs::assemble_wallpaper(vxio::parser::context_t& ctx)
{
    ctx.begin_cache();

    logger::debug(src_funcname) << ":\nfirst token: " << (*ctx.token_ptr)->text();
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    // ':'
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    // '"'
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    _config_data.wallpaper = (*ctx.token_ptr)->text();
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    //'"'
    if(!--ctx)
    {
        logger::error(src_funcname) << " unexpected eot";
        return rem::code::rejected;
    }
    // ';'
    logger::debug(src_funcname) << "check:" << rem::code::endl << " gameconfigs::wallpaper = " << _config_data.wallpaper << rem::code::endl;
    return rem::code::accepted;
}

rem::code game_configs::assign_name(vxio::parser::context_t&)
{
    return rem::code::rejected;
}


rem::code game_configs::assemble_bloc(vxio::parser::context_t& ctx)
{
    return rem::code::accepted;
}

rem::code game_configs::assemble_global(vxio::parser::context_t& ctx)
{
    return rem::code::accepted;
}

}

