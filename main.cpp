#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <iostream>
#include <random>
#include <vector>

#include "Constants.h"
#include "Dino.h"
#include "Obstacles.h"
#include "SoundManager.h"
#include "Ground.h"
#include "Scores.h"
#include "Clouds.h"
#include "RestartButton.h"


class GameState {
 public:
  Dino dino;
  Ground ground;
  Obstacles obstacles;
  Scores scores;
  Clouds clouds;
  RestartButton restartButton;
  sf::Font gameOverFont;
  sf::Text gameOverText;
  sf::Vector2f mousePos{0.f, 0.f};

  GameState()
      : dino(),
        ground(),
        obstacles(),
        scores(),
        clouds(),
        gameOverFont(),
        gameOverText(),{
    gameOverFont.loadFromFile("assets/Fonts/Font.ttf");
    gameOverText.setFont(gameOverFont);
    dino.dino.setPosition(sf::Vector2f(windowSize_x / 2 - windowSize_x / 4,
                                       windowSize_y - 150.f));
    gameOverText.setString("Game Over");
    gameOverText.setPosition(
        sf::Vector2f(restartButton.restartButtonSprite.getPosition().x -
                         gameOverText.getCharacterSize(),
                     restartButton.restartButtonSprite.getPosition().y - 50));
    gameOverText.setFillColor(sf::Color(83, 83, 83));
  }
  void setMousePos(sf::Vector2i p_mousePos) {
    mousePos.x = p_mousePos.x;
    mousePos.y = p_mousePos.y;
  }

  void update(sf::Time deltaTime) {
    restartButton.checkPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    if (playerDead == true &&
        restartButton.restartButtonSpriteBounds.contains(mousePos) &&
        restartButton.checkPressed == true) {
      ground.reset();
      obstacles.reset();
      dino.reset();
      scores.reset();

      playerDead = false;
    } else {
      ground.updateGround();
      obstacles.update(deltaTime);
      dino.update(deltaTime, obstacles.obstacles);
      clouds.updateClouds(deltaTime);
      scores.update();
    }
  }

  void drawTo(sf::RenderWindow& window) {
    if (playerDead == true) {
      clouds.drawTo(window);
      window.draw(ground.groundSprite);
      obstacles.drawTo(window);
      window.draw(scores.scoresText);
      window.draw(scores.previousScoreText);
      window.draw(scores.HIText);
      window.draw(dino.dino);
      window.draw(gameOverText);
      window.draw(restartButton.restartButtonSprite);
    } else {
      clouds.drawTo(window);
      window.draw(ground.groundSprite);
      obstacles.drawTo(window);
      window.draw(scores.scoresText);
      window.draw(scores.previousScoreText);
      window.draw(scores.HIText);
      window.draw(dino.dino);
    }
  }
};

int main() {
  sf::RenderWindow window(sf::VideoMode(windowSize_x, windowSize_y), "Dino");

  GameState gameState;

  sf::Event event;
  sf::Time deltaTime;
  sf::Clock deltaTimeClock;

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      gameState.setMousePos(sf::Mouse::getPosition(window));
    }
    deltaTime = deltaTimeClock.restart();

    gameState.update(deltaTime);

    window.clear(sf::Color::White);
    gameState.drawTo(window);
    window.display();
  }
}
