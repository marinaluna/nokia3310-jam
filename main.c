#include <stdio.h>
#include <SDL2/SDL.h>


static int WIDTH = 48;
static int HEIGHT = 84;
static int SCALE = 4;
static const char* GAMENAME = "Untitled";

int main(int argc, char* argv[]) {

    SDL_Window* window;
    int running = 1;
    SDL_Event event;

    printf("Welcome to my game!\n");

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    
        printf("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(GAMENAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        WIDTH * SCALE, HEIGHT * SCALE, 0);
    if(window == NULL) {
    
        printf("Failed to initialize window or renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    while(running == 1) {
        
        while(SDL_PollEvent(&event)) {

            switch(event.type) {
                case SDL_QUIT:
                    running = 0;
                default:
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}