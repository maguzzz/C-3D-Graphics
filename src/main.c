#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "display.h"
#include "vector.h"

////////////////////////////////////////////////////////////
// Declaring an array of vector/points
///////////////////////////////////////////////////////////
#define N_POINTS (9 * 9 * 9)

vecc3_t cube_points[N_POINTS]; // 9x9x9 cube
vecc2_t projected_points[N_POINTS];

vecc3_t camer_position = {.x = 0, .y = 0, .z = -5};
float fov_factor = 640;

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

    int point_count = 0;
    // Starting to load array of vectors
    // From -1 to 1  in (9x9x9 cube)

    for (float x = -1; x <= 1; x += 0.25){
        for (float y = -1; y <= 1; y += 0.25){
            for (float z = -1; z <= 1; z += 0.25){
                vecc3_t new_point = {.x = x, .y = y , .z = z};
                cube_points[point_count++] = new_point;
            }
        }
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


////////////////////////////////////////////////////////////
// Function that receives a 3D vector and retuns a projected 2d pont
///////////////////////////////////////////////////////////
vecc2_t project(vecc3_t point){
    vecc2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z,
    };

    return projected_point;
}


void update(void)
{

    for(int i = 0; i < N_POINTS; i++){
        vecc3_t point = cube_points[i];

        //moving point away from camera
        point.z -= camer_position.z;

        //Project the current point
        vecc2_t projected_point = project(point);


        // Save the projected 2D vector in the array of projected points 
        projected_points[i] = projected_point;
    }
}

void render(void)
{
    render_color_buffer();
    clear_color_buffer(0x000000);

    draw_grid(0x212121, 10);

    //Project All projected points
    for(int i = 0; i <= N_POINTS; i++){
        vecc2_t projected_point = projected_points[i];
        draw_rect(
            0xFF00FF00,
            projected_point.x + (WindowWidth / 2),
            projected_point.y + (WindowHeight / 2),
            4,
            4
        );
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    is_running = initialize_window();

    setup();

    vecc3_t myvector = {2.0, 3.0, 4.0};

    while (is_running)
    {
        proccess_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}