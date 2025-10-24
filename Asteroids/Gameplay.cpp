#include "raylib.h"
#include "Gameplay.h"
#include "Player.h"
#include "Bullet.h"

Texture2D backgroundText;
extern Player player;

void InitGame()
{
    InitPlayer();
    InitBullet();
    backgroundText = LoadTexture("../res/gameplayText.png");
}

void UpdateGame()
{

    UpdatePlayer();
    UpdateBullet();
}

void DrawGame()
{
    DrawTexture(backgroundText,0, 0, WHITE);
    DrawBullet();
    DrawPlayer();
}
