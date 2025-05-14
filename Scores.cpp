#include "Scores.h"
#include "Constants.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;
Scores::Scores(SDL_Renderer* renderer, Sound* soundManager):font(NULL), sound(soundManager),scores(0), scoresIndex(0), scoresDiff(0), scoresInital(0) {
    
    // Initialize TTF
    font = TTF_OpenFont("assets/Fonts/Font.ttf", 24);
    // Initialize score textures
    update(renderer);
}

Scores::~Scores() {
    if (font) TTF_CloseFont(font);
}

void Scores::update(SDL_Renderer* renderer) {
    if (!playerDead) {
        // Increase score counter
        scoresIndex++;
        
        // Update score every 5 frames
        if (scoresIndex >= 5) {
            scores++;
            scoresDiff++;
            scoresIndex = 0;
            
            // Play point sound every 100 points
            if (scores % 100 == 0) {
                sound->playPointSound();
                
                // Update game speed every 100 points (up to a maximum)
                if (gameSpeed < 10) {
                    gameSpeed++;
                }
            }
        }
    }
    
    // Render score text
    SDL_Color textColor = {83, 83, 83, 255}; // Dark gray color
    
    // Create current score texture
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, to_string(scores).c_str(), textColor);
    if (scoreSurface) {
        scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        
        // Position in top right
        scoreRect.x = windowSize_x - scoreSurface->w - 20;
        scoreRect.y = 20;
        scoreRect.w = scoreSurface->w;
        scoreRect.h = scoreSurface->h;
        
        SDL_FreeSurface(scoreSurface);
    }
    
    // Create "SCORE" text
    SDL_Surface* scoreTextSurface = TTF_RenderText_Solid(font, "SCORE", textColor);
    if (scoreTextSurface) {
        scoreTextTexture = SDL_CreateTextureFromSurface(renderer, scoreTextSurface);
        
        scoreTextRect.x = scoreRect.x - scoreTextSurface->w - 30;
        scoreTextRect.y = 20;
        scoreTextRect.w = scoreTextSurface->w;
        scoreTextRect.h = scoreTextSurface->h;
        
        SDL_FreeSurface(scoreTextSurface);
    }   
}



void Scores::render(SDL_Renderer* renderer) {
    // Render current score
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);    
    // Render high score label and value
    SDL_RenderCopy(renderer, scoreTextTexture, NULL, &scoreTextRect);

}

void Scores::reset(SDL_Renderer* renderer) {
    // Reset current score
    scores = 0;
    scoresIndex = 0;
    scoresDiff = 0;
    scoresInital = 0;
    
    // Reset game speed to initial value
    gameSpeed = 4;
    
    // Update score display
    update(renderer);
}