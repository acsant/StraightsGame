cmake_minimum_required(VERSION 3.2)
project(Straights)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES straights.cpp)
add_executable(Straights ${SOURCE_FILES} Card.h Card.cpp Command.h Command.cpp GameManager.h GameManager.cpp Deck.h Deck.cpp Player.h Player.cpp Hand.h Hand.cpp ComputerPlayer.h ComputerPlayer.cpp PlayerID.h PlayerID.cpp HumanPlayer.h HumanPlayer.cpp)