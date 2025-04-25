#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const std::string& fileName, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (!surface) {
        std::cout << "Failed to load texture: " << fileName << " - " << IMG_GetError() << std::endl;
        return nullptr;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }
    
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, 
                         SDL_Renderer* renderer, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(renderer, tex, &src, &dest, 0, nullptr, flip);
}