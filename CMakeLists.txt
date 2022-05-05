cmake_minimum_required(VERSION 3.0)
project(JogoDaForca)
include_directories(./include)
add_executable(
    jogo
    ./src/main.cpp
    ./src/Forca.cpp
)