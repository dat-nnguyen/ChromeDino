#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <map>

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const std::string& fileName, SDL_Renderer* renderer);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer, 
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
};