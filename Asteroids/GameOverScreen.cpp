#include "GameOverScreen.h"
#include "raylib.h"
#include "Utils.h"
#include "MainMenu.h"
#include "Screens.h"
#include "Player.h"
#include "Audio.h"
#include "Asteroids.h"

Texture2D popUpGameOver;
Texture2D buttonPlayAgain;
Texture2D buttonMain;


Rectangle playAgainRec;
Rectangle mainmenuRec;



void InitGameOverScreen()
{
    popUpGameOver = LoadTexture("res/GameOverPopUp.png");
    buttonPlayAgain = LoadTexture("res/buttonPlayagain.png");
    buttonMain = LoadTexture("res/buttonMain.png");
 

    float centerX = screenWidth / 2.0f;
    float startY = 350.0f;
    float spacing = 80.0f;

    playAgainRec = { centerX - buttonPlayAgain.width / 2.0f, startY + spacing * 0, (float)buttonPlayAgain.width, (float)buttonPlayAgain.height };
    mainmenuRec = { centerX - buttonMain.width / 2.0f, startY + spacing * 2, (float)buttonMain.width, (float)buttonMain.height };

    mousePressedLastFrame = false; 
}

void UpdateGameOverScreen()
{
    extern Vector2 mousePoint;
    extern bool mousePressedLastFrame;
    extern bool isPaused;
    extern GameScreen currentScreen;
    extern Player player;

    mousePoint = GetMousePosition();
    bool mousePressed = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    if (mousePressed && !mousePressedLastFrame)
    {
        if (CheckCollisionPointRec(mousePoint, playAgainRec))
        {
            PlaySound(clickSound);
            RestartGame();
        }
        else if (CheckCollisionPointRec(mousePoint, mainmenuRec))
        {
            isPaused = false;
            player.score = 0;
            ResetTimer();
            PlaySound(clickSound);
            currentScreen = GameScreen::MENU;


        }
   
    }

    mousePressedLastFrame = mousePressed;
}


void DrawGameOverScreen()
{

 
    Color hover = { 255, 255, 255, 200 };
    /*DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));*/
    DrawTexture(popUpGameOver, 245, 100, WHITE);
    DrawTextEx(font, TextFormat("Score: %i", player.score), { 420, 440 }, 34, 2, ORANGE);
    DrawTexture(buttonPlayAgain, playAgainRec.x, playAgainRec.y, CheckCollisionPointRec(mousePoint, playAgainRec) ? hover : WHITE);
    DrawTexture(buttonMain, mainmenuRec.x, mainmenuRec.y, CheckCollisionPointRec(mousePoint, mainmenuRec) ? hover : WHITE);
}

void RestartGame()
{
    InitPlayer();
    player.lives = 5;       
    player.score = 0;     
    InitAsteroids();        
    currentScreen = GameScreen::GAMEPLAY;

}