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

                SDL_FillRect( w_surface, NULL, SDL_MapRGB( (w_surface)->format, 0, 0, 0 ) );
                
                SDL_UpdateWindowSurface( window );

                //Create renderer for window
                gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
                if( gRenderer == NULL )
                {
                    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                    exit(1);
                }
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

/**
 * @brief Update the screen with all the rendering
*/
void Window::update_window(){
    SDL_SetRenderDrawColor( gRenderer, 0, 0xFF, 0xFF, 0xFF );
    SDL_UpdateWindowSurface( window );
    SDL_RenderPresent( gRenderer );
}

/**
 * @brief Clears the window of all rendered targets
*/
void Window::clear_window(){
    // TODO : Code color management better ...
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF ); // Set color to black when clearing window
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor( gRenderer, 0, 0xFF, 0xFF, 0xFF );  // Set color back to drawing color
}

/**
 * @brief The class constructor
 * @param width Width of the window
 * @param height Height of the window
*/
Window::Window(uint width, uint height)
    : w_width {width}
    , w_height {height}
    {
        init();
    }

/**
 * @brief draw a circle on the window (This is an adaptation of the Midpoint circle algorithm)
 * @param x0 the x coordinate of the center of the circle
 * @param y0 the y coordinate of the center of the circle
 * @param radius the radius of the circle (in pixels)
*/
void Window::draw_circle(int x0, int y0, uint radius){
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        SDL_RenderDrawPoint(gRenderer ,x0 + x, y0 + y);
        SDL_RenderDrawPoint(gRenderer ,x0 + y, y0 + x);
        SDL_RenderDrawPoint(gRenderer ,x0 - y, y0 + x);
        SDL_RenderDrawPoint(gRenderer ,x0 - x, y0 + y);
        SDL_RenderDrawPoint(gRenderer ,x0 - x, y0 - y);
        SDL_RenderDrawPoint(gRenderer ,x0 - y, y0 - x);
        SDL_RenderDrawPoint(gRenderer ,x0 + y, y0 - x);
        SDL_RenderDrawPoint(gRenderer ,x0 + x, y0 - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

/**
 * @brief Draw a particle
 * @param particle The particle to be drawn
*/
void Window::draw_particle(Particle particle){
    Vector pos = particle.getPosition();
    uint size = particle.getSize();
    draw_circle(pos.x, pos.y, size);
}

/**
 * @brief Draw all the particles in the vector
 * @param particles A vector of particles
*/
void Window::draw_particles(std::vector<Particle>& particles){
    for (Particle& p : particles){
        set_rendering_color(0, 0, 255, 255);

        for (Particle& other : particles){
            if (&p != &other && p.isInContact(other)){
                set_rendering_color(255, 0, 255, 255);  // Draw particle in pink if they are in contact
            }
        }
        draw_particle(p);
    }
}

/**
 * @brief Set the color used for the drawings
 * @param r Value for the red component
 * @param g Value for the green component
 * @param b Value for the blue component
 * @param a Value for the opacity component
*/
void Window::set_rendering_color(uint r, uint g, uint b, uint a){
    SDL_SetRenderDrawColor( gRenderer, r, g, b, a );
}
