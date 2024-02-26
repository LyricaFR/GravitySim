/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <Particle.hpp>

/**
 * @brief Constructor
 * @param position Vector describing the coordinates of the particle
 * @param size Radius of the particle (in pixels)
 * @param speed The speed of a particle
 * @param direction Vector describing the direction of the particle
 * @param fixed Whether the particle's position is fixed or not
*/
Particle::Particle(Vector position, uint size, float speed, Vector direction, bool fixed)
    : _position {position}
    , _size {size}
    , _fixed {fixed}
    , _speed {speed}
    , _direction {direction}
    {}

Vector Particle::getPosition() const{
    return _position;
}

/**
 * @brief Size accessor
*/
uint Particle::getSize() const{
    return _size;
}