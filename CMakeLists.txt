cmake_minimum_required(VERSION 3.14)
project(ChromeDino)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set path to Homebrew-installed SFML@2
set(CMAKE_PREFIX_PATH "/usr/local/opt/sfml@2")

# Source files only (.cpp)
set(SOURCES
        main.cpp
        Clouds.cpp
        Dino.cpp
        Ground.cpp
        Obstacles.cpp
        RestartButton.cpp
        Scores.cpp
        SoundManager.cpp
)

# Executable
add_executable(ChromeDino ${SOURCES})

# SFML setup
find_package(SFML 2.5 REQUIRED COMPONENTS graphics audio network window)

# Link libraries
target_link_libraries(ChromeDino PRIVATE
        sfml-graphics
        sfml-audio
        sfml-network
        sfml-window
)

# Include header folder
target_include_directories(ChromeDino PRIVATE include)

# Copy assets after build
add_custom_command(TARGET ChromeDino POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:ChromeDino>/assets
)
