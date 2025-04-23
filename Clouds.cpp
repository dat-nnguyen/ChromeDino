#include "Clouds.h"
#include "Constants.h"
#include <array>

Clouds::Clouds() : cloudTexture(), clouds(), currTime(), dev() {
    if (cloudTexture.loadFromFile("assets/Images/Clouds.png")) {
        std::cout << "Loaded CloudTexture" << std::endl;
    }

    clouds.reserve(4);
    clouds.emplace_back(sf::Sprite(cloudTexture));
    clouds.back().setPosition(sf::Vector2f(windowSize_x, windowSize_y / 2 - 40.f));
}

void Clouds::updateClouds(sf::Time& deltaTime) {
    currTime += deltaTime;

    if (currTime.asSeconds() > 8.f) {
        clouds.emplace_back(sf::Sprite(cloudTexture));
        std::uniform_int_distribution<std::mt19937::result_type> dist6(
            windowSize_y / 2 - 200, windowSize_y / 2 - 50);
        clouds.back().setPosition(sf::Vector2f(windowSize_x, dist6(rng)));

        currTime = sf::Time::Zero;
    }

    for (int i = 0; i < clouds.size(); i++) {
        if (!playerDead)
            clouds[i].move(sf::Vector2f(-1.f, 0.f));
        else
            clouds[i].move(sf::Vector2f(-0.5f, 0.f));

        if (clouds[i].getPosition().x < 0.f - cloudTexture.getSize().x) {
            clouds.erase(clouds.begin() + i);
            i--;  // adjust index after erasing
        }
    }
}

void Clouds::drawTo(sf::RenderWindow& window) {
    for (auto& cloud : clouds) {
        window.draw(cloud);
    }
}
