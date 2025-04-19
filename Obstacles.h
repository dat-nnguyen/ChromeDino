#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Obstacle { // cactus
public:
    Obstacle(sf::Texture& texture); // hold the image

    sf::Sprite obstacleSprite{}; // the frame of the image (texture)

    sf::FloatRect obstacleBounds{0.f, 0.f, 0.f, 0.f}; // space that the object ocuipie on the screen
    // for collision detecting
};

class Obstacles {
public:
    std::vector<Obstacle> obstacles;
    sf::Time spawnTimer;
    sf::Texture obstacleTexture_1;
    sf::Texture obstacleTexture_2;
    sf::Texture obstacleTexture_3;
    int randomNumber{0};

    Obstacles();

    void update(sf::Time& deltaTime);
    void drawTo(sf::RenderWindow& window);
    void reset();
};
