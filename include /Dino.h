//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef DINO_H
#define DINO_H

#include <SFML/Graphics.hpp>
#include <array>

#include "Obstacles.h"
#include "SoundManager.h"

class Dino {
public:
     Dino();
     void update(sf::Time& deltaTime, std::vector<Obstacle>& obstacles);
     void walk();
     void reset();
     sf::Sprite dino;
     sf::FloatRect dinoBounds;
private:
     sf::Vector2f dinoPos{0.f, 0.f};
     sf::Vector2f dinoMotion{0.f, 0.f};
     sf::Texture dinoTex;
     SoundManager soundManager;
     std::array<sf::IntRect, 6> frames;
     sf::Time timeTracker;
     int animationCounter{0};
};




#endif //DINO_H
