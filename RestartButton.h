#pragma once
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "Constants.h"

class RestartButton {
public:
    SDL_Texture* buttonTexture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    RestartButton(SDL_Renderer* renderer);
    ~RestartButton();
    bool isClicked(int mouseX, int mouseY);
};