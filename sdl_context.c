#include "sdl_context.h"
#include "gfx.h"

#include <stdio.h>


SDLContext sdl_ctx;


int sdl_init(int w, int h, int scale, const char* title) {

    int rmask, gmask, bmask, amask;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    
        printf("Failed to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    sdl_ctx.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  w * scale, h * scale, 0);
    if(sdl_ctx.window == NULL) {
    
        printf("Failed to initialize window: %s", SDL_GetError());
        return -1;
    }

    sdl_ctx.windowSurface = SDL_GetWindowSurface(sdl_ctx.window);
    if(sdl_ctx.windowSurface == NULL) {

        printf("Failed to get window's surface: %s", SDL_GetError());
        return -1;
    }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xFF000000;
    gmask = 0x00FF0000;
    bmask = 0x0000FF00;
    amask = 0x000000FF;
#else
    rmask = 0x000000FF;
    gmask = 0x0000FF00;
    bmask = 0x00FF0000;
    amask = 0xFF000000;
#endif

    sdl_ctx.drawSurface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
    if(sdl_ctx.drawSurface == NULL) {

        printf("Failed to create draw surface: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

void sdl_update() {
    SDL_BlitScaled(sdl_ctx.drawSurface, NULL, sdl_ctx.windowSurface, NULL);
    SDL_UpdateWindowSurface(sdl_ctx.window);
}

int sdl_poll_events() {

    while(SDL_PollEvent(&sdl_ctx.event)) {
        switch(sdl_ctx.event.type) {

            case SDL_KEYDOWN: {
                switch(sdl_ctx.event.key.keysym.sym) {
                    case SDLK_w:
                        topViewport.y += 1;
                        break;
                    case SDLK_s:
                        topViewport.y -= 1;
                        if(topViewport.y < 0) {
                            topViewport.y = 0;
                        }
                        break;
                    case SDLK_d:
                        topViewport.x += 1;
                        break;
                    case SDLK_a:
                        topViewport.x -= 1;
                        if(topViewport.x < 0) {
                            topViewport.x = 0;
                        }
                        break;
                    
                    case SDLK_UP:
                        bottomViewport.y += 1;
                        break;
                    case SDLK_DOWN:
                        bottomViewport.y -= 1;
                        if(bottomViewport.y < 0) {
                            bottomViewport.y = 0;
                        }
                        break;
                    case SDLK_RIGHT:
                        bottomViewport.x += 1;
                        break;
                    case SDLK_LEFT:
                        bottomViewport.x -= 1;
                        if(bottomViewport.x < 0) {
                            bottomViewport.x = 0;
                        }
                        break;
                }
                break;
            }

            case SDL_QUIT:
                return -1;
            
            default:
                break;
        }
    }

    return 0;
}

void sdl_destroy() {

    if(sdl_ctx.drawSurface != NULL) {
        SDL_FreeSurface(sdl_ctx.drawSurface);
    }
    if(sdl_ctx.window != NULL) {
        SDL_DestroyWindow(sdl_ctx.window);
    }
    SDL_Quit();
}