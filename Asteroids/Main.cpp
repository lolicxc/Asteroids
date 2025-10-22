#include "raylib.h"
#include "Utils.h"
#include "MainMenu.h"
#include "Gameplay.h"

enum class GAMESTATE
{
    MainMenu,
    Playing,
    Exit
};

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Asteroids");
    SetTargetFPS(60);

    GAMESTATE currentState = GAMESTATE::MainMenu;
    InitMainMenu();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        switch (currentState)
        {
        case GAMESTATE::MainMenu:
            UpdateMainMenu();
            DrawMainMenu();

            if (currentMenuOption == MAINMENU::Play)
            {
                InitGame();                      // inicializa la partida
                currentState = GAMESTATE::Playing;
            }
            else if (currentMenuOption == MAINMENU::Exit)
                currentState = GAMESTATE::Exit;
            break;

        case GAMESTATE::Playing:
            UpdateGame();
            DrawGame();

            // ejemplo: volver al menú
            if (IsKeyPressed(KEY_Z))
                currentState = GAMESTATE::MainMenu;
            break;

        case GAMESTATE::Exit:
            CloseWindow();
            return 0;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
