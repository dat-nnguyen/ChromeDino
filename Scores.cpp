#include "Scores.h"

Scores::Scores() // object score doesn't move, but update the score
    : scoresFont(), scoresText(), previousScoreText(), HIText(), scoresInital(),
      sound() {
  if (scoresFont.loadFromFile("assets/Fonts/Font.ttf")) {
    scoresText.setFont(scoresFont);
    scoresText.setCharacterSize(15);
    scoresText.setPosition(
        sf::Vector2f(windowSize_x / 2 + windowSize_x / 4 + 185.f,
                     scoresText.getCharacterSize() + 10.f));
    scoresText.setFillColor(sf::Color(83, 83, 83));

    previousScoreText.setFont(scoresFont);
    previousScoreText.setCharacterSize(15);
    previousScoreText.setPosition(sf::Vector2f(
        scoresText.getPosition().x - 100.f, scoresText.getPosition().y));
    previousScoreText.setFillColor(sf::Color(83, 83, 83));

    HIText.setFont(scoresFont);
    HIText.setCharacterSize(15);
    HIText.setPosition(sf::Vector2f(previousScoreText.getPosition().x - 50.f,
                                    previousScoreText.getPosition().y));
    HIText.setFillColor(sf::Color(83, 83, 83));
  }
  HIText.setString("HI");
  scoresInital = 0;
}

void Scores::update() {
    if (!playerDead) {
        scoresIndex++;
        if (scoresIndex >= 5) {
            scoresIndex = 0;
            scores++;
        }

        scoresDiff = scores - scoresInital;
        if (scoresDiff > 100) {
            scoresInital += 100;
            gameSpeed += 1;
            sound.pointSound.play();
        }

        scoresText.setString(std::to_string(scores));
        previousScoreText.setString(std::to_string(previousScore));
    }
}

void Scores::reset() {
    if (scores > previousScore) {
        previousScore = scores;
    }
    previousScoreText.setString(std::to_string(previousScore));
    scores = 0;
}
