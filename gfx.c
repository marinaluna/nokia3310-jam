#include "gfx.h"
#include "sdl_context.h"

#include <SDL2/SDL.h>

static Uint32 gColors[2] = {
    0xFFC7F0D8,
    0xFF43523D
};

void gfx_draw() {
    Uint32* pixels = (Uint32*) sdl_ctx.drawSurface->pixels;
    int w = sdl_ctx.drawSurface->w;
    int h = sdl_ctx.drawSurface->h;
    int x, y;
    int color = 0;

    for(y = 0; y < h; y++) {
        color ^= 1;
        for(x = 0; x < w; x++) {
            color ^= 1;
            pixels[x + (y*w)] = gColors[color];
        }
    }
}