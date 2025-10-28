#pragma once


enum class GameScreen
{
    MENU,
    GAMEPLAY,
    PAUSE,
    HOWTO,
    CREDITS,
    GAMEOVER,
    EXIT
};


extern GameScreen currentScreen;
extern bool isPaused;