#include "MainMenu.h"
#include "Utils.h"
#include "Screens.h"
#include "raylib.h"

Texture2D background;
Texture2D buttonPlay;
Texture2D buttonHowTo;
Texture2D buttonCredits;
Texture2D buttonExit;

Rectangle playRec;
Rectangle howToRec;
Rectangle creditsRec;
Rectangle exitRec;

Vector2 mousePoint = { 0 };
bool mousePressedLastFrame = false;

void InitMainMenu()
{
    background = LoadTexture("../res/background.png");
    buttonPlay = LoadTexture("../res/buttonPlay.png");
    buttonHowTo = LoadTexture("../res/buttonHow.png");
    buttonCredits = LoadTexture("../res/buttonCredits.png");
    buttonExit = LoadTexture("../res/buttonQuit.png");

    float centerX = screenWidth / 4.0f;
    float startY = 350.0f;
    float spacing = 80.0f;

    playRec = { centerX - buttonPlay.width / 2.0f, startY + spacing * 0, (float)buttonPlay.width, (float)buttonPlay.height };
    howToRec = { centerX - buttonHowTo.width / 2.0f, startY + spacing * 1.1f, (float)buttonHowTo.width, (float)buttonHowTo.height };
    creditsRec = { centerX - buttonCredits.width / 2.0f, startY + spacing * 2, (float)buttonCredits.width, (float)buttonCredits.height };
    exitRec = { centerX - buttonExit.width / 2.0f, startY + spacing * 2.9f, (float)buttonExit.width, (float)buttonExit.height };
}

void UpdateMainMenu()
{
    mousePoint = GetMousePosition();
    bool mousePressed = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    if (mousePressed && !mousePressedLastFrame)
    {
        if (CheckCollisionPointRec(mousePoint, playRec))
            currentScreen = GameScreen::GAMEPLAY;
        else if (CheckCollisionPointRec(mousePoint, howToRec))
            currentScreen = GameScreen::HOWTO;
        else if (CheckCollisionPointRec(mousePoint, creditsRec))
            currentScreen = GameScreen::CREDITS;
        else if (CheckCollisionPointRec(mousePoint, exitRec))
            currentScreen = GameScreen::EXIT;
    }

    mousePressedLastFrame = mousePressed;
}

void DrawMainMenu()
{
    DrawTexture(background, 0, 0, WHITE);

    Color hover = { 255, 255, 255, 200 };

    DrawTexture(buttonPlay, playRec.x, playRec.y, CheckCollisionPointRec(mousePoint, playRec) ? hover : WHITE);
    DrawTexture(buttonHowTo, howToRec.x, howToRec.y, CheckCollisionPointRec(mousePoint, howToRec) ? hover : WHITE);
    DrawTexture(buttonCredits, creditsRec.x, creditsRec.y, CheckCollisionPointRec(mousePoint, creditsRec) ? hover : WHITE);
    DrawTexture(buttonExit, exitRec.x, exitRec.y, CheckCollisionPointRec(mousePoint, exitRec) ? hover : WHITE);
}
