cmake_minimum_required(VERSION 3.2)
project(Straights)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-2.4)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

set(SOURCE_FILES straights.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} Card.h Card.cpp Command.h Command.cpp GameManager.h GameManager.cpp Deck.h Deck.cpp Player.h Player.cpp Hand.h Hand.cpp ComputerPlayer.h ComputerPlayer.cpp PlayerID.h PlayerID.cpp HumanPlayer.h HumanPlayer.cpp PlayerStrategy.h PlayerStrategy.cpp MemCheck.h MemCheck.cpp DeckGUI.cpp DeckGUI.h TableGUI.cpp TableGUI.h)
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})

