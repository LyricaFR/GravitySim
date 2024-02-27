/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <Particle.hpp>

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

/**
 * @brief Create a set of particle with random directions,
 *        including nb particles + the center fixed black hole
 * @param nb The number of particles to create
 * @param size The size of the particles to create
 * @param w_width The width of the window
 * @param w_height The height of the window
*/
std::vector<Particle> Particle::createParticleSet(uint nb, uint size, uint w_width, uint w_height){
    std::vector<Particle> particles;

    // Adding black hole

    particles.push_back(Particle(Vector{(float) w_width / 2, (float) w_height / 2}, 4 * size, 0, Vector{0, 0}, true ));

    for (size_t i = 0; i < nb; i++){
        Vector position = {(float) (rand() % w_width), (float) (rand() % w_height)};
        Vector direction = {(float) (rand() % w_width), (float) (rand() % w_height)};
        particles.push_back(Particle(position, size, 1, direction)); // Maybe random speed?
    }

    return particles;
}

/**
 * @brief Update the position of all particles contained in the vector
 * @param particles Reference to a vector of particle
*/
void Particle::updateParticlesPosition(std::vector<Particle>& particles){
    for (Particle& p : particles){
        p.updatePosition();
    }
}