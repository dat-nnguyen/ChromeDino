// Created by Nguyen Tuan Dat on 18/3/25.
#include "../include /SoundManager.h"
#include <SFML/Audio.hpp>
#include <iostream>
SoundManager::SoundManager() // No need to initialize sf::Sound explicitly
{
    if (!dieBuffer.loadFromFile("assets/Sounds/die.wav"))
    {
        std::cerr << "Error loading die.wav" << std::endl;
    }
    else
    {
        dieSound.setBuffer(dieBuffer);
    }

    if (!jumpBuffer.loadFromFile("assets/Sounds/jump.wav"))
    {
        std::cerr << "Error loading jump.wav" << std::endl;
    }
    else
    {
        jumpSound.setBuffer(jumpBuffer);
    }

    if (!pointBuffer.loadFromFile("assets/Sounds/point.wav"))
    {
        std::cerr << "Error loading point.wav" << std::endl;
    }
    else
    {
        pointSound.setBuffer(pointBuffer);
    }
}
