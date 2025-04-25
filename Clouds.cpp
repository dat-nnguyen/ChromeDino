#include "Clouds.h"
#include <iostream>
#include <random>
#include "TextureManager.h"
#include "Constants.h"
Clouds::Clouds(SDL_Renderer* renderer) : lastCloudTime(0) {
    // Initialize random generator
    std::random_device dev;
    rng = std::mt19937(dev());
    
    // Load cloud texture
    cloudTexture = TextureManager::LoadTexture("assets/Images/Clouds.png", renderer);
    
    if (cloudTexture) {
        std::cout << "Loaded CloudTexture" << std::endl;
        
        // Create initial cloud
        int texW, texH;
        SDL_QueryTexture(cloudTexture, NULL, NULL, &texW, &texH);
        
        SDL_Rect cloudRect;
        cloudRect.x = windowSize_x;
        cloudRect.y = windowSize_y / 2 - 40;
        cloudRect.w = texW;
        cloudRect.h = texH;
        
        cloudPositions.push_back(cloudRect);
    }
}

Clouds::~Clouds() {
    SDL_DestroyTexture(cloudTexture);
}

void Clouds::updateClouds(Uint32 currentTime) {
    // Spawn new clouds every 8 seconds
    if (currentTime - lastCloudTime > 8000) {
        int texW, texH;
        SDL_QueryTexture(cloudTexture, NULL, NULL, &texW, &texH);
        
        SDL_Rect cloudRect;
        cloudRect.x = windowSize_x;
        
        // Random Y position for cloud
        std::uniform_int_distribution<std::mt19937::result_type> dist(
            windowSize_y / 2 - 200, windowSize_y / 2 - 50);
        cloudRect.y = dist(rng);
        
        cloudRect.w = texW;
        cloudRect.h = texH;
        
        cloudPositions.push_back(cloudRect);
        lastCloudTime = currentTime;
    }
    
    // Move clouds and remove when off screen
    for (int i = 0; i < cloudPositions.size(); i++) {
        if (!playerDead) {
            cloudPositions[i].x -= 1;
        } else {
            cloudPositions[i].x -= 0.5;
        }
        
        if (cloudPositions[i].x < -cloudPositions[i].w) {
            cloudPositions.erase(cloudPositions.begin() + i);
            i--; // adjust index after erasing
        }
    }
}

void Clouds::render(SDL_Renderer* renderer) {
    for (auto& cloudPos : cloudPositions) {
        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = cloudPos.w;
        srcRect.h = cloudPos.h;
        
        TextureManager::Draw(cloudTexture, srcRect, cloudPos, renderer);
    }
}