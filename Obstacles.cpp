#include "Obstacles.h"

Obstacle::Obstacle(SDL_Texture* tex, SDL_Renderer* renderer) : texture(tex) {
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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    obstacleTexture_1 = TextureManager::LoadTexture("assets/Images/Cactus1.png", renderer);
    if (obstacleTexture_1) {
        std::cout << "Loaded cactus Image 1" << std::endl;
    }
    
    obstacleTexture_2 = TextureManager::LoadTexture("assets/Images/Cactus2.png", renderer);
    if (obstacleTexture_2) {
        std::cout << "Loaded cactus Image 2" << std::endl;
    }
    
    obstacleTexture_3 = TextureManager::LoadTexture("assets/Images/Cactus3.png", renderer);
    if (obstacleTexture_3) {
        std::cout << "Loaded cactus Image 3" << std::endl;
    }
}

Obstacles::~Obstacles() {
    SDL_DestroyTexture(obstacleTexture_1);
    SDL_DestroyTexture(obstacleTexture_2);
    SDL_DestroyTexture(obstacleTexture_3);
}

void Obstacles::update(Uint32 currentTime) {
    // Spawn new obstacles periodically, with better spacing
    Uint32 elapsedTime = currentTime - lastSpawnTime;
    
    // Increased minimum time between obstacles to make the game more fair
    // Also scales with game speed to maintain challenge balance
    if (elapsedTime > (1000 + gameSpeed * 150)) {  // Increased from 500 + gameSpeed * 125
        randomNumber = (std::rand() % 100);
        
        if (randomNumber < 40) {  // 40% chance for small cactus
            obstacles.emplace_back(obstacleTexture_1, nullptr);
        } else if (randomNumber < 70) {  // 30% chance for medium cactus
            obstacles.emplace_back(obstacleTexture_2, nullptr);
        } else {  // 30% chance for triple cactus
            obstacles.emplace_back(obstacleTexture_3, nullptr);
        }
        
        lastSpawnTime = currentTime;
    }
    
    if (!playerDead) {
        for (int i = 0; i < obstacles.size(); i++) {
            // Update collision rect position
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
        TextureManager::Draw(obstacle.texture, obstacle.srcRect, obstacle.destRect, renderer);
    }
}

void Obstacles::reset() {
    obstacles.clear();
}