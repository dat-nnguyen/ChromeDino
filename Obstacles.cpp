#include "Obstacles.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
using namespace std;
Obstacle::Obstacle(SDL_Texture* tex, SDL_Renderer* renderer):texture(tex) {
    // Configure the obstacle's source rectangle (entire texture)
    srcRect.x = 0;
    srcRect.y = 0;
    SDL_QueryTexture(tex, NULL, NULL, &srcRect.w, &srcRect.h);
    
    // Position the obstacle at the right side of the screen
    destRect.x = windowSize_x;
    destRect.y = groundOffset;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    
    // Set up collision rectangle (slightly smaller than visual)
    collisionRect = destRect;
    collisionRect.w -= 10;
}

Obstacles::Obstacles(SDL_Renderer* renderer) : lastSpawnTime(0) {
    obstacles.reserve(5);
    
    // Initialize random seed
    srand(static_cast<unsigned int>(time(NULL)));
    
    obstacleTexture_1 = IMG_LoadTexture(renderer, "assets/Images/Cactus1.png");
    obstacleTexture_2 = IMG_LoadTexture(renderer, "assets/Images/Cactus2.png");
    obstacleTexture_3 = IMG_LoadTexture(renderer, "assets/Images/Cactus3.png");
}

Obstacles::~Obstacles() {
    SDL_DestroyTexture(obstacleTexture_1);
    SDL_DestroyTexture(obstacleTexture_2);
    SDL_DestroyTexture(obstacleTexture_3);
}

void Obstacles::update(Uint32 currentTime){
    Uint32 elapsedTime = currentTime - lastSpawnTime;

    // Also scales with game speed to maintain challenge balance
    if (elapsedTime > (1000 + gameSpeed * 150)) {  
        randomNumber = (std::rand() % 100);
        
        if (randomNumber < 40) {  // 40% chance for small cactus
            obstacles.emplace_back(obstacleTexture_1, nullptr);
        } else if (randomNumber < 70) {  // 30% chance for medium cactus
            obstacles.emplace_back(obstacleTexture_2, nullptr);
        } else {  // 30% chance for large cactus
            obstacles.emplace_back(obstacleTexture_3, nullptr);
        }
        
        lastSpawnTime = currentTime;
    }
    
    if (!playerDead) {
        for (int i = 0; i < obstacles.size(); i++) {
            // Update obstacle position and collision box
            obstacles[i].destRect.x -= gameSpeed;
            obstacles[i].collisionRect = obstacles[i].destRect;
            obstacles[i].collisionRect.w -= 10;
            
            // Remove obstacles that have moved off screen
            if (obstacles[i].destRect.x < -150) {
                obstacles.erase(obstacles.begin() + i);
                i--; // adjust index after erasing
            }
        }
    }
}

void Obstacles::render(SDL_Renderer* renderer) {
    for (auto& obstacle : obstacles) {
        SDL_RenderCopy(renderer, obstacle.texture, &obstacle.srcRect, &obstacle.destRect);
    }
}

void Obstacles::reset() {
    obstacles.clear();
}