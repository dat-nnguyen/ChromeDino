//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef SCORES_H
#define SCORES_H
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

class Scores {
public:
    Scores();
    void update();
    void reset();
    sf::Text scoreText;
    sf::Text HIscoreText;
private:
    sf::Font scoresFont;
    SoundManager soundManager;
    short scores{0};
    short scoresIndex{0};
    short previousScore{0};
    short scoreDifficulty{0};
    short scoreInitial{0};
};



#endif //SCORES_H
