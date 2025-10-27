#pragma once
#include "raylib.h"
#include "raymath.h"

struct Player
{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float rotation;
    float speed;
    Texture2D texture;
    int score;

};

void InitPlayer();
void UpdatePlayer();
void DrawPlayer();
void DrawScore();


