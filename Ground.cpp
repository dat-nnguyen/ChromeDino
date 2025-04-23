#include "Ground.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <array>
Ground::Ground() : groundTexture() {
    if (groundTexture.loadFromFile("assets/Images/GroundImage.png")) {
        groundSprite.setTexture(groundTexture);
        groundSprite.setPosition(
            sf::Vector2f(0.f, windowSize_y - groundTexture.getSize().y - 50));
    }
}

void Ground::updateGround() {
    if (!playerDead) {
        if (offset > groundTexture.getSize().x - windowSize_x) {
            offset = 0;
        }

        offset += gameSpeed;
        groundSprite.setTextureRect(
            sf::IntRect<int>(offset, 0, windowSize_x, windowSize_y));
    } else {
        groundSprite.setTextureRect(
            sf::IntRect<int>(offset, 0, windowSize_x, windowSize_y));
    }
}

void Ground::reset() {
    offset = 0;
    groundSprite.setTextureRect(
        sf::IntRect<int>(offset, 0, windowSize_x, windowSize_y));
}
