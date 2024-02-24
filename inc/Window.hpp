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

        void close_window();

        /**
         * @brief The class constructor
        */
        Window(uint width, uint height);



    private:
        SDL_Window* window;
        SDL_Surface* w_surface;
        uint w_width;
        uint w_height;
};

#endif