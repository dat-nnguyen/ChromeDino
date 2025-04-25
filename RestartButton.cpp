#include "RestartButton.h"

RestartButton::RestartButton(SDL_Renderer* renderer) {
    buttonTexture = TextureManager::LoadTexture("assets/Images/RestartButton.png", renderer);
    
    if (buttonTexture) {
        // Get texture dimensions
        SDL_QueryTexture(buttonTexture, NULL, NULL, &srcRect.w, &srcRect.h);
        
        srcRect.x = 0;
        srcRect.y = 0;
        
        // Position button in the middle of the screen
        destRect.x = windowSize_x / 2 - srcRect.w / 2;
        destRect.y = windowSize_y / 2;
        destRect.w = srcRect.w;
        destRect.h = srcRect.h;
    }
}

RestartButton::~RestartButton() {
    SDL_DestroyTexture(buttonTexture);
}

bool RestartButton::isClicked(int mouseX, int mouseY) {
    // Check if mouse position is within button boundaries
    return (mouseX >= destRect.x && mouseX <= destRect.x + destRect.w &&
            mouseY >= destRect.y && mouseY <= destRect.y + destRect.h);
}