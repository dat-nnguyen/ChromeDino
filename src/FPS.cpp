//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#include "../include /FPS.h"
#include "../include /Constants.h"

FPS::FPS(): text(font), frameCount(0), fps(0)
{
    font.openFromFile("assets/Fonts/ Font.ttf");
    text.setFont(font);
    text.getCharacterSize();
    text.setPosition(sf::Vector2f(text.getCharacterSize() + 10.f, text.getCharacterSize()));
    text.setFillColor(sf::Color(83, 83, 83));
}


void FPS::update()
{
    if (clock.getElapsedTime().asSeconds() >= 1.f)
    {
        fps = frameCount;
        frameCount = 0;
        clock.restart();
    }
    frameCount++;
    text.setString("FPS: " + std::to_string(fps));
}

void FPS::drawTo(sf::RenderWindow& window)
{
    window.draw(text);
}
