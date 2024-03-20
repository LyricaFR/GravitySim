/*
Author: Kevin QUACH 
Created: 24/02/2024
*/

#include <iostream>
#include <Window.hpp>

int main(void){

    std::srand(std::time(0));

    /* Values used for nanosleep */
    /* 1 frame per 16.6 ms is equal to 60 fps */
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 16000000; /* 0.016 sec */

    /* Event handler */
    SDL_Event e;

    /* Window size */
    uint w_width = 600;
    uint w_height = 600;

    Vector<int> mouse_pos = {0, 0}; 
    bool mouse_button_down = false;

    /* Create window */
    Window window = Window(w_width, w_height);
    
    bool EXIT = false;
    /* Test */
    // Generating particles
    auto particles = Particle::createParticleSet(100, 10, w_width, w_height);
    window.set_rendering_color(0, 255, 255, 255);
    int exploded = 0;
    while (!EXIT){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_ESCAPE){
                    EXIT = true;
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN){
                if (!mouse_button_down){
                    mouse_button_down = true;
                    SDL_GetMouseState( &mouse_pos.x, &mouse_pos.y );
                }
            }

            if (e.type == SDL_MOUSEBUTTONUP){
                if (mouse_button_down){
                    mouse_button_down = false;
                }
            }

            if (e.type == SDL_MOUSEMOTION){
                if (mouse_button_down){
                    window.move_window(e.motion.x - mouse_pos.x, e.motion.y - mouse_pos.y);
                    mouse_pos.x = e.motion.x;
                    mouse_pos.y = e.motion.y;
                }
            }
        }

        Particle::explode(particles, 75, w_width, w_height, exploded);
        Particle::applyGravity(particles);
        Particle::applyCollision(particles);
        window.draw_particles(particles);
        window.update_window();
        Particle::updateParticlesPosition(particles);
        nanosleep(&tim, NULL);
        window.clear_window();
        /*if (exploded) {
            exploded += 1;
        }*/
        //std::cout << exploded << std::endl;
    }

    window.close_window();

    return 0;
}