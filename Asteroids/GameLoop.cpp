#include "GameLoop.h"
#include "raylib.h"
#include "Utils.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "screens.h"
#include "HowPlayScreen.h"

void RunGame()
{
	InitWindow(screenWidth, screenHeight, "Asteroids");
	SetTargetFPS(60);

	InitMainMenu();

	bool gameplayInitialized = false;
	bool howScreenInitialized = false;  

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		switch (currentScreen)
		{
		case GameScreen::MENU:
			UpdateMainMenu();
			DrawMainMenu();
			break;

		case GameScreen::GAMEPLAY:
			if (!gameplayInitialized)
			{
				InitGame();
				gameplayInitialized = true;
			}

			UpdateGame();
			DrawGame();

			if (IsKeyPressed(KEY_Z))
			{
				currentScreen = GameScreen::MENU;
				gameplayInitialized = false;
			}
			break;

		case GameScreen::HOWTO:

			if (!howScreenInitialized)
			{
				InitHowScreen();
				howScreenInitialized = true;
			}

			UpdateHowScreen();
			DrawHowScreen();

			if (IsKeyPressed(KEY_Z))
			{
				currentScreen = GameScreen::MENU;
				howScreenInitialized = false; // reinicia para la próxima vez
			}
			break;

		case GameScreen::CREDITS:
			// cuando tengas pantalla CREDITS
			// UpdateCreditsScreen();
			// DrawCreditsScreen();
			if (IsKeyPressed(KEY_Z)) currentScreen = GameScreen::MENU;
			break;

		case GameScreen::EXIT:
			CloseWindow();
			return;
		}

		EndDrawing();
	}

	CloseWindow();
}
