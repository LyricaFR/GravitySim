/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <Particle.hpp>
#include <math.h>

/**
 * @brief Constructor
 * @param position Vector describing the coordinates of the particle
 * @param size Radius of the particle (in pixels), we will use the size as mass in formulas
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

/**
 * @brief Update a particle's position
*/
void Particle::updatePosition(){
    // TODO: apply attraction by other particles (Maybe in another function...)
    if (!_fixed){

        Vector distances = {_direction.x - _position.x, _direction.y - _position.y};
        float distance = sqrt(pow(distances.x, 2) + pow(distances.y, 2));

        float factor = _speed / distance; // Speed factor by which the particle moves

        float step_x = distances.x * factor;
        float step_y = distances.y * factor;

        _position.x = _position.x + step_x; 
        _position.y = _position.y + step_y;

        // Updating the direction to keep the particle moving
        _direction.x += step_x;
        _direction.y += step_y;
    }
}