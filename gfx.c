#include "gfx.h"
#include "sdl_context.h"

#include <SDL2/SDL.h>


static Uint32 gColors[2] = {
    0xFFC7F0D8,
    0xFF43523D
};

static Tile gTiles[6] = {
    {   {0, 0, 0, 0, 0, 0, //
         0, 0, 0, 0, 0, 0, ///
         0, 0, 0, 0, 0, 0, ///// empty
         0, 0, 0, 0, 0, 0, ///
         0, 0, 0, 0, 0, 0, //
         0, 0, 0, 0, 0, 0} //
    },
    {   {1, 0, 0, 0, 0, 0, //
         1, 0, 0, 0, 0, 0, ///
         1, 0, 0, 0, 0, 0, ///// left tile
         1, 0, 0, 0, 0, 0, ///
         1, 0, 0, 0, 0, 0, //
         1, 0, 0, 0, 0, 0} //
    },
    {   {1, 1, 1, 1, 1, 1, //
         0, 0, 0, 0, 0, 0, ///
         0, 0, 0, 0, 0, 0, ///// top tile
         0, 0, 0, 0, 0, 0, ///
         0, 0, 0, 0, 0, 0, //
         0, 0, 0, 0, 0, 0} //
    },
    {   {0, 0, 0, 0, 0, 1, //
         0, 0, 0, 0, 0, 1, ///
         0, 0, 0, 0, 0, 1, ///// right tile
         0, 0, 0, 0, 0, 1, ///
         0, 0, 0, 0, 0, 1, //
         0, 0, 0, 0, 0, 1} //
    },
    {   {0, 0, 0, 0, 0, 0, //
         0, 0, 0, 0, 0, 0, ///
         0, 0, 0, 0, 0, 0, ///// bottom tile
         0, 0, 0, 0, 0, 0, ///
         0, 0, 0, 0, 0, 0, //
         1, 1, 1, 1, 1, 1} //
    },
    {   {1, 1, 1, 1, 1, 1, //
         1, 0, 0, 0, 0, 1, ///
         1, 0, 0, 0, 0, 1, ///// square tile
         1, 0, 0, 0, 0, 1, ///
         1, 0, 0, 0, 0, 1, //
         1, 1, 1, 1, 1, 1} //
    }
};

// These are viewed through a viewport
int topTilemap[20*20];
int bottomTilemap[20*20];
// These Viewports are 48x42
Viewport topViewport = {14, 4, 48, 42};
Viewport bottomViewport = {0, 0, 48, 42};


void gfx_init() {
    int x, y;

    for(x = 0; x < 20; x++) {
        for(y = 0; y < 20; y++) {
            topTilemap[x + (y * 20)] = 5;
        }
    }
    for(x = 0; x < 20; x++) {
        for(y = 0; y < 20; y++) {
            bottomTilemap[x + (y * 20)] = 1;
        }
    }
}

void gfx_draw() {
    Uint32* pixels = (Uint32*) sdl_ctx.drawSurface->pixels;
    int w = sdl_ctx.drawSurface->w;
    int h = sdl_ctx.drawSurface->h;
    int x, y;
    int srcX, srcY;
    int pos;
    Uint32 color;

    for(y = 0; y < h / 2; y++) {
        srcY = ((topViewport.y / 6) + (y / 6)) % 20;
        
        for(x = 0; x < w; x++) {
            srcX = ((topViewport.x / 6) + (x / 6)) % 20;
            
            Tile* tile = &gTiles[topTilemap[srcX + (srcY * 20)]];

            int px = (topViewport.x + x) % 6;
            int py = (topViewport.y + y) % 6;

            color = gColors[tile->pixels[px + (py * 6)]];
            pixels[x + (y * w)] = color;
        }
    }
    for(y = 0; y < h / 2; y++) {
        srcY = ((bottomViewport.y / 6) + (y / 6)) % 20;
        
        for(x = 0; x < w; x++) {
            srcX = ((bottomViewport.x / 6) + (x / 6)) % 20;
            
            Tile* tile = &gTiles[bottomTilemap[srcX + (srcY * 20)]];

            int px = (bottomViewport.x + x) % 6;
            int py = (bottomViewport.y + y) % 6;

            color = gColors[tile->pixels[px + (py * 6)]];
            pixels[x + ((y + h/2) * w)] = color;
        }
    }

    // Draw the line in the middle of the screen
    y = h/2;
    for(x = 0; x < w; x++) {
        pixels[x + (y * w)] = gColors[1];
    }
}