#include "Dino.h"

Dino::Dino(SDL_Renderer* renderer, Sound* soundManager) 
    : animationCounter(0), posY(windowSize_y - 150.0f), velocityY(0), sound(soundManager), deathTime(0) {
    
    dinoTexture = TextureManager::LoadTexture("assets/Images/PlayerSpriteSheet.png", renderer);
    
    if (dinoTexture) {
        // Set up animation frames from sprite sheet
        for (size_t i = 0; i < frames.size(); i++) {
            frames[i].x = i * FRAME_WIDTH;
            frames[i].y = 0;
            frames[i].w = FRAME_WIDTH;
            frames[i].h = FRAME_HEIGHT;
        }
        
        // Initialize source rect to first frame
        srcRect = frames[0];
        
        // Set up destination rectangle
        destRect.x = windowSize_x / 2 - windowSize_x / 4;
        destRect.y = posY;
        destRect.w = FRAME_WIDTH;
        destRect.h = FRAME_HEIGHT;
        
        // Set up collision rectangle (slightly smaller than visual)
        collisionRect = destRect;
        collisionRect.h -= 15;
        collisionRect.w -= 10;
    } else {
        std::cout << "Error loading the PlayerSprite texture" << std::endl;
    }
}

Dino::~Dino() {
    SDL_DestroyTexture(dinoTexture);
}

void Dino::update(Uint32 currentTime, std::vector<Obstacle>& obstacles) {
    // Update position
    destRect.y = posY;
    
    // Update collision rectangle
    collisionRect.x = destRect.x;
    collisionRect.y = destRect.y;
    
    // Check for collisions
    for (auto& obs : obstacles) {
        SDL_Rect result;
        if (SDL_IntersectRect(&collisionRect, &obs.collisionRect, &result)) {
            playerDead = true;
            deathTime = currentTime;
        }
    }
    
    if (!playerDead) {
        walk();
        
        // Check for jump input
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_SPACE] && posY >= windowSize_y - 150.0f) {
            animationCounter = 0;
            velocityY = -20.0f;
            srcRect = frames[1];
            sound->playJumpSound();
        }
        
        // Apply gravity if in air
        if (posY < windowSize_y - 150.0f) {
            velocityY += 1.0f;
            srcRect = frames[1];
        }
        
        // Apply velocity
        posY += velocityY;
        
        // Check for ground collision
        if (posY > windowSize_y - 150.0f) {
            posY = windowSize_y - 150.0f;
            velocityY = 0.0f;
        }
    } else {
        // Character is dead
        velocityY = 0.0f;
        srcRect = frames[3];
        
        // Play death sound once
        if (currentTime - deathTime < 170) {
            sound->playDieSound();
        }
    }
}

void Dino::walk() {
    for (int i = 0; i < frames.size() - 3; i++) {
        if (animationCounter == (i + 1) * 3) {
            srcRect = frames[i];
        }
    }
    
    if (animationCounter >= (frames.size() - 2) * 3) {
        animationCounter = 0;
    }
    
    animationCounter++;
}

void Dino::render(SDL_Renderer* renderer) {
    TextureManager::Draw(dinoTexture, srcRect, destRect, renderer);
}

void Dino::reset() {
    velocityY = 0;
    posY = windowSize_y - 150.0f;
    srcRect = frames[0];
}