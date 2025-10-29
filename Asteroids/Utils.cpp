#include "Utils.h"
#include <cmath>
#include "Screens.h"

Font font;
float gameTime = 0.0f;


void LoadGameFont()
{
    font = LoadFont("res/CourierPrime-Regular.ttf");
}

bool CollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2)
{
    float dx = center1.x - center2.x;
    float dy = center1.y - center2.y;
    float distance = sqrtf(dx * dx + dy * dy);
    return distance < (radius1 + radius2);
}



void UpdateTimer()
{
    if (!isPaused)
    {
    gameTime += GetFrameTime(); 
    }
}

void ResetTimer()
{
    gameTime = 0.0f;
}

void DrawTimer()
{
    DrawTextEx(font, TextFormat("Time: %.2f", gameTime), { 220, 700 }, 34, 2, ORANGE);

}

