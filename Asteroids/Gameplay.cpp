#include "raylib.h"
#include "Gameplay.h"
#include "Player.h"


Texture2D backgroundText;

void InitGame()
{
    InitPlayer();
    backgroundText = LoadTexture("../res/gameplayText.png");
}

void UpdateGame()
{
    UpdatePlayer();
}

void DrawGame()
{
    DrawTexture(backgroundText,0, 0, WHITE);
    DrawPlayer();
}
