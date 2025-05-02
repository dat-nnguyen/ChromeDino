#include "Dino.h"
#include "Obstacles.h"
#include <SDL2/SDL_image.h>

Dino::Dino(SDL_Renderer* renderer, Sound* soundManager) 
    : animationCounter(0), posY(windowSize_y - 150.0f), velocityY(0), sound(soundManager), deathTime(0) {
    
    dinoTexture = IMG_LoadTexture(renderer, "assets/Images/PlayerSpriteSheet.png");
    
    if (dinoTexture) {
        // Set up animation frames from sprite sheet
        for (size_t i = 0; i < frames.size(); i++) {
            frames[i].x = i * FRAME_WIDTH;
            frames[i].y = 0;
            frames[i].w = FRAME_WIDTH;
            frames[i].h = FRAME_HEIGHT;
        }
        
        // Initialize source rect to first frame
        srcRect = frames[0];
        
        // Set up destination rectangle
        destRect.x = windowSize_x / 2 - windowSize_x / 4;
        destRect.y = posY;
        destRect.w = FRAME_WIDTH;
        destRect.h = FRAME_HEIGHT;
        
        // Set up collision rectangle (slightly smaller than visual)
        collisionRect = destRect;
        collisionRect.h -= 15;
        collisionRect.w -= 10;
    } else {
        std::cout << "Error loading the PlayerSprite texture" << std::endl;
    }
}

Dino::~Dino() {
    SDL_DestroyTexture(dinoTexture);
}

void Dino::update(Uint32 currentTime, std::vector<Obstacle>& obstacles) {
  // Update vertical position and collision box
  destRect.y = static_cast<int>(posY);
  collisionRect.x = destRect.x;
  collisionRect.y = destRect.y;
  bool hasPlayedDeathSound = false;
  // Check collision
  for (auto& obs : obstacles) {
      SDL_Rect result;
      if (SDL_IntersectRect(&collisionRect, &obs.collisionRect, &result)) {
          if (!playerDead) {
              playerDead = true;
              deathTime = currentTime;
              hasPlayedDeathSound = false;
          }
          break;
      }
  }

  if (!playerDead) {
      walk();  // Handle walking animation

      const Uint8* state = SDL_GetKeyboardState(NULL);

      // Handle jump input
      bool onGround = posY >= windowSize_y - 150.0f;
      bool jumping = state[SDL_SCANCODE_SPACE];

      if (jumping && onGround) {
        animationCounter = 0;
        velocityY = JUMP_VELOCITY;
        srcRect = frames[1]; // Jump frame
        sound->playJumpSound();
    }
    
      // Apply gravity
    velocityY += GRAVITY;

      // Apply velocity
      posY += velocityY;

      // Clamp to ground
      if (posY >= windowSize_y - 150.0f) {
          posY = windowSize_y - 150.0f;
          velocityY = 0.0f;
      }

      // Choose animation frame
      srcRect = (posY < windowSize_y - 150.0f) ? frames[1] : srcRect;

  } else {
      // Handle death state
      velocityY = 0.0f;
      srcRect = frames[3]; // Death frame

      if (!hasPlayedDeathSound && currentTime - deathTime < 170) {
          sound->playDieSound();
          hasPlayedDeathSound = true;
      }
  }
}


void Dino::walk() {
    for (int i = 0; i < frames.size() - 3; i++) {
        if (animationCounter == (i + 1) * 3) {
            srcRect = frames[i];
        }
    }
    
    if (animationCounter >= (frames.size() - 2) * 3) {
        animationCounter = 0;
    }
    
    animationCounter++;
}

void Dino::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, dinoTexture, &srcRect, &destRect);
}

void Dino::reset() {
  velocityY = 0;
  posY = groundOffset;
  srcRect = frames[0];
}

