//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef RESTARTBUTTON_H
#define RESTARTBUTTON_H

#include <SFML/Graphics.hpp>

class RestartButton {
public:
    RestartButton();
    sf::Sprite RestartButtonSprite;
    sf::FloatRect RestartButtonBounds;
    sf::Vector2f MousePosition;
    bool checkClick{false};
private:
    sf::Texture RestartButtonTexture;
};




#endif //RESTARTBUTTON_H
