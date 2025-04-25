#include "Scores.h"

Scores::Scores(SDL_Renderer* renderer, Sound* soundManager) 
    : scoreTexture(nullptr), prevScoreTexture(nullptr), hiTextTexture(nullptr),
      sound(soundManager), scores(0), previousScore(0), scoresIndex(0), 
      scoresDiff(0), scoresInital(0) {
    
    font = TTF_OpenFont("assets/Fonts/Font.ttf", 15);
    
    if (font) {
        SDL_Color textColor = {83, 83, 83, 255}; // Dark gray
        
        // Create HI text
        SDL_Surface* hiSurface = TTF_RenderText_Solid(font, "HI", textColor);
        hiTextTexture = SDL_CreateTextureFromSurface(renderer, hiSurface);
        
        // Position the HI text
        hiTextRect.x = windowSize_x / 2 + windowSize_x / 4 + 35;
        hiTextRect.y = 25;
        hiTextRect.w = hiSurface->w;
        hiTextRect.h = hiSurface->h;
        SDL_FreeSurface(hiSurface);
        
        // Initialize score text
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, "0", textColor);
        scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        
        // Position the score text
        scoreRect.x = windowSize_x / 2 + windowSize_x / 4 + 185;
        scoreRect.y = 25;
        scoreRect.w = scoreSurface->w;
        scoreRect.h = scoreSurface->h;
        SDL_FreeSurface(scoreSurface);
        
        // Initialize previous score text
        SDL_Surface* prevScoreSurface = TTF_RenderText_Solid(font, "0", textColor);
        prevScoreTexture = SDL_CreateTextureFromSurface(renderer, prevScoreSurface);
        
        // Position the previous score text
        prevScoreRect.x = hiTextRect.x + hiTextRect.w + 15;
        prevScoreRect.y = 25;
        prevScoreRect.w = prevScoreSurface->w;
        prevScoreRect.h = prevScoreSurface->h;
        SDL_FreeSurface(prevScoreSurface);
    }
}

Scores::~Scores() {
    if (font) TTF_CloseFont(font);
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (prevScoreTexture) SDL_DestroyTexture(prevScoreTexture);
    if (hiTextTexture) SDL_DestroyTexture(hiTextTexture);
}

void Scores::update(SDL_Renderer* renderer) {
    if (!playerDead) {
        scoresIndex++;
        if (scoresIndex >= 5) {
            scoresIndex = 0;
            scores++;
        }
        
        scoresDiff = scores - scoresInital;
        if (scoresDiff > 100) {
            scoresInital += 100;
            gameSpeed += 1;
            sound->playPointSound();
        }
        
        // Update score texture
        SDL_Color textColor = {83, 83, 83, 255};
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, std::to_string(scores).c_str(), textColor);
        
        if (scoreTexture) {
            SDL_DestroyTexture(scoreTexture);
        }
        
        scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        scoreRect.w = scoreSurface->w;
        scoreRect.h = scoreSurface->h;
        SDL_FreeSurface(scoreSurface);
        
        // Update previous score texture
        SDL_Surface* prevScoreSurface = TTF_RenderText_Solid(font, std::to_string(previousScore).c_str(), textColor);
        
        if (prevScoreTexture) {
            SDL_DestroyTexture(prevScoreTexture);
        }
        
        prevScoreTexture = SDL_CreateTextureFromSurface(renderer, prevScoreSurface);
        prevScoreRect.w = prevScoreSurface->w;
        prevScoreRect.h = prevScoreSurface->h;
        SDL_FreeSurface(prevScoreSurface);
    }
}

void Scores::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, hiTextTexture, NULL, &hiTextRect);
    SDL_RenderCopy(renderer, prevScoreTexture, NULL, &prevScoreRect);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}

void Scores::reset(SDL_Renderer* renderer) {
    if (scores > previousScore) {
        previousScore = scores;
        
        // Update previous score texture
        SDL_Color textColor = {83, 83, 83, 255};
        SDL_Surface* prevScoreSurface = TTF_RenderText_Solid(font, std::to_string(previousScore).c_str(), textColor);
        
        if (prevScoreTexture) {
            SDL_DestroyTexture(prevScoreTexture);
        }
        
        prevScoreTexture = SDL_CreateTextureFromSurface(renderer, prevScoreSurface);
        prevScoreRect.w = prevScoreSurface->w;
        prevScoreRect.h = prevScoreSurface->h;
        SDL_FreeSurface(prevScoreSurface);
    }
    
    scores = 0;
    
    // Reset score texture
    SDL_Color textColor = {83, 83, 83, 255};
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, "0", textColor);
    
    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
    }
    
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    scoreRect.w = scoreSurface->w;
    scoreRect.h = scoreSurface->h;
    SDL_FreeSurface(scoreSurface);
}