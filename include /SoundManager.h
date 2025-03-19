//
// Created by Nguyen Tuan Dat on 18/3/25.
//

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include<SFML/Audio.hpp>

class SoundManager {
public:
    SoundManager();
private:
    sf::Sound dieSound;
    sf::Sound jumpSound;
    sf::Sound pointSound;
};



#endif //SOUNDMANAGER_H
