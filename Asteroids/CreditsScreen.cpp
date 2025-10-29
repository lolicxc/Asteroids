#include "CreditsScreen.h"
#include "screens.h"  
#include "Utils.h"    

Texture2D creditsBackground;
Texture2D bBack;
Rectangle bRec;

Texture2D button1Tex;
Texture2D button2Tex;
Texture2D button3Tex;

Rectangle button1Rec;
Rectangle button2Rec;
Rectangle button3Rec;

Vector2 creditsMousePoint = { 0 };
bool creditsMousePressedLastFrame = false;

void InitCreditsScreen()
{
	creditsBackground = LoadTexture("res/CreditsScreen.png");
	bBack = LoadTexture("res/buttonBack.png");     

	button1Tex = LoadTexture("res/itchioLink.png");
	button2Tex = LoadTexture("res/artStationLink.png");
	button3Tex = LoadTexture("res/musicLink.png");

	float centerX = screenWidth / 2.0f - 20;
	float startY = 290.0f;
	float spacing = 100.0f;

	button1Rec = { centerX - button1Tex.width / 2.0f, startY + 0 * spacing, (float)button1Tex.width, (float)button1Tex.height };
	button2Rec = { centerX - button2Tex.width / 2.0f, startY + 1 * spacing, (float)button2Tex.width, (float)button2Tex.height };
	button3Rec = { centerX - button3Tex.width / 2.0f, startY + 2 * spacing, (float)button3Tex.width, (float)button3Tex.height };


	float buttonX = (screenWidth - bBack.width) / 2.0f;
	float buttonY = screenHeight - bBack.height - 50.0f;
	bRec = { buttonX, buttonY, (float)bBack.width, (float)bBack.height };
}

void UpdateCreditsScreen()
{
	creditsMousePoint = GetMousePosition();
	bool mousePressed = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

	if (mousePressed && !creditsMousePressedLastFrame)
	{
		if (CheckCollisionPointRec(creditsMousePoint, bRec))
		{
			currentScreen = GameScreen::MENU;
		}

		else if (CheckCollisionPointRec(creditsMousePoint, button1Rec))
		{
			OpenURL("https://lolicxc.itch.io/");
		}
		else if (CheckCollisionPointRec(creditsMousePoint, button2Rec))
		{
			OpenURL("https://www.artstation.com/mariadolorescaparroz");
		}
		else if (CheckCollisionPointRec(creditsMousePoint, button3Rec))
		{
			OpenURL("https://pixabay.com/users/lnplusmusic-47631836/");
		}
	}

	creditsMousePressedLastFrame = mousePressed;
}

void DrawCreditsScreen()
{
	DrawTexture(creditsBackground, 0, 0, WHITE);

	
	Color hover = { 255, 255, 255, 200 };
	DrawTexture(bBack, bRec.x, bRec.y, CheckCollisionPointRec(creditsMousePoint, bRec) ? hover : WHITE);
	DrawTexture(button1Tex, button1Rec.x, button1Rec.y, CheckCollisionPointRec(creditsMousePoint, button1Rec) ? hover : WHITE);
	DrawTexture(button2Tex, button2Rec.x, button2Rec.y, CheckCollisionPointRec(creditsMousePoint, button2Rec) ? hover : WHITE);
	DrawTexture(button3Tex, button3Rec.x, button3Rec.y, CheckCollisionPointRec(creditsMousePoint, button3Rec) ? hover : WHITE);
}


