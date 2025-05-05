#include "SoundManager.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;
Sound::Sound() 
    :   dieSound(NULL), jumpSound(NULL), pointSound(NULL) {
    dieSound = Mix_LoadWAV("assets/Sounds/Die.wav");
    jumpSound = Mix_LoadWAV("assets/Sounds/Jump.wav");
    pointSound = Mix_LoadWAV("assets/Sounds/Point.wav");
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