#include "GameLoop.h"
#include "raylib.h"
#include "Screens.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "PauseScreen.h"
#include "Utils.h"
#include "HowPlayScreen.h"
#include "Audio.h"
#include "GameOverScreen.h"
#include "CreditsScreen.h"


void RunGame()
{
	InitWindow(screenWidth, screenHeight, "Asteroids");
	InitAudioDevice();
	SetTargetFPS(60);

	InitMainMenu();
	InitGame();
	InitPauseScreen();
	InitHowScreen();
	InitGameOverScreen();
	InitAudio();
	InitCreditsScreen();

	GameScreen lastScreen = GameScreen::EXIT;

	while (!WindowShouldClose())
	{
		UpdateTimer();

		static bool menuPlaying = false;
		static bool gameplayPlaying = false;

		if (currentScreen != lastScreen)
		{
			
			StopMusicStream(mainMenuMusic);
			StopMusicStream(gameMusicMusic);
			menuPlaying = false;
			gameplayPlaying = false;

			lastScreen = currentScreen;
		}

		// reproducir segun pantalla
		switch (currentScreen)
		{
		case GameScreen::HOWTO:
		case GameScreen::CREDITS:
		case GameScreen::MENU:
			if (!menuPlaying)
			{
				PlayMusicStream(mainMenuMusic); 
				menuPlaying = true;
			}
			break;

		case GameScreen::GAMEPLAY:
			if (!gameplayPlaying)
			{
				PlayMusicStream(gameMusicMusic);
				gameplayPlaying = true;
			}
			break;
		}

		
		if (menuPlaying) UpdateMusicStream(mainMenuMusic);
		if (gameplayPlaying) UpdateMusicStream(gameMusicMusic);

		BeginDrawing();

		switch (currentScreen)
		{
		case GameScreen::MENU:
			UpdateMainMenu();
			DrawMainMenu();
			break;

		case GameScreen::GAMEPLAY:
			if (isPaused)
			{
				UpdatePauseScreen();
				DrawPauseScreen();
			}
			else
			{
				UpdateGame();
				DrawGame();
			}
			break;
		case GameScreen::HOWTO:
			UpdateHowScreen(); 
			DrawHowScreen();
			break;
		case GameScreen::CREDITS:
			UpdateCreditsScreen();
			DrawCreditsScreen();
			break;
		case GameScreen::GAMEOVER:
			UpdateGameOverScreen();
			DrawGameOverScreen();
			break;
		case GameScreen::EXIT:
			CloseWindow();
			return;
		}

		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();
}
