#include "raylib.h"
#include "Gameplay.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroids.h"
#include "Utils.h"
#include "MainMenu.h"

Texture2D backgroundText;
extern Player player;

Texture2D buttonPause;

Rectangle pauseRec;

bool isPaused = false;
extern Player player;

void InitGame()
{
    LoadGameFont();
    InitPlayer();
    InitBullet();
    InitAsteroids();
    backgroundText = LoadTexture("../res/gameplayText.png");
    buttonPause = LoadTexture("../res/buttoonPause.png");


    // ?? posición del botón (arriba a la derecha)
    pauseRec = { screenWidth - buttonPause.width - 60.0f, 20.0f, (float)buttonPause.width, (float)buttonPause.height };
}

void UpdateGame()
{
    mousePoint = GetMousePosition();
    bool mousePressed = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    // Detectar clic solo cuando se presiona una vez
    if (mousePressed && !mousePressedLastFrame)
    {
        if (CheckCollisionPointRec(mousePoint, pauseRec))
        {
            isPaused = !isPaused;
        }
    }

    mousePressedLastFrame = mousePressed;

    if (!isPaused)
    {
        UpdatePlayer();
        UpdateBullet();
        UpdateAsteroids();
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
  
    // ?? Dibuja el botón con efecto hover
    Color hover = { 255, 255, 255, 200 };
    DrawTexture(buttonPause, pauseRec.x, pauseRec.y, CheckCollisionPointRec(mousePoint, pauseRec) ? hover : WHITE);

    // ?? Si el juego está pausado, mostrar capa y texto
    if (isPaused)
    {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
        DrawText("PAUSADO", screenWidth / 2 - 100, screenHeight / 2, 40, WHITE);
    }
}
