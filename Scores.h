#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "SoundManager.h"

class Scores{
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
    SDL_Texture* scoreTextTexture;     // "Score" label
    
    // Rectangle positions for text rendering
    SDL_Rect scoreRect;
    SDL_Rect scoreTextRect;

    Sound* sound;
    int scores;            // Current score
    int scoresIndex;       // Animation counter
    int scoresDiff;        // Score since last speedup
    int scoresInital;      // Base score for difficulty scaling
};