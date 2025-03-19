//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef OBSTACLES_H
#define OBSTACLES_H


#include <SFML/Graphics.hpp>
#include <vector>
class Obstacles {
    Obstacles(sf::Texture& texture);
    sf::Sprite obstacleSprite;
    sf::FloatRect obstacleBound;
};
class Obstacle {
public:
    Obstacle();
    void update(sf::Time& deltaTime);
    void drawTo(sf::RenderWindow& window);
    void reset();
    std::vector<Obstacle> obstacles;
private:
    sf::Time spawnTimer;
    sf::Texture obstacleTexture_1;
    sf::Texture obstacleTexture_2;
    sf::Texture obstacleTexture_3;
    int randomNumber{0};
};



#endif //OBSTACLES_H
