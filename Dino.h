#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "SoundManager.h"
#include "Obstacles.h"

extern bool playerDead;
extern float windowSize_y;

// detect collision with cactus (obstcle)
class Dino {
public:
     sf::Sprite dino{};
     sf::Vector2f dinoPos{0.f, 0.f};
     sf::Vector2f dinoMotion{0.f, 0.f};
     sf::Texture dinoTex;
     sf::FloatRect dinoBounds;
     Sound sound;
     std::array<sf::IntRect, 6> frames;
     sf::Time timeTracker;
     int animationCounter{0};

     Dino();
     void update(sf::Time& deltaTime, std::vector<Obstacle>& obstacles);
     void walk();
     void reset();
};
