#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


extern bool is_running;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *color_buffer_texture;
extern uint32_t *color_buffer;

extern int WindowHeight;
extern int WindowWidth;


bool initialize_window(void);
void destroy_window(void);

void render_color_buffer(void);
void clear_color_buffer(uint32_t color);

void draw_grid(uint32_t color, int gridSize);
void draw_rect(uint32_t color, int x_pos, int y_pos, int height, int width);
void draw_pixel(uint32_t color, int x_pos, int y_pos);

#endif