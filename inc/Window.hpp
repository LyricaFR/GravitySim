/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#ifndef __WINDOW__
#define __WINDOW__

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Particle.hpp>

class Window{

    public:

        /**
         * @brief Initiates a SDL window
        */
        void init();

        /**
         * @brief Destroys the window and clean up all initialized SDL libraries
        */
        void close_window();

        /**
         * @brief Update the screen with all the rendering
        */
        void update_window();

        /**
         * @brief Clears the window of all rendered targets
        */
        void clear_window();

        /**
         * @brief The class constructor
         * @param width Width of the window
         * @param height Height of the window
        */
        Window(uint width, uint height);

        /**
         * @brief draw a circle on the window (This is an adaptation of the Midpoint circle algorithm)
         * @param x0 the x coordinate of the center of the circle
         * @param y0 the y coordinate of the center of the circle
         * @param radius the radius of the circle (in pixels)
        */
        void draw_circle(int x0, int y0, uint radius);

        /**
         * @brief Draw a particle
         * @param particle The particle to be drawn
        */
        void draw_particle(Particle particle);

        /**
         * @brief Draw all the particles in the vector
         * @param particles A vector of particles
        */
        void draw_particles(std::vector<Particle>& particles);

        /**
         * @brief Set the color used for the drawings
         * @param r Value for the red component
         * @param g Value for the green component
         * @param b Value for the blue component
         * @param a Value for the opacity component
        */
        void set_rendering_color(uint r, uint g, uint b, uint a);

        /**
         * @brief Move the point of focus of the window by adding x and y to the current position
         * @param x The number of pixel to move horizontally from
         * @param y The number of pixel to move vertically from
        */
        void move_window(int x, int y);



    private:
        SDL_Window* window;
        SDL_Surface* w_surface;
        SDL_Renderer* gRenderer;
        uint w_width;
        uint w_height;
        Vector<int> current_pos;  // Coordinates of the upper left corner, (0, 0) by default
};

#endif