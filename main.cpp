#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "Dino.h"
#include "Ground.h"
#include "Obstacles.h"
#include "Scores.h"
#include "SoundManager.h"

// Global variables
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Sound* soundManager = NULL;
Dino* dino = NULL;
Ground* ground = NULL;
Obstacles* obstacles = NULL;
Scores* scores = NULL;

bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    
    // Create window
    window = SDL_CreateWindow("Dino Game", 
                              SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, 
                              windowSize_x, 
                              windowSize_y, 
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void loadGame() {
    // Initialize game objects
    soundManager = new Sound();
    dino = new Dino(renderer, soundManager);
    ground = new Ground(renderer);
    obstacles = new Obstacles(renderer);
    scores = new Scores(renderer, soundManager);
}

void handleEvents(SDL_Event& event, bool& quit, int& mouseX, int& mouseY, bool& mousePressed) {
    if (event.type == SDL_QUIT) {
        quit = true;
    }
    
    // Track mouse position
    if (event.type == SDL_MOUSEMOTION) {
        mouseX = event.motion.x;
        mouseY = event.motion.y;
    }
    
    // Track mouse button state
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            mousePressed = true;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            mousePressed = false;
        }
    }
}

void updateGame(Uint32 currentTime, int mouseX, int mouseY, bool& mousePressed) {
    if (playerDead) {
        // Check if restart was clicked
        SDL_Rect restartRect = {static_cast<int>(windowSize_x) / 2 - 36, static_cast<int>(windowSize_y) / 2, 72, 64};
        bool restartClicked = mousePressed && 
                             mouseX >= restartRect.x && mouseX <= restartRect.x + restartRect.w &&
                             mouseY >= restartRect.y && mouseY <= restartRect.y + restartRect.h;
        
        if (restartClicked) {
            ground->reset();
            obstacles->reset();
            dino->reset();
            scores->reset(renderer);
            
            playerDead = false;
            mousePressed = false;
        }
    } else {
        ground->updateGround();
        obstacles->update(currentTime);
        dino->update(currentTime, obstacles->obstacles);
        scores->update(renderer);
    }
}

void render() {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // Render game objects
    ground->render(renderer);
    obstacles->render(renderer);
    scores->render(renderer);
    dino->render(renderer);
    
    // Draw game over screen if player is dead
    if (playerDead) {
        // Render "Game Over" text
        TTF_Font* font = TTF_OpenFont("assets/Fonts/Font.ttf", 24);
        if (font) {
            SDL_Color textColor = {83, 83, 83, 255}; // Dark gray
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game Over", textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            
            SDL_Rect textRect;
            textRect.x = windowSize_x / 2 - textSurface->w / 2;
            textRect.y = windowSize_y / 2 - 50;
            textRect.w = textSurface->w;
            textRect.h = textSurface->h;
            
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
            TTF_CloseFont(font);
        }
        
        // Render restart button
        SDL_Rect restartRect = {static_cast<int>(windowSize_x) / 2 - 36, static_cast<int>(windowSize_y) / 2, 72, 64};
        SDL_Texture* restartTexture = IMG_LoadTexture(renderer, "assets/Images/RestartButton.png");
        if (restartTexture) {
            SDL_RenderCopy(renderer, restartTexture, NULL, &restartRect);
            SDL_DestroyTexture(restartTexture);
        }
    }
    
    // Update screen
    SDL_RenderPresent(renderer);
}

void cleanup() {
    // Free resources
    delete dino;
    delete ground;
    delete obstacles;
    delete scores;
    delete soundManager;
    
    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (!init()) {
        return -1;
    }
    
    // Load game assets
    loadGame();
    
    // Game loop variables
    bool quit = false;
    SDL_Event e;
    int mouseX = 0, mouseY = 0;
    bool mousePressed = false;
    Uint32 lastFrameTime = SDL_GetTicks();
    
    // Game loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            handleEvents(e, quit, mouseX, mouseY, mousePressed);
        }
        
        // Get current time
        Uint32 currentFrameTime = SDL_GetTicks();
        
        // Update game state
        updateGame(currentFrameTime, mouseX, mouseY, mousePressed);
        
        // Render the game
        render();
        
        // Cap frame rate to ~60 FPS
        if (currentFrameTime - lastFrameTime < 16) {
            SDL_Delay(16 - (currentFrameTime - lastFrameTime));
        }
        lastFrameTime = currentFrameTime;
    }
    
    // Clean up
    cleanup();
    
    return 0;
}