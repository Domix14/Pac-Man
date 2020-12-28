cmake_minimum_required(VERSION 3.5)

project(Pac-Man)



set(HEADERS
    include/Engine.h
    include/Entity.h
    include/Game.h
    include/PacManGame.h
    include/ResourceManager.h
    include/PacMan.h
    include/Map.h
    include/Level.h
    include/Coin.h
    include/Ghost.h
    include/ScoreText.h
    include/Blinky.h
    include/Pinky.h
    include/Clyde.h
    include/Inky.h
    include/PowerUp.h
    include/Animation.h
    include/Menu.h
    include/Utilities.h)

set(SOURCE
	src/main.cpp
  src/Engine.cpp
  src/Entity.cpp
  src/Game.cpp
  src/PacManGame.cpp
  src/ResourceManager.cpp
  src/PacMan.cpp
  src/Level.cpp
  src/Coin.cpp
  src/Ghost.cpp
  src/ScoreText.cpp
  src/Blinky.cpp
  src/Clyde.cpp
  src/Inky.cpp
  src/PowerUp.cpp
  src/Animation.cpp
  src/Menu.cpp
  src/Pinky.cpp)

include_directories(
  ${CMAKE_SOURCE_DIR}/include)

add_executable (Pac-Man ${SOURCE} ${HEADERS})
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})


#Find SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window system audio)
if(SFML_FOUND)
	target_link_libraries(Pac-Man sfml-graphics sfml-window sfml-system sfml-audio)
endif(SFML_FOUND)



if(WIN32)
  file(COPY ${SFML_DIR}/../../../bin/openal32.dll
    DESTINATION .)
endif()