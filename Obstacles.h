#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Constants.h"
using namespace std;
class Obstacle{
public:
    SDL_Texture* texture;
    SDL_Rect srcRect;      // Source rectangle
    SDL_Rect destRect;     // Destination rectangle
    SDL_Rect collisionRect; // Collision box

    Obstacle(SDL_Texture* tex, SDL_Renderer* renderer);
};

class Obstacles{
public:
    vector<Obstacle> obstacles;
    Uint32 lastSpawnTime;
    SDL_Texture* obstacleTexture_1; // Small cactus
    SDL_Texture* obstacleTexture_2; // Medium cactus
    SDL_Texture* obstacleTexture_3; // Large cactus
    int randomNumber;

    Obstacles(SDL_Renderer* renderer);
    ~Obstacles();
    void update(Uint32 currentTime);
    void render(SDL_Renderer* renderer);
    void reset();
};