#ifndef __GFX_H_
#define __GFX_H_

#include <SDL2/SDL.h>

typedef struct Tile {
    Uint8 pixels[6*6];
} Tile;

typedef struct Viewport {
    int x, y;
    int width, height;
} Viewport;

extern int topTilemap[20*20];
extern int bottomTilemap[20*20];
extern Viewport topViewport;
extern Viewport bottomViewport;

void gfx_init();
void gfx_draw();

#endif // __GFX_H_