#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include "Constants.h"  // for windowSize_x, windowSize_y, playerDead

class Clouds {
public:
    std::vector<sf::Sprite> clouds;
    sf::Time currTime;
    sf::Texture cloudTexture;
    std::random_device dev;
    std::mt19937 rng{dev()};

    Clouds();
    void updateClouds(sf::Time& deltaTime);
    void drawTo(sf::RenderWindow& window);
};
