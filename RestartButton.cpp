#include "RestartButton.h"

RestartButton::RestartButton()
    : restartButtonSprite(),
      restartButtonTexture(),
      mousePos(0.f, 0.f),
      restartButtonSpriteBounds() {
    if (restartButtonTexture.loadFromFile("assets/Images/RestartButton.png")) {
        restartButtonSprite.setTexture(restartButtonTexture);
        restartButtonSprite.setPosition(
            sf::Vector2f(windowSize_x / 2 - restartButtonTexture.getSize().x / 2,
                         windowSize_y / 2));
        restartButtonSpriteBounds = restartButtonSprite.getGlobalBounds();
    }
}
