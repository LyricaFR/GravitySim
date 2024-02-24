/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <iostream>
#include <Window.hpp>
// #include <time.h>

int main(void){

    /* Values used for nanosleep */
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 5000000; /* 0.005 sec */

    /* Event handler */
    SDL_Event e;

    Window window = Window(1200,800);
    
    bool EXIT = false;

    while (!EXIT){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_ESCAPE){
                    EXIT = true;
                }
            }
        }
        nanosleep(&tim, NULL);
    }

    window.close_window();

    return 0;
}