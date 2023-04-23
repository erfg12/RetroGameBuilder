cmake_minimum_required(VERSION 3.6)

project(MY_APP)

find_library(SDL2 SDL2 SDL2_mixer SDL2_ttf)

add_library(main SHARED)

target_sources(main PRIVATE ../../../../game/main.cpp ../../../../game/shared.cpp)

target_link_libraries(main SDL2 SDL2_mixer SDL2_ttf)


