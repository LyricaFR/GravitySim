/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <Particle.hpp>

const float Particle::BH_RADIUS = 20;

/**
 * @brief Constructor
 * @param position Vector describing the coordinates of the particle
 * @param size Radius of the particle (in pixels), we will use the size as mass in formulas
 * @param speed The speed of a particle
 * @param direction Vector describing the direction of the particle
 * @param fixed Whether the particle's position is fixed or not
*/
Particle::Particle(Vector position, float size, float speed, Vector direction, bool fixed)
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
float Particle::getSize() const{
    return _size;
}

/**
 * @brief Calculate the area
*/
float Particle::getArea() const{
    return M_PI * pow(2,(_size/2));
}

bool Particle::isInContact(Particle& other) {
    float center_dist = sqrt(pow(_position.x - other._position.x, 2) + pow(_position.y - other._position.y, 2));
    float sum_of_reach = _size + other.getSize();
    return sum_of_reach >= center_dist;
}

/**
 * @brief Update a particle's position
*/
void Particle::updatePosition(){
    // TODO: apply attraction by other particles (Maybe in another function...)
    if (!_fixed){

        Vector distances = {_direction.x - _position.x, _direction.y - _position.y};
        float distance = sqrt(pow(distances.x, 2) + pow(distances.y, 2));

        _speed = (distance+1) / 1000000000000;

        // float factor = _speed / distance; // Speed factor by which the particle moves

        // float step_x = distances.x * factor;
        // float step_y = distances.y * factor;

        float step_x = distances.x * _speed;
        float step_y = distances.y * _speed;

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
std::vector<Particle> Particle::createParticleSet(uint nb, float size, uint w_width, uint w_height){
    std::vector<Particle> particles;

    // Adding black hole

    particles.push_back(Particle(Vector{(float) w_width / 2, (float) w_height / 2}, BH_RADIUS, 0, Vector{0, 0}, true ));

    for (size_t i = 0; i < nb; i++){
        Vector position = {(float) (rand() % w_width), (float) (rand() % w_height)};

        // TODO Generate random direction in a cleaner way.        
        Vector direction = {(float) (rand() % w_width * 2000), (float) (rand() % w_height * 2000)};

        direction.x = (rand() % 2 == 1 ? -direction.x : direction.x);
        direction.y = (rand() % 2 == 1 ? -direction.y : direction.y);

        particles.push_back(Particle(position, size, 3, direction)); // Maybe random speed?
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

// Real value of the gravitational constant is 6.67430e-11
const double Particle::G = 6.67430 * 500; // The gravitational constant in Newton's Law of Universal Gravitation

/**
 * @brief Compute the gravitational force between two particle using Newton's equation for universal gravitation
 * @param p1 Reference to the first particle
 * @param p2 Reference to the second particle
*/
double Particle::computeGravitationalForce(Particle& p1, Particle& p2){
    Vector distances = {p1._position.x - p2._position.x, p1._position.y - p2._position.y};
    float distance = sqrt(pow(distances.x, 2) + pow(distances.y, 2));
    return distance == 0 ? 0 : (G * p1._size * p2._size) / pow(distance, 2);
}

/**
 * @brief Apply the gravity of all the particle on all other particles
 * @param particles Reference to a vector of particle
*/
void Particle::applyGravity(std::vector<Particle>& particles){
    for (Particle& p : particles){
        Vector total_force = {0, 0};

        for (Particle& other : particles){

            if (&p != &other){ 

                // Distance between the two particles
                double F = computeGravitationalForce(p, other);

                // Vector from p to other
                Vector force_direction = {other._position.x - p._position.x, other._position.y - p._position.y};

                total_force.x += F * force_direction.x;
                total_force.y += F * force_direction.y;
            }
        }

        p._direction.x += total_force.x;
        p._direction.y += total_force.y;
    }
}

/**
 * @brief Apply the collision of all the particle on all other particles
 * @param particles Reference to a vector of particle
*/
void Particle::applyCollision(std::vector<Particle>& particles){
    float new_radius;
    for (Particle& p : particles) {
        if (p._toRemove) {
            break;  // If current particle is to be removed, no point to keep computing
        }
        for (Particle& other : particles) {
            if (&p != &other && !other._toRemove && !other._fixed) {
                if (p.isInContact(other)) {
                    if (!p._toRemove && !other._toRemove) {
                        other._toRemove = true;
                    }

                    // Area accurate grow ( NOT WORKING, reach infinity )
                    // new_radius = p.getArea() + other.getArea();
                    // p._size = sqrt(new_radius/M_PI)*2;
                    // std::cout << p._size << std::endl;


                    // Fast grow
                    //p._size += other._size/std::log(p._size);

                    // Medium grow
                    //p._size += other._size/std::log(p._size);
                    
                    // Slow grow
                    p._size += std::log(1+other._size/p._size);

                    p._speed /= 2;
                    p._direction = Vector{(other._direction.x + p._direction.x) / 2, (other._direction.y + p._direction.y) / 2};
                }
            }
        }
    }

    particles.erase(std::remove_if(particles.begin(),particles.end(), [](const Particle& p) {return p._toRemove;}), particles.end());
}