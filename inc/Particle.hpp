/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#ifndef __PARTICLE__
#define __PARTICLE__

#pragma once
#include <iostream>

struct Vector {
    uint x;
    uint y;
};


class Particle{
    public:

        Particle(Vector position, uint size, float speed, Vector direction, bool fixed = false)
            : _position {position}
            , _size {size}
            , _fixed {fixed}
            , _speed {speed}
            , _direction {direction}
            {}

    private:
        Vector _position;
        uint _size;
        bool _fixed;  // Whether the particle can move or not
        float _speed;
        Vector _direction;
};

#endif