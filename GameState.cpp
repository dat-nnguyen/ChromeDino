#include "GameState.h"

GameState::GameState(SDL_Renderer* renderer) : mouseX(0), mouseY(0), mousePressed(false) {
    // Create sound manager
    Sound* sound = new Sound();
    
    // Initialize game objects
    dino = new Dino(renderer, sound);
    ground = new Ground(renderer);
    obstacles = new Obstacles(renderer);
    scores = new Scores(renderer, sound);
    clouds = new Clouds(renderer);
    restartButton = new RestartButton(renderer);
    
    // Set up game over text
    gameOverFont = TTF_OpenFont("assets/Fonts/Font.ttf", 24);
    
    if (gameOverFont) {
        SDL_Color textColor = {83, 83, 83, 255}; // Dark gray
        SDL_Surface* gameOverSurface = TTF_RenderText_Solid(gameOverFont, "Game Over", textColor);
        gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
        
        // Position game over text above restart button
        gameOverRect.x = restartButton->destRect.x - 10;
        gameOverRect.y = restartButton->destRect.y - 50;
        gameOverRect.w = gameOverSurface->w;
        gameOverRect.h = gameOverSurface->h;
        
        SDL_FreeSurface(gameOverSurface);
    }
}

GameState::~GameState() {
    // Clean up resources
    if (gameOverFont) TTF_CloseFont(gameOverFont);
    if (gameOverTexture) SDL_DestroyTexture(gameOverTexture);
    
    delete dino;
    delete ground;
    delete obstacles;
    delete scores;
    delete clouds;
    delete restartButton;
}

void GameState::handleEvents(SDL_Event& event) {
    // Track mouse position
    if (event.type == SDL_MOUSEMOTION) {
        mouseX = event.motion.x;
        mouseY = event.motion.y;
    }
    
    // Track mouse button state
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            mousePressed = true;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            mousePressed = false;
        }
    }
}

void GameState::update(Uint32 currentTime) {
    // Check for restart button press
    if (playerDead && mousePressed && restartButton->isClicked(mouseX, mouseY)) {
        // Reset game state and objects
        ground->reset();
        obstacles->reset();
        dino->reset();
        scores->reset(nullptr); // No renderer here, will update on next render cycle
        
        playerDead = false;
        mousePressed = false;
    } else {
        // Update game objects
        ground->updateGround();
        obstacles->update(currentTime);
        dino->update(currentTime, obstacles->obstacles);
        clouds->updateClouds(currentTime);
        scores->update(nullptr); // No renderer here, will update on next render cycle
    }
}

void GameState::render(SDL_Renderer* renderer) {
    // Set white background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // Draw clouds
    clouds->render(renderer);
    
    // Draw ground
    ground->render(renderer);
    
    // Draw obstacles
    obstacles->render(renderer);
    
    // Draw scores
    scores->render(renderer);
    
    // Draw dino
    dino->render(renderer);
    
    // Draw game over screen if player is dead
    if (playerDead) {
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
        TextureManager::Draw(restartButton->buttonTexture, restartButton->srcRect, restartButton->destRect, renderer);
    }
    
    SDL_RenderPresent(renderer);
}