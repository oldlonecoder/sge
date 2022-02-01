//#include "game.h"
#include <iostream>
#include <sge/sge.h>
#include <vxio/interpret/compiler/axt.h>

vxio::token_data* token;

auto test_axt_newoperator()->rem::code
{
    token = new vxio::token_data(vxio::token_data::scan("//"));

    vxio::axt* axt_node = new vxio::axt(token);
    logger::debug(src_funcname) << " axt pool count: " << vxio::color::Yellow << vxio::axt::axt_pool.size();
    logger::debug(src_funcname) << " axt* axt_node: " << vxio::color::Yellow << axt_node->t0->details();
    logger::debug(src_funcname) << " axt pool instance at index 1: " << vxio::color::Yellow << vxio::axt::axt_pool.begin()->t0->text();

    return rem::code::accepted;
}


int main()
{
    sge::game game = sge::game("virtualspace");

    game.init();

    test_axt_newoperator();
    logger::debug(src_funcname) << " axt pool count: " << vxio::color::Yellow << vxio::axt::axt_pool.size();
    logger::debug(src_funcname) << " axt pool instance at index 1: '" << vxio::color::Yellow << vxio::axt::axt_pool.begin()->t0->text() << vxio::color::White << "'";

    vxio::axt::clear_static_pool();
    //game.run();
    delete token;
    logger::clear([](rem& r){
       std::cout << r.cc() << "\n";
    });

    return 0;
}
