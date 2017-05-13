cmake_minimum_required(VERSION 3.6)
project(BlackJackGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        blackjack.c
        blackjack.h
        Hand.c
        Hand.h
        main.c
        testing.c)

add_executable(BlackJackGame ${SOURCE_FILES})