#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Dino.h"
#include "Ground.h"
#include "Obstacles.h"
#include "Scores.h"
#include "Clouds.h"
#include "RestartButton.h"
#include "SoundManager.h"
#include "Constants.h"

class GameState {
public:
    Dino* dino;
    Ground* ground;
    Obstacles* obstacles;
    Scores* scores;
    Clouds* clouds;
    RestartButton* restartButton;
    
    TTF_Font* gameOverFont;
    SDL_Texture* gameOverTexture;
    SDL_Rect gameOverRect;
    
    int mouseX, mouseY;
    bool mousePressed;
    
    GameState(SDL_Renderer* renderer);
    ~GameState();
    
    void handleEvents(SDL_Event& event);
    void update(Uint32 currentTime);
    void render(SDL_Renderer* renderer);
};