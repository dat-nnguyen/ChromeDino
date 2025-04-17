#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "SoundManager.h"
#include "Constants.h"  // for windowSize_x, gameSpeed, playerDead

class Scores {
public:
    sf::Text previousScoreText;
    sf::Text HIText;
    sf::Text scoresText;
    sf::Font scoresFont;
    Sound sound;
    short scores{0};
    short previousScore{0};
    short scoresIndex{0};
    short scoresDiff{0};
    short scoresInital{0};

    Scores();
    void update();
    void reset();
};
