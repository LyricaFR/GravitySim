/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <iostream>
#include <Window.hpp>

int main(void){

    /* Values used for nanosleep */
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 5000000; /* 0.005 sec */

    /* Event handler */
    SDL_Event e;

    /* Window size */
    uint w_width = 1200;
    uint w_height = 800;

    /* Create window */
    Window window = Window(w_width, w_height);
    
    bool EXIT = false;
    
    /* Test */
    Vector v = {800, 500};
    Vector d = {0, 0};
    Particle p = Particle(v, 20, 0, v);
    window.set_rendering_color(0, 255, 255, 255);

    while (!EXIT){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_ESCAPE){
                    EXIT = true;
                }
            }
        }
        nanosleep(&tim, NULL);
        window.draw_particle(p);
        window.update_window();
    }

    window.close_window();

    return 0;
}