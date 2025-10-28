#pragma once
#include "raylib.h"

extern Texture2D creditsBackground;
extern Texture2D button1Tex;
extern Texture2D button2Tex;
extern Texture2D button3Tex;
extern Texture2D bBack;

extern Rectangle button1Rec;
extern Rectangle button2Rec;
extern Rectangle button3Rec;
extern Rectangle bRec;

extern Vector2 creditsMousePoint;
extern bool creditsMousePressedLastFrame;

void InitCreditsScreen();
void UpdateCreditsScreen();
void DrawCreditsScreen();