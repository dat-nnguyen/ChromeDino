#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "SoundManager.h"
#include "Constants.h"

class Scores {
public:
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    SDL_Texture* prevScoreTexture;
    SDL_Texture* hiTextTexture;
    
    SDL_Rect scoreRect;
    SDL_Rect prevScoreRect;
    SDL_Rect hiTextRect;
    
    Sound* sound;
    short scores;
    short previousScore;
    short scoresIndex;
    short scoresDiff;
    short scoresInital;
    
    Scores(SDL_Renderer* renderer, Sound* soundManager);
    ~Scores();
    void update(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void reset(SDL_Renderer* renderer);
};