//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "Clouds.h"
#include "Dino.h"
#include "Ground.h"
#include "Obstacles.h"
#include "RestartButton.h"
#include "Scores.h"
#include "FPS.h"
#include "SoundManager.h"

class GameState {
public:
    GameState();
    void setMousePosition(sf::Vector2i p_mousePos);
    void update(sf::Time deltaTime);
    void drawWindow(sf::RenderWindow& window);
private:
    FPS m_fps;
    Dino m_dino;
    Ground m_ground;
    Obstacles m_obstacles;
    RestartButton m_restartButton;
    SoundManager m_soundManager;
    Clouds m_clouds;
    Scores m_scores;
    sf::Font GameOverFont;
    sf::Text GameOverText;
    sf::Vector2f m_mousePos{0.f, 0.f};
};



#endif //GAMESTATE_H
