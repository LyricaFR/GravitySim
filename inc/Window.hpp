/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#ifndef __WINDOW__
#define __WINDOW__

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
         * @brief The class constructor
         * @param width Width of the window
         * @param height Height of the window
        */
        Window(uint width, uint height);



    private:
        SDL_Window* window;
        SDL_Surface* w_surface;
        uint w_width;
        uint w_height;
};

#endif