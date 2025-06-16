#ifndef __SCREEN_H
#define __SCREEN_H

#include "SDL2/SDL.h"
#include "stdint.h"

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

class Screen
{   
    int screen_w;
    int screen_h;

    int particle_size;
    int scale;

    int grid_w;
    int grid_h;
    std::vector<std::vector<uint8_t>>* grid;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    public:
        SDL_Event event;

        Screen(int screen_w, int screen_h, int particle_size, int scale = 1);
        ~Screen();

        void set_pixel(int x, int y, uint8_t value);
        void paint(int x, int y, uint8_t value);
        void update();
        void draw();
};

#endif