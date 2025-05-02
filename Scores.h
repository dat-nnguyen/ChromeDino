#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "SoundManager.h"

class Scores {
public:
    Scores(SDL_Renderer* renderer, Sound* soundManager);
    ~Scores();

    void update(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void reset(SDL_Renderer* renderer);

private:
    TTF_Font* font;
    
    // Textures for displaying scores
    SDL_Texture* scoreTexture;      // Current score
    SDL_Texture* prevScoreTexture;  // High score
    SDL_Texture* hiTextTexture;     // "HI" label
    
    // Rectangle positions for text rendering
    SDL_Rect scoreRect;
    SDL_Rect prevScoreRect;
    SDL_Rect hiTextRect;

    Sound* sound;
    int scores;            // Current score
    int previousScore;     // High score
    int scoresIndex;       // Animation counter
    int scoresDiff;        // Score since last speedup
    int scoresInital;      // Base score for difficulty scaling
};