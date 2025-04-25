#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TextureManager.h"
#include "Constants.h"

class Obstacle {
public:
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    SDL_Rect collisionRect;

    Obstacle(SDL_Texture* tex, SDL_Renderer* renderer);
};

class Obstacles {
public:
    std::vector<Obstacle> obstacles;
    Uint32 lastSpawnTime;
    SDL_Texture* obstacleTexture_1;
    SDL_Texture* obstacleTexture_2;
    SDL_Texture* obstacleTexture_3;
    int randomNumber;

    Obstacles(SDL_Renderer* renderer);
    ~Obstacles();
    void update(Uint32 currentTime);
    void render(SDL_Renderer* renderer);
    void reset();
};