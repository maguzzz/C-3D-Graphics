#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *color_buffer_texture = NULL;
uint32_t *color_buffer = NULL;

int WindowHeight = 800;
int WindowWidth = 700;

bool initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL COULD NOT INITIALIZE!");
        return false;
    }

    // Get Window Height
    SDL_DisplayMode display_node;
    SDL_GetCurrentDisplayMode(
        0,
        &display_node);

    WindowHeight = display_node.h;
    WindowWidth = display_node.w;

    // Create SDL Window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WindowWidth,
        WindowHeight,
        SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        fprintf(stderr, "ERROR Creating SDL WINDOW  ");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        fprintf(stderr, "ERROR Renderer Could not be Created");
        return false;
    }

    return true;
}

void destroy_window(void)
{
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render_color_buffer(void)
{
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(sizeof(uint32_t) * WindowWidth));

    SDL_RenderCopy(
        renderer,
        color_buffer_texture,
        NULL,
        NULL

    );
}

void clear_color_buffer(uint32_t color)
{
    for (int y = 0; y < WindowHeight; y++)
    {
        for (int x = 0; x < WindowWidth; x++)
        {
            color_buffer[(WindowWidth * y) + x] = color;
        }
    }
}

void draw_grid(uint32_t color, int gridSize)
{
    for (int y = 0; y < WindowHeight; y++)
    {
        for (int x = 0; x < WindowWidth; x++)
        {
            if (y % gridSize == 0 || x % gridSize == 0)
            {
                color_buffer[(WindowWidth * y) + x] = color;
            }
        }
    }
};

void draw_rect(uint32_t color, int x_pos, int y_pos, int height, int width)
{
    for (int y = 0; y < WindowHeight; y++)
    {
        for (int x = 0; x < WindowWidth; x++)
        {
            if (x_pos + width > WindowWidth || y_pos + height > WindowHeight)
            {
                color_buffer[3] = 0x00FFFFFF;
                return;
            }

            if ((x > x_pos && x < x_pos + width) && (y > y_pos && y < y_pos + height))
            {
                color_buffer[(WindowWidth * y) + x] = color;
            }
        }
    }
}

void draw_pixel(uint32_t color, int x_pos, int y_pos)
{

    if (x_pos > WindowWidth || y_pos > WindowHeight)
    {
        color_buffer[6] = 0xFFFFFFF;
        return;
    }

    color_buffer[(WindowWidth * y_pos) + x_pos] = color;
}
