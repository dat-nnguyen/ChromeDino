#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"  // assuming this has windowSize_x, windowSize_y, gameSpeed, playerDead

class Ground {
public:
    sf::Sprite groundSprite{};
    sf::Texture groundTexture;
    int offset{0};

    Ground();
    void updateGround();
    void reset();
};
