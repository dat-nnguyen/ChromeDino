#include "Dino.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <array>
constexpr int FRAME_WIDTH = 90;
constexpr int FRAME_HEIGHT = 95;
Dino::Dino() : dinoBounds() {
  if (dinoTex.loadFromFile("assets/Images/PlayerSpriteSheet.png")) {
    dino.setTexture(dinoTex);
    for (size_t i = 0; i < frames.size(); i++) {
      frames[i] = sf::IntRect(i * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT);
    }
    dino.setTextureRect(frames[0]);
    dinoPos = dino.getPosition();
  } else {
    std::cout << "Error loading the PlayerSprite texture" << std::endl;
  }
}

void Dino::update(sf::Time& deltaTime, std::vector<Obstacle>& obstacles) {
  dinoPos = dino.getPosition();
  dinoBounds = dino.getGlobalBounds();
  dinoBounds.height -= 15.f;
  dinoBounds.width -= 10.f;
  timeTracker += deltaTime;

  // if dino is collide with obstactcle, player is dead
  for (auto& obs : obstacles) {
    if (dinoBounds.findIntersection(obs.obstacleBounds)) {
      playerDead = true;
    }
  }

  if (!playerDead) {
    walk();

    // jump logic, hopefully the jump animation is good
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) &&
        dinoPos.y >= windowSize_y - 150.f) {
      animationCounter = 0;
      dinoMotion.y = -20.f;
      dino.setTextureRect(frames[1]);
      sound.jumpSound.play();
    }

    if (dinoPos.y < windowSize_y - 150.f) {
      dinoMotion.y += 1.f;
      dino.setTextureRect(frames[1]);
    }

    if (dinoPos.y > windowSize_y - 150.f) {
      dino.setPosition(sf::Vector2f(dino.getPosition().x, windowSize_y - 150.f));
      dinoMotion.y = 0.f;
    }

    dino.move(dinoMotion);
  } else {
    dinoMotion.y = 0.f;
    dino.setTextureRect(frames[3]);

    if (timeTracker.asMilliseconds() > 170.f) {
      sound.dieSound.stop();
      sound.dieSound.setLooping(false);
      timeTracker = sf::Time::Zero;
    } else {
      sound.dieSound.play();
    }
  }
}

void Dino::walk() {
  for (int i = 0; i < frames.size() - 3; i++) {
    if (animationCounter == (i + 1) * 3) {
      dino.setTextureRect(frames[i]);
    }
  }

  if (animationCounter >= (frames.size() - 2) * 3) {
    animationCounter = 0;
  }

  animationCounter++;
}

void Dino::reset() {
  dinoMotion.y = 0;
  dino.setPosition(sf::Vector2f(dino.getPosition().x, windowSize_y - 150.f));
  dino.setTextureRect(frames[0]);
}

