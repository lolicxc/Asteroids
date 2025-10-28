#include "raylib.h"
#include "Gameplay.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroids.h"
#include "Utils.h"
#include "MainMenu.h"
#include "PauseScreen.h"
#include "Screens.h"

Texture2D backgroundText;
extern Player player;

Texture2D buttonPause;
Rectangle pauseRec;

extern Player player;

void InitGame()
{
    LoadGameFont();
    InitPlayer();
    InitBullet();
    InitAsteroids();
    backgroundText = LoadTexture("../res/gameplayText.png");
    buttonPause = LoadTexture("../res/buttoonPause.png");


    pauseRec = { screenWidth - buttonPause.width - 130.0f, 670.0f, (float)buttonPause.width, (float)buttonPause.height };
}

void UpdateGame()
{
    mousePoint = GetMousePosition();
    bool mousePressed = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    if (mousePressed && !mousePressedLastFrame)
    {
        if (CheckCollisionPointRec(mousePoint, pauseRec))
        {
            isPaused = !isPaused;
            if (isPaused)
            {
                InitPauseScreen();
            }
        
        }
    }

    mousePressedLastFrame = mousePressed;

    if (!isPaused)
    {

        UpdatePlayer();
        UpdateBullet();
        UpdateAsteroids();
    }
    else
    {
        UpdatePauseScreen();
        extern GameScreen currentScreen;
        if (currentScreen != GameScreen::GAMEPLAY)
            return;
    }
}

void DrawGame()
{
 
    DrawTexture(backgroundText,0, 0, WHITE);
    DrawAsteroids();
    DrawBullet();
    DrawPlayer();
    DrawScore();
    DrawTimer();
 /*   DrawAsteroidBoundingCircle();*/
    DrawLives();
  
    Color hover = { 255, 255, 255, 200 };
    DrawTexture(buttonPause, pauseRec.x, pauseRec.y, CheckCollisionPointRec(mousePoint, pauseRec) ? hover : WHITE);

    if (isPaused)
    {
        DrawPauseScreen();
    }
}

