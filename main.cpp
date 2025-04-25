#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "GameState.h"

int main(int argc, char* argv[]) {
    // Initialize SDL subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return -1;
    }
    
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return -1;
    }
    
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return -1;
    }
    
    // Create window
    SDL_Window* window = SDL_CreateWindow("Dino Game", 
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         windowSize_x, 
                                         windowSize_y, 
                                         SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    // Initialize game state
    GameState gameState(renderer);
    
    // Game loop variables
    bool quit = false;
    SDL_Event e;
    Uint32 lastFrameTime = SDL_GetTicks();
    
    // Game loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            gameState.handleEvents(e);
        }
        
        // Get current time
        Uint32 currentFrameTime = SDL_GetTicks();
        
        // Update game state
        gameState.update(currentFrameTime);
        
        // Render the game
        gameState.render(renderer);
        
        // Cap frame rate to ~60 FPS
        if (currentFrameTime - lastFrameTime < 16) {
            SDL_Delay(16 - (currentFrameTime - lastFrameTime));
        }
        lastFrameTime = currentFrameTime;
    }
    
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}