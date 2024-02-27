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

        void update_window();

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

        void draw_particle(Particle particle);

        void draw_particles(std::vector<Particle>& particles);

        /**
         * @brief Set the color used for the drawings
         * @param r Value for the red component
         * @param g Value for the green component
         * @param b Value for the blue component
         * @param a Value for the opacity component
        */
        void set_rendering_color(uint r, uint g, uint b, uint a);



    private:
        SDL_Window* window;
        SDL_Surface* w_surface;
        SDL_Renderer* gRenderer;
        uint w_width;
        uint w_height;
};

#endif