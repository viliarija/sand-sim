#include <iostream>
#include "SDL2/SDL.h"
#include "screen.h"

const int SCREEN_W{620};
const int SCREEN_H{400};
const int PARTICLE_SIZE{5};

const int TARGET_FRAME_RATE = 60;
const int DELAY_TIME = 1000 / TARGET_FRAME_RATE;

int main()
{
    Screen screen{SCREEN_W, SCREEN_H, PARTICLE_SIZE, 4};

    uint8_t cur_color = 255;
    int modifyer = 1;

    bool mouse_down_l = false;
    bool mouse_down_r = false;
    bool running = true;

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    while(running)
    {
        Uint32 frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&(screen.event)))
        {   
            switch(screen.event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(screen.event.button.button == SDL_BUTTON_LEFT) mouse_down_l = true;
                    if(screen.event.button.button == SDL_BUTTON_RIGHT) mouse_down_r = true;
                    break;

                case SDL_MOUSEBUTTONUP:
                    if(screen.event.button.button == SDL_BUTTON_LEFT) mouse_down_l = false;
                    if(screen.event.button.button == SDL_BUTTON_RIGHT) mouse_down_r = false;
                    break;

            }
        }
        if (mouse_down_l)
        {   
            int mouseX , mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            screen.paint(mouseX, mouseY, cur_color);

        } else if (mouse_down_r)
        {
            int mouseX , mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            screen.paint(mouseX, mouseY, 0);
        }
        screen.update();
        screen.draw();
    
        if ((cur_color + modifyer) < 100 || !((cur_color + modifyer) < 255))
        {
            modifyer *= -1;
        }
        cur_color += modifyer;

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME) 
        {
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }

    return 0;
}