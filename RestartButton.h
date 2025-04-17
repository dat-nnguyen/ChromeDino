#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"  // for windowSize_x, windowSize_y

class RestartButton {
public:
    sf::Sprite restartButtonSprite;
    sf::FloatRect restartButtonSpriteBounds;
    sf::Texture restartButtonTexture;
    sf::Vector2f mousePos;
    bool checkPressed{false};

    RestartButton();
};
