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
using namespace std;
// Global variables
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Sound* soundManager = nullptr;
Dino* dino = nullptr;
Ground* ground = nullptr;
Obstacles* obstacles = nullptr;
Scores* scores = nullptr;

bool init(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        return false;
    }
    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    window = SDL_CreateWindow("Dino Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize_x, windowSize_y, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return true;
}

void loadGame(){
    // initialize objects
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
    
    // track mouse position
    if (event.type == SDL_MOUSEMOTION) {
        mouseX = event.motion.x;
        mouseY = event.motion.y;
    }
    
    // track mouse button state
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

void updateGame(Uint32 currentTime, int mouseX, int mouseY, bool& mousePressed){
    if (playerDead) {
        // check restart was clicked
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

void render(){
    // clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // render objects
    ground->render(renderer);
    obstacles->render(renderer);
    scores->render(renderer);
    dino->render(renderer);
    
    // draw game over screen when die
    if (playerDead) {
        // render game over text
        TTF_Font* font = TTF_OpenFont("assets/Fonts/Font.ttf", 24);
        if (font) {
            SDL_Color textColor = {83, 83, 83, 255}; // Dark gray
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game Over", textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect;

            textRect.x = windowSize_x/2 - textSurface->w/2;
            textRect.y = windowSize_y / 2 - 50;
            textRect.w = textSurface->w;
            textRect.h = textSurface->h;
            
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
            TTF_CloseFont(font);
        }
        
        // Render restart button
        SDL_Rect restartRect = {static_cast<int>(windowSize_x) / 2 - 36, static_cast<int>(windowSize_y) / 2, 72, 64};
        SDL_Texture* restartTexture = IMG_LoadTexture(renderer, "assets/Images/RestartButton.png");
        if (restartTexture) {
            SDL_RenderCopy(renderer, restartTexture, nullptr, &restartRect);
            SDL_DestroyTexture(restartTexture);
        }
    }
    
    // update screen
    SDL_RenderPresent(renderer);
}

void cleanup(){
    delete dino;
    delete ground;
    delete obstacles;
    delete scores;
    delete soundManager;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    // initialize SDL
    if (!init()) {
         return -1;
    }
    
    // load game assets
    loadGame();
    
    // game loop var
    bool quit = false;
    SDL_Event e;
    int mouseX = 0, mouseY = 0;
    bool mousePressed = false;
    Uint32 lastFrameTime = SDL_GetTicks();
    
    // game loop
    while (!quit) {
        // events
        while (SDL_PollEvent(&e) != 0) {
            handleEvents(e, quit, mouseX, mouseY, mousePressed);
        }
        // current time
        Uint32 currentFrameTime = SDL_GetTicks();
        // update game
        updateGame(currentFrameTime, mouseX, mouseY, mousePressed);
        // render
        render();
        // rate frame to 60FPS
        if (currentFrameTime - lastFrameTime < 16) {
            SDL_Delay(16 - (currentFrameTime - lastFrameTime));
        }
        lastFrameTime = currentFrameTime;
    }
    cleanup();
    
    return 0;
}

