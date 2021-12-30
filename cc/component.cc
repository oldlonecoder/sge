//
// Created by oldlonecoder on 21-12-11.
//

#include <sge/component.h>


namespace sge
{

transform::transform(float angle_, float radius_):
speed({0.f,0.f}), angle(angle_), radius(radius_)
{
}


shape::shape(float radius_, int pts_, const sf::Color &fill, const sf::Color& outline_, float thck_)
{

}
shape::~shape()
{
    if(_type == shape::type::circle)
        delete _circle;
    else
        delete _rec;
}

}
