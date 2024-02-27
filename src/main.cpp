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
    Vector position = {100, 100};
    Vector direction = {900, 500};
    Vector b_position = {(float) w_width/2, (float) w_height/2};
    Particle p = Particle(position, 20, 1, direction);
    Particle blackHole = Particle(b_position, 50, 1, direction, true);
    window.set_rendering_color(0, 255, 255, 255);

    while (!EXIT){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_ESCAPE){
                    EXIT = true;
                }
            }
        }
        window.draw_particle(p);
        window.draw_particle(blackHole);
        window.update_window();
        p.updatePosition();
        nanosleep(&tim, NULL);
        window.clear_window();
    }

    window.close_window();

    return 0;
}