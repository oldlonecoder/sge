//#include "game.h"
#include <iostream>
#include <sge/sge.h>


int main()
{
    sge::game game = sge::game("virtualspace");
    
    game.init();
    //game.run();
    logger::clear([](rem& r){
       std::cout << r.cc() << "\n";
    });
    return 0;
}
