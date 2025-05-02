#include "Scores.h"
#include "Constants.h"

Scores::Scores(SDL_Renderer* renderer, Sound* soundManager) 
    : font(nullptr), 
      sound(soundManager),
      scores(0), 
      previousScore(0), 
      scoresIndex(0), 
      scoresDiff(0), 
      scoresInital(0) {
    
    // Initialize TTF
    font = TTF_OpenFont("assets/Fonts/Font.ttf", 24);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    
    // Initialize score textures
    update(renderer);
}

Scores::~Scores() {
    if (font) TTF_CloseFont(font);
}

void Scores::update(SDL_Renderer* renderer) {
    if (!playerDead) {
        // Increment score counter
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
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, std::to_string(scores).c_str(), textColor);
    if (scoreSurface) {
        scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        
        // Position in top right
        scoreRect.x = windowSize_x - scoreSurface->w - 20;
        scoreRect.y = 20;
        scoreRect.w = scoreSurface->w;
        scoreRect.h = scoreSurface->h;
        
        SDL_FreeSurface(scoreSurface);
    }
    
    // Update high score if necessary
    if (scores > previousScore) {
        previousScore = scores;
    }
    
    // Create "HI" text
    SDL_Surface* hiTextSurface = TTF_RenderText_Solid(font, "HI", textColor);
    if (hiTextSurface) {
        hiTextTexture = SDL_CreateTextureFromSurface(renderer, hiTextSurface);
        
        hiTextRect.x = scoreRect.x - hiTextSurface->w - 40;
        hiTextRect.y = 20;
        hiTextRect.w = hiTextSurface->w;
        hiTextRect.h = hiTextSurface->h;
        
        SDL_FreeSurface(hiTextSurface);
    }
    
    // Create previous score texture
    SDL_Surface* prevScoreSurface = TTF_RenderText_Solid(font, std::to_string(previousScore).c_str(), textColor);
    if (prevScoreSurface) {
        prevScoreTexture = SDL_CreateTextureFromSurface(renderer, prevScoreSurface);
        
        prevScoreRect.x = hiTextRect.x + hiTextRect.w + 10;
        prevScoreRect.y = 20;
        prevScoreRect.w = prevScoreSurface->w;
        prevScoreRect.h = prevScoreSurface->h;
        
        SDL_FreeSurface(prevScoreSurface);
    }
}



void Scores::render(SDL_Renderer* renderer) {
    // Render current score
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
    
    // Render high score label and value
    SDL_RenderCopy(renderer, hiTextTexture, nullptr, &hiTextRect);
    SDL_RenderCopy(renderer, prevScoreTexture, nullptr, &prevScoreRect);
}

void Scores::reset(SDL_Renderer* renderer) {
    // Reset current score, but keep high score
    scores = 0;
    scoresIndex = 0;
    scoresDiff = 0;
    scoresInital = 0;
    
    // Reset game speed to initial value
    gameSpeed = 4;
    
    // Update score display
    update(renderer);
}