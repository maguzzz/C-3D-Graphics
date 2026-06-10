#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"

void setup(void)
{
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WindowWidth * WindowHeight);

    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WindowWidth,
        WindowHeight);

    if (!color_buffer)
    {
        fprintf(stderr, "MALLOC not enough memmory!");
    }
}

void proccess_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            is_running = false;
        }
        break;
    }
}

void update(void)
{
}

void render(void)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderClear(renderer);

    render_color_buffer();
    // clear_color_buffer(0x000000);
    draw_grid(0x212121, 10);
    draw_rect(0xFF00FFFF, 400, 800, 300, 500);
    draw_pixel(0xFF00FFFF, 0, 20);
    //color_buffer[1] = 0xFFFFFFFF;

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    is_running = initialize_window();

    setup();

    while (is_running)
    {
        proccess_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}