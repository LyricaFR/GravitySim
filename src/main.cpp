/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <iostream>
#include <Window.hpp>

int main(void){

    std::srand(std::time(0));

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
    // Generating particles
    auto particles = Particle::createParticleSet(2, 10, w_width, w_height);
    window.set_rendering_color(0, 255, 255, 255);

    while (!EXIT){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_ESCAPE){
                    EXIT = true;
                }
            }
        }
        window.draw_particles(particles);
        window.update_window();
        Particle::updateParticlesPosition(particles);
        nanosleep(&tim, NULL);
        window.clear_window();
    }

    window.close_window();

    return 0;
}