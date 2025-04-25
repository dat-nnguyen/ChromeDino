#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "Constants.h"

class Ground {
public:
    SDL_Texture* groundTexture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    int textureWidth;
    int offset;

    Ground(SDL_Renderer* renderer);
    ~Ground();
    void updateGround();
    void render(SDL_Renderer* renderer);
    void reset();
};