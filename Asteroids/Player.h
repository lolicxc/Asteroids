#pragma once

struct Player
{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float rotation;
    float speed;
    Texture2D texture;

};

void InitPlayer();
void UpdatePlayer();
void DrawPlayer();


