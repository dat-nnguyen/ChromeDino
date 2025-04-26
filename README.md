to execute, run the command in terminal:

g++ -std=c++17 main.cpp GameState.cpp Dino.cpp Ground.cpp Obstacles.cpp Scores.cpp Clouds.cpp RestartButton.cpp TextureManager.cpp SoundManager.cpp Constants.cpp -o dino -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

./Dino
