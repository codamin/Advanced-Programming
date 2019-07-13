cmake_minimum_required(VERSION 3.12)
project(Mafia)

set(CMAKE_CXX_STANDARD 98)

add_executable(Mafia main.cpp Room.cpp Room.h functions.cpp Game.cpp Game.h functions.h Player.cpp Player.h Detective.cpp Detective.h Doctor.cpp Doctor.h Joker.cpp Joker.h Godfather.cpp Godfather.h RouinTan.cpp RouinTan.h Silencer.cpp Silencer.h Simple_mafia.cpp Simple_mafia.h Simple_villager.cpp Simple_villager.h Vote.cpp Vote.h)