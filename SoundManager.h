#pragma once  // prevent duplicated definition
// kinda like #ifndef SOUND_H

#include <SFML/Audio.hpp>

// sound, easy enough
class Sound {
public:
    sf::SoundBuffer dieBuffer; // buffer is the sound audio from a file
    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer pointBuffer;
    sf::Sound dieSound; // object sounds let us play/loop/stop the buffer, here we only need to play the buffer
    sf::Sound jumpSound;
    sf::Sound pointSound;

    Sound();
};
