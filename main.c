#include <stdio.h>

#include "sdl_context.h"
#include "game.h"
#include "gfx.h"


int WIDTH = 48;
int HEIGHT = 84;
int SCALE = 8;
const char* TITLE = "Untitled";

int main(int argc, char* argv[]) {

    printf("Welcome to my game!\n");

    if(sdl_init(WIDTH, HEIGHT, SCALE, TITLE) == -1) {

        sdl_destroy();
        return -1;
    }
    gfx_init();

    while(1) {
        
        game_tick();
        gfx_draw();
        sdl_update();

        if(sdl_poll_events() == -1)
            break;
    }

    sdl_destroy();

    return 0;
}