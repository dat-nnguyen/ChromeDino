//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef GROUND_H
#define GROUND_H


#include <SFML/Graphics.hpp>
class Ground {
public:
    Ground();
    void updateGround();
    void resetGround();
    sf::Sprite groundSprite;
private:
    sf::Texture groundTexture;
    int offset{0};
};



#endif //GROUND_H
