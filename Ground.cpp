#include "Ground.h"

Ground::Ground(SDL_Renderer* renderer) : offset(0) {
    groundTexture = TextureManager::LoadTexture("assets/Images/GroundImage.png", renderer);
    
    if (groundTexture) {
        SDL_QueryTexture(groundTexture, NULL, NULL, &textureWidth, &srcRect.h);
        
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = windowSize_x;
        
        destRect.x = 0;
        destRect.y = windowSize_y - srcRect.h - 50;
        destRect.w = windowSize_x;
        destRect.h = srcRect.h;
    }
}

Ground::~Ground() {
    SDL_DestroyTexture(groundTexture);
}

void Ground::updateGround() {
    if (!playerDead) {
        if (offset > textureWidth - windowSize_x) {
            offset = 0;
        }
        
        offset += gameSpeed;
        srcRect.x = offset;
    }
}

void Ground::render(SDL_Renderer* renderer) {
    TextureManager::Draw(groundTexture, srcRect, destRect, renderer);
}

void Ground::reset() {
    offset = 0;
    srcRect.x = offset;
}