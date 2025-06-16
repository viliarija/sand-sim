#include "screen.h"

Screen::Screen(int screen_w, int screen_h, int particle_size, int scale)
{   
    this->scale = scale;
    this->particle_size = particle_size;
    this->screen_w = screen_w;
    this->screen_h = screen_h;

    LOG("Initializing: screen->grid");

    if (!(screen_w % particle_size) && !(screen_h % particle_size))
    {   
        grid_w = screen_w / particle_size;
        grid_h = screen_h / particle_size;

        grid = new std::vector<std::vector<uint8_t>>(grid_w, std::vector<uint8_t>(grid_h, 0));
    } else 
    {
        LOG("Error: Screen W or H not divisible by particle size");
    }

    LOG("Initializing: screen->window");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(screen_w*scale, screen_h*scale, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, scale, scale);

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
}
Screen::~Screen()
{

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

}

void Screen::set_pixel(int x, int y, uint8_t value)
{   
    if(x < grid_w && !(x < 0))
    {      
        if(value)
        {
            if(!(*grid)[x][y])
            {
                (*grid)[x][y] = value;
            }
        } else 
        {
            (*grid)[x][y] = 0;
        }
    }
}
void Screen::paint(int mouseX, int mouseY, uint8_t value)
{
            int x = std::round(mouseX / scale / particle_size);
            int y = std::round(mouseY / scale / particle_size);

            set_pixel(x,y, value);
            set_pixel(x+1,y, value);
            set_pixel(x+1,y+1, value);
            set_pixel(x,y+1, value);
}
void Screen::update()
{   
    uint8_t value;
    for(int x{}; x < grid_w; ++x) 
    {   
        for(int y{grid_h-1}; !(y < 0); --y)
        {   
            value = (*grid)[x][y];
            if(value != 0)
            {   
                if(y+1 < grid_h)
                {
                    if((*grid)[x][y+1] == 0)
                    {
                        (*grid)[x][y+1] = value;
                        (*grid)[x][y]   = 0;
                    } else 
                    {   
                        int choices[2]{-1,1};
                        int rand_value = choices[rand()%2];
                        if(x+rand_value < grid_w && !(x+rand_value < 0))
                        {
                            if((*grid)[x+rand_value][y+1] == 0) 
                            {
                                (*grid)[x+rand_value][y+1] = value;
                                (*grid)[x][y] = 0;
                            }
                        } else
                        {
                            if((*grid)[x-rand_value][y+1] == 0) 
                            {
                                (*grid)[x-rand_value][y+1] = value;
                                (*grid)[x][y] = 0;
                            }
                        }
                    }
                }   
            }
        }
    }
}
void Screen::draw()
{   
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    uint8_t value;
    for(int x{}; x < grid_w; ++x) 
    {
        for(int y{}; y < grid_h; ++y)
        {   
            value = (*grid)[x][y];
            if(value != 0)
            {   
                SDL_SetRenderDrawColor(renderer, value,value,value, 255);
                for(int k{}; k < particle_size; ++k)
                {
                    for(int l{}; l < particle_size; ++l)
                    {
                        SDL_RenderDrawPoint(renderer, x*particle_size+k, y*particle_size+l);
                    }

                }
            }

        }
    }
    SDL_RenderPresent(renderer);
}