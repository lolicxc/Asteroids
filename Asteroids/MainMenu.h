#pragma once
#include "raylib.h"

enum class MAINMENU
{
    Play,
    HowToPlay,
    Credits,
    Exit,
    None
};

extern MAINMENU currentMenuOption;
extern Vector2 mousePoint;
extern bool mousePressedLastFrame;

void InitMainMenu();
void UpdateMainMenu();
void DrawMainMenu();
