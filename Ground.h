#pragma once
#include <SDL2/SDL.h>
#include "Constants.h"

class Ground {
public:
    SDL_Texture* groundTexture;
    SDL_Rect srcRect;  // Source rectangle for ground texture
    SDL_Rect destRect; // Destination rectangle for rendering
    int textureWidth;  // Total width of ground texture
    int offset;        // Current offset for scrolling

    Ground(SDL_Renderer* renderer);
    ~Ground();
    void updateGround();
    void render(SDL_Renderer* renderer);
    void reset();
};