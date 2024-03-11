/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <Particle.hpp>

const float Particle::BH_RADIUS = 20;

/**
 * @brief Constructor
 * @param position Vector describing the coordinates of the particle
 * @param radius Radius of the particle (in pixels), we will use the radius as mass in formulas
 * @param speed The speed of a particle
 * @param direction Vector describing the direction of the particle
 * @param fixed Whether the particle's position is fixed or not
*/
Particle::Particle(Vector<float> position, float radius, Vector<float> speed, Vector<float> direction, bool fixed)
    : _position {position}
    , _radius {radius}
    , _fixed {fixed}
    , _speed {speed}
    , _direction {direction}
    {}

Vector<float> Particle::getPosition() const{
    return _position;
}

/**
 * @brief Radius accessor
*/
float Particle::getRadius() const{
    return _radius;
}

/**
 * @brief Calculate the area
*/
float Particle::getArea() const{
    return M_PI * pow((_radius),2);
}

bool Particle::isInContact(Particle& other) {
    c3ga::Mvec<float> center = c3ga::point<float>(_position.x, _position.y, 0.f);
    c3ga::Mvec<float> center_other = c3ga::point<float>(other._position.x, other._position.y, 0.f);
    float distance = (center - center_other).norm();

    // float distance = sqrt(pow(_position.x - other._position.x, 2) + pow(_position.y - other._position.y, 2));
    float sum_of_radius = _radius + other.getRadius();
    return distance <= sum_of_radius;
}

/**
 * @brief Update a particle's position
*/
void Particle::updatePosition(){
    // TODO: apply attraction by other particles (Maybe in another function...)
    if (!_fixed){

        Vector<float> distances = {_direction.x - _position.x, _direction.y - _position.y};
        float distance = sqrt(pow(distances.x, 2) + pow(distances.y, 2));

        distances.x /= distance;
        distances.y /= distance;

        // float factor = _speed / distance; // Speed factor by which the particle moves

        // float step_x = distances.x * factor;
        // float step_y = distances.y * factor;

        _speed.x = distance / 1000000;
        _speed.y = distance / 1000000;

        float step_x = distances.x * _speed.x;
        float step_y = distances.y * _speed.y;

        _position.x = _position.x + step_x; 
        _position.y = _position.y + step_y;

        // Updating the direction to keep the particle moving
        // _direction.x += step_x;
        // _direction.y += step_y;
    }
}

/**
 * @brief Create a set of particle with random directions,
 *        including nb particles + the center fixed black hole
 * @param nb The number of particles to create
 * @param radius The radius of the particles to create
 * @param w_width The width of the window
 * @param w_height The height of the window
*/
std::vector<Particle> Particle::createParticleSet(uint nb, float radius, uint w_width, uint w_height){
    std::vector<Particle> particles;

    // Adding black hole

    Vector<float> black_hole_pos = {(float) w_width / 2, (float) w_height / 2};

    particles.push_back(Particle(black_hole_pos, BH_RADIUS,
                                Vector<float>{0, 0},
                                Vector<float>{0, 0},
                                true ));

    // The size of the area in which the particles positions can be generated in
    int spawnAreaX = w_width * 2;
    int spawnAreaY = w_height * 2;

    for (size_t i = 0; i < nb; i++){
        Vector<float> position = {(float) ((rand() % spawnAreaX) - (spawnAreaX / 2) + black_hole_pos.x),
                                  (float) ((rand() % spawnAreaY) - (spawnAreaY / 2) + black_hole_pos.y)};

        // TODO Generate random direction in a cleaner way.        
        Vector<float> direction = {(float) (rand() % w_width * 5000), (float) (rand() % w_height * 5000)};

        direction.x = (rand() % 2 == 1 ? -direction.x : direction.x);
        direction.y = (rand() % 2 == 1 ? -direction.y : direction.y);

        particles.push_back(Particle(position, radius, Vector<float>{3,3}, direction)); // Maybe random speed?
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
const double Particle::G = 6.67430 * 800; // The gravitational constant in Newton's Law of Universal Gravitation

/**
 * @brief Compute the gravitational force between two particle using Newton's equation for universal gravitation
 * @param p1 Reference to the first particle
 * @param p2 Reference to the second particle
*/
double Particle::computeGravitationalForce(Particle& p1, Particle& p2){
    Vector<float> distances = {p1._position.x - p2._position.x, p1._position.y - p2._position.y};
    float distance = sqrt(pow(distances.x, 2) + pow(distances.y, 2));
    return distance == 0 ? 0 : (G * p1._radius * p2._radius) / pow(distance, 2);
}

/**
 * @brief Apply the gravity of all the particle on all other particles
 * @param particles Reference to a vector of particle
*/
void Particle::applyGravity(std::vector<Particle>& particles){
    for (Particle& p : particles){
        Vector<float> total_force = {0, 0};

        for (Particle& other : particles){

            if (&p != &other){ 

                // Distance between the two particles
                double F = computeGravitationalForce(p, other);

                // Vector from p to other
                Vector<float> force_direction = {other._position.x - p._position.x, other._position.y - p._position.y};

                total_force.x += F * force_direction.x;
                total_force.y += F * force_direction.y;
            }
        }

        p._speed.x += (total_force.x * p._speed.x) /p._direction.x;
        p._speed.y += (total_force.y * p._speed.y) /p._direction.y;

        p._direction.x += total_force.x;
        p._direction.y += total_force.y;
    }
}

/**
 * @brief Apply the collision of all the particle on all other particles
 * @param particles Reference to a vector of particle
*/
void Particle::applyCollision(std::vector<Particle>& particles){
    float new_area;
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

                    

                    // Fast grow
                    //p._radius += other._radius

                    // Area accurate grow
                    new_area = p.getArea() + other.getArea();
                    p._radius = sqrt(new_area/M_PI);

                    // Medium grow
                    //p._radius += other._radius/std::log(p._radius);
                    
                    // Slow grow
                    //p._radius += std::log(1+other._radius/p._radius);

                    //p._speed /= 2;
                    p._direction = Vector<float>{(other._direction.x + p._direction.x) / 2, (other._direction.y + p._direction.y) / 2};
                }
            }
        }
    }

    particles.erase(std::remove_if(particles.begin(),particles.end(), [](const Particle& p) {return p._toRemove;}), particles.end());
}