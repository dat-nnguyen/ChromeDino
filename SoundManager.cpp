#include "SoundManager.h"

Sound::Sound()
    : dieBuffer(),
      jumpBuffer(),
      pointBuffer(),
      dieSound(),
      jumpSound(),
      pointSound() {
    dieBuffer.loadFromFile("assets/Sounds/Die.wav");
    jumpBuffer.loadFromFile("assets/Sounds/Jump.wav");
    pointBuffer.loadFromFile("assets/Sounds/Point.wav");

    dieSound.setBuffer(dieBuffer);
    jumpSound.setBuffer(jumpBuffer);
    pointSound.setBuffer(pointBuffer);
}
