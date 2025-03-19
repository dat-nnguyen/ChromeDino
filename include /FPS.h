//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef FPS_H
#define FPS_H

#include <SFML/Graphics.hpp>

class FPS {
public:
    FPS();
    void update();
    void drawTo(sf::RenderWindow& window);
private:
    sf::Clock clock;
    sf::Text text;
    sf::Font font;
    int frameCount;
    int fps;
};

#endif //FPS_H
