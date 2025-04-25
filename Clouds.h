#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <random>
#include "TextureManager.h"
#include "Constants.h"

class Clouds {
public:
    std::vector<SDL_Rect> cloudPositions;
    SDL_Texture* cloudTexture;
    Uint32 lastCloudTime;
    std::mt19937 rng;
    
    Clouds(SDL_Renderer* renderer);
    ~Clouds();
    void updateClouds(Uint32 currentTime);
    void render(SDL_Renderer* renderer);
};