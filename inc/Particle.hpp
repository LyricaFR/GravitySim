/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#ifndef __PARTICLE__
#define __PARTICLE__

#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

struct Vector {
    float x;
    float y;
};


class Particle{
    public:

        /**
         * @brief Constructor
         * @param position Vector describing the coordinates of the particle
         * @param size Radius of the particle (in pixels)
         * @param speed The speed of a particle
         * @param direction Vector describing the direction of the particle
         * @param fixed Whether the particle is fixed or not
         * @param toRemove Whether the particle should be removed
        */
        Particle(Vector position, float size, Vector speed, Vector direction, bool fixed = false);

        /**
         * @brief Position accessor
        */
        Vector getPosition() const;

        /**
         * @brief Size accessor
        */
        float getSize() const;

        /**
         * @brief Calculate the area
        */
        float getArea() const;

        /**
         * @brief Check whether the particle is in contact with another
        */
        bool isInContact(Particle& other);

        /**
         * @brief Update a particle's position
        */
        void updatePosition();

        /**
         * @brief Create a set of particle with random directions,
         *        including nb particles + the center fixed black hole
         * @param nb The number of particles to create
         * @param size The size of the particles to create
         * @param w_width The width of the window
         * @param w_height The height of the window
        */
        static std::vector<Particle> createParticleSet(uint nb, float size, uint w_width, uint w_height);

        /**
         * @brief Update the position of all particles contained in the vector
         * @param particles Reference to a vector of particle
        */
        static void updateParticlesPosition(std::vector<Particle>& particles);

        static double computeGravitationalForce(Particle& p1, Particle& p2);

        /**
         * @brief Apply the gravity of all the particle on all other particles
         * @param particles Reference to a vector of particle
        */
        static void applyGravity(std::vector<Particle>& particles);

        /**
         * @brief Apply the collision of all the particle on all other particles
         * @param particles Reference to a vector of particle
        */
        static void applyCollision(std::vector<Particle>& particles);

    private:
        Vector _position;
        float _size;
        bool _fixed;  // Whether the particle can move or not
        Vector _speed;
        Vector _direction;
        bool _toRemove = false;

        static const double G;
        static const float BH_RADIUS;
};

#endif