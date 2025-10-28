#include "PauseScreen.h"
#include "raylib.h"
#include "Utils.h"
#include "MainMenu.h"
#include "Screens.h"
#include "Player.h"
#include "Audio.h"

Texture2D popUp;
Texture2D buttonResume;
Texture2D buttonMainMenu;
Texture2D buttonExitGame;

Rectangle resumeRec;
Rectangle mainRec;
Rectangle exitGameRec;


void InitPauseScreen()
{
    popUp = LoadTexture("../res/PausePopUp.png");
    buttonResume = LoadTexture("../res/buttonResume.png");
    buttonMainMenu = LoadTexture("../res/buttonMain.png");
    buttonExitGame = LoadTexture("../res/buttonExit.png");

    float centerX = screenWidth / 2.0f;
    float startY = 350.0f;
    float spacing = 80.0f;

    resumeRec = { centerX - buttonResume.width / 2.0f, startY + spacing * 0, (float)buttonResume.width, (float)buttonResume.height };
    mainRec = { centerX - buttonMainMenu.width / 2.0f, startY + spacing * 2, (float)buttonMainMenu.width, (float)buttonMainMenu.height };
    exitGameRec = { centerX - buttonExitGame.width / 2.0f, startY + spacing * 2.9f, (float)buttonExitGame.width, (float)buttonExitGame.height };

}

void UpdatePauseScreen()
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
        if (CheckCollisionPointRec(mousePoint, resumeRec))
        {
            PlaySound(clickSound);
            isPaused = false;  // continuar el juego
        }
        else if (CheckCollisionPointRec(mousePoint, mainRec))
        {
            isPaused = false;
            player.score = 0;
            ResetTimer();
            PlaySound(clickSound);
            currentScreen = GameScreen::MENU;


        }
        else if (CheckCollisionPointRec(mousePoint, exitGameRec))
        {
            PlaySound(clickSound);
            isPaused = false;
            currentScreen = GameScreen::EXIT;
        }
    }

    mousePressedLastFrame = mousePressed;
}


void DrawPauseScreen()
{
    Color hover = { 255, 255, 255, 200 };

    /*DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));*/
    DrawTexture(popUp, 245, 100, WHITE);
    DrawTexture(buttonResume, resumeRec.x, resumeRec.y, CheckCollisionPointRec(mousePoint, resumeRec) ? hover : WHITE);
    DrawTexture(buttonMainMenu, mainRec.x, mainRec.y, CheckCollisionPointRec(mousePoint, mainRec) ? hover : WHITE);
    DrawTexture(buttonExitGame, exitGameRec.x, exitGameRec.y, CheckCollisionPointRec(mousePoint, exitGameRec) ? hover : WHITE);
}
