#include "raylib.h"
#include "HowPlayScreen.h"
#include "screens.h"   // para usar currentScreen
#include "Utils.h"     // por screenWidth y screenHeight

Texture2D howBackground;
Texture2D buttonBack;
Rectangle backRec;

Vector2 howMousePoint = { 0 };
bool howMousePressedLastFrame = false;

void InitHowScreen()
{
    howBackground = LoadTexture("../res/HTPScreen.png"); // ??? imagen de fondo
    buttonBack = LoadTexture("../res/buttonBack.png");      // ?? botón de volver

    // centramos el botón abajo
    float buttonX = (screenWidth - buttonBack.width) / 2.0f;
    float buttonY = screenHeight - buttonBack.height - 50.0f;
    backRec = { buttonX, buttonY, (float)buttonBack.width, (float)buttonBack.height };
}

void UpdateHowScreen()
{
    howMousePoint = GetMousePosition();
    bool mousePressed = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    // clic en botón ? volver al menú
    if (mousePressed && !howMousePressedLastFrame &&
        CheckCollisionPointRec(howMousePoint, backRec))
    {
        currentScreen = GameScreen::MENU;
    }

    howMousePressedLastFrame = mousePressed;
}

void DrawHowScreen()
{
    DrawTexture(howBackground, 0, 0, WHITE);

    // efecto hover
    Color hover = { 255, 255, 255, 200 };
    DrawTexture(buttonBack, backRec.x, backRec.y,
        CheckCollisionPointRec(howMousePoint, backRec) ? hover : WHITE);
}

