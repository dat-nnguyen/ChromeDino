cmake_minimum_required(VERSION 3.14)
project(ChromeDino)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        src/main.cpp
        src/Clouds.cpp
        "include /Clouds.h"
        src/Dino.cpp
        "include /Dino.h"
        src/FPS.cpp
        "include /FPS.h"
        src/GameState.cpp
        "include /GameState.h"
        src/Ground.cpp
        "include /Ground.h"
        src/Obstacles.cpp
        "include /Obstacles.h"
        src/RestartButton.cpp
        "include /RestartButton.h"
        src/Scores.cpp
        "include /Scores.h"
        src/SoundManager.cpp
        "include /SoundManager.h"

)

add_executable(ChromeDino ${SOURCES}
)

find_package(SFML 3 COMPONENTS Graphics Audio Network Window REQUIRED)
target_link_libraries(ChromeDino PRIVATE SFML::Graphics SFML::Audio SFML::Network SFML::Window)

target_include_directories(ChromeDino PRIVATE src)

add_custom_command(TARGET ChromeDino POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:ChromeDino>/assets
)
