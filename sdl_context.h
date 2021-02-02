#ifndef __SDL_SURFACE_H_
#define __SDL_SURFACE_H_

#include <SDL2/SDL.h>

typedef struct SDLContext {
    SDL_Window* window;
    SDL_Surface* drawSurface;
    SDL_Surface* windowSurface;
    SDL_Event event;
} SDLContext;

extern SDLContext sdl_ctx;


int sdl_init(int w, int h, int scale, const char* title);
void sdl_update();
int sdl_poll_events();
void sdl_destroy();

#endif // __SDL_SURFACE_H_