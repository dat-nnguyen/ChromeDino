//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef CLOUDS_H
#define CLOUDS_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Clouds {
public:
    Clouds();
    void updateClouds(sf::Time& deltaTime);
    void drawClouds(sf::RenderWindow& window);
private:
    std::vector<sf::Sprite> clouds;
    sf::Time currentTime;
    sf::Texture cloudTexture;
    std::random_device random;
    std::mt19937 randomGenerator;
};



#endif //CLOUDS_H
