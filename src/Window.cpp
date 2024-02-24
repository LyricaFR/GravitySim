/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <Window.hpp>


/**
 * @brief Initiates a SDL window
*/
void Window::init(){
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) < 0 )
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }
    
    else
    {
        window = SDL_CreateWindow( "GravitySim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_width, w_height, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            exit(1);
        }
        else
        {

            /* Initiate SLD Image */
            if (!IMG_Init(IMG_INIT_PNG)){
                fprintf(stderr, "Couldn't initialize SDL_image! SDL_Error: %s\n", IMG_GetError() );
                exit(1);
            }
            else{
                w_surface = SDL_GetWindowSurface( window );

                SDL_FillRect( w_surface, NULL, SDL_MapRGB( (w_surface)->format, 200, 200, 200 ) );
                
                SDL_UpdateWindowSurface( window );
            }
            
        }

    }
}

/**
 * @brief Destroys the window and clean up all initialized SDL libraries
*/
void Window::close_window(){
    SDL_DestroyWindow( window );
    SDL_Quit();
}

Window::Window(uint width, uint height)
    : w_width {width}
    , w_height {height}
    {
        init();
    }
