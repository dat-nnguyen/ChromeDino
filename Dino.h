#pragma once
#include <SDL2/SDL.h>
#include <array>
#include <iostream>
#include "TextureManager.h"
#include "SoundManager.h"
#include "Obstacles.h"
#include "Constants.h"

constexpr int FRAME_WIDTH = 90;
constexpr int FRAME_HEIGHT = 95;

class Dino {
public:
    SDL_Texture* dinoTexture;
    SDL_Rect srcRect;  // Source rectangle for sprite sheet
    SDL_Rect destRect; // Destination rectangle for rendering
    SDL_Rect collisionRect; // Collision box
    
    std::array<SDL_Rect, 6> frames;  // Animation frames
    int animationCounter;
    
    float posY;        // Y position
    float velocityY;   // Vertical velocity for jump physics
    
    Sound* sound;      // Sound manager
    Uint32 deathTime;  // Time when player died
    
    Dino(SDL_Renderer* renderer, Sound* soundManager);
    ~Dino();
    
    void update(Uint32 currentTime, std::vector<Obstacle>& obstacles);
    void render(SDL_Renderer* renderer);
    void walk();
    void reset();
};