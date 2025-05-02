#include "SoundManager.h"

Sound::Sound() 
    : dieSound(nullptr), jumpSound(nullptr), pointSound(nullptr) {
    
    dieSound = Mix_LoadWAV("assets/Sounds/Die.wav");
    jumpSound = Mix_LoadWAV("assets/Sounds/Jump.wav");
    pointSound = Mix_LoadWAV("assets/Sounds/Point.wav");
    
    if (!dieSound) {
        std::cout << "Failed to load die sound: " << Mix_GetError() << std::endl;
    }
    if (!jumpSound) {
        std::cout << "Failed to load jump sound: " << Mix_GetError() << std::endl;
    }
    if (!pointSound) {
        std::cout << "Failed to load point sound: " << Mix_GetError() << std::endl;
    }
}

Sound::~Sound() {
    if (dieSound) Mix_FreeChunk(dieSound);
    if (jumpSound) Mix_FreeChunk(jumpSound);
    if (pointSound) Mix_FreeChunk(pointSound);
}

void Sound::playDieSound() {
    if (dieSound) {
        // Stop any previously playing instances of the sound
        Mix_HaltChannel(-1);
        // Play sound on channel 0 (specific channel) so we can control it
        Mix_PlayChannel(0, dieSound, 0);
    }
}
void Sound::playJumpSound() {
    if (jumpSound) {
        Mix_PlayChannel(-1, jumpSound, 0);
    }
}

void Sound::playPointSound() {
    if (pointSound) {
        Mix_PlayChannel(-1, pointSound, 0);
    }
}