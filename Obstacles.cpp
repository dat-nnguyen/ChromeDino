#include "Obstacles.h"
#include "Constants.h"

Obstacle::Obstacle(sf::Texture& texture) : obstacleSprite(), obstacleBounds() {
  obstacleSprite.setTexture(texture);
  obstacleSprite.setPosition(sf::Vector2f(windowSize_x, groundOffset));
}

Obstacles::Obstacles() : spawnTimer(sf::Time::Zero) {
  obstacles.reserve(5);

  if (obstacleTexture_1.loadFromFile("assets/Images/Cactus1.png")) {
    std::cout << "loaded cactus Image 1 " << std::endl;
  }

  if (obstacleTexture_2.loadFromFile("assets/Images/Cactus2.png")) {
    std::cout << "Loaded cactus Image 2" << std::endl;
  }

  if (obstacleTexture_3.loadFromFile("assets/Images/Cactus3.png")) {
    std::cout << "Loaded cactus Image 3" << std::endl;
  }
}

// When enough time passes, randomly spawns a new cactus (choosing one of 3 textures)
// If the player is alive, every obstacle moves left, and eventually off the screen
void Obstacles::update(sf::Time& deltaTime) {
  spawnTimer += deltaTime;
  if (spawnTimer.asSeconds() > 0.5f + gameSpeed / 8) {
    randomNumber = (rand() % 3) + 1;
    if (randomNumber == 1) {
      obstacles.emplace_back(Obstacle(obstacleTexture_1));
    } else if (randomNumber == 2 || randomNumber == 3) {
      obstacles.emplace_back(Obstacle(obstacleTexture_2));
    }
    spawnTimer = sf::Time::Zero;
  }

  if (!playerDead) {
    for (int i = 0; i < obstacles.size(); i++) {
      obstacles[i].obstacleBounds = obstacles[i].obstacleSprite.getGlobalBounds();
      obstacles[i].obstacleBounds.width -= 10.f;
      obstacles[i].obstacleSprite.move(-1 * gameSpeed, 0.f);
      if (obstacles[i].obstacleSprite.getPosition().x < -150.f) {
        obstacles.erase(obstacles.begin() + i);
        i--;  // prevent skipping the next one after erase
      }
    }
  } else { // player is dead, everything stop moving
    for (auto& obstacle : obstacles) {
      obstacle.obstacleSprite.move(0.f, 0.f);
    }
  }
}

void Obstacles::drawTo(sf::RenderWindow& window) {
  for (auto& obstacle : obstacles) {
    window.draw(obstacle.obstacleSprite);
  }
}

void Obstacles::reset() {
  obstacles.clear();
}