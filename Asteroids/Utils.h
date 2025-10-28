#pragma once
#include "raylib.h"

const int screenWidth = 1024;
const int screenHeight = 768;

extern Font font;

extern float gameTime; 

void LoadGameFont();
bool CollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);
void UpdateTimer();
void ResetTimer();
void DrawTimer();
