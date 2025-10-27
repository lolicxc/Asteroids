#include "Player.h"
#include "raymath.h"
#include "Utils.h"

Player player;

void InitPlayer()
{
   
    player.position = { 400, 300 };
    player.velocity = { 0, 0 };
    player.acceleration = { 0, 0 };
    player.speed = 100.0f;   // valor base
    player.rotation = 0.0f;
    player.texture = LoadTexture("../res/nave.png");
}


void UpdatePlayer()
{
    Vector2 posMouse = GetMousePosition();
    Vector2 vectorDireccion = Vector2Subtract(posMouse, player.position);

    player.rotation = atan2(vectorDireccion.y, vectorDireccion.x) * RAD2DEG;


    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        Vector2 dirNormalizada = Vector2Normalize(vectorDireccion);
        player.acceleration = Vector2Scale(dirNormalizada, 200.0f);
    }
    else
    {

        player.acceleration = { 0, 0 };
    }

   
    player.velocity.x += player.acceleration.x * GetFrameTime();
    player.velocity.y += player.acceleration.y * GetFrameTime();
    player.position.x += player.velocity.x * GetFrameTime();
    player.position.y += player.velocity.y * GetFrameTime();

    float halfWidth = player.texture.width / 2.0f;
    float halfHeight = player.texture.height / 2.0f;

    if (player.position.x < -halfWidth) player.position.x = screenWidth + halfWidth;
    if (player.position.x > screenWidth + halfWidth) player.position.x = -halfWidth;
    if (player.position.y < -halfHeight) player.position.y = screenHeight + halfHeight;
    if (player.position.y > screenHeight + halfHeight) player.position.y = -halfHeight;
}

void DrawPlayer()
{
 
    Rectangle source = { 0.0f, 0.0f, (float)player.texture.width, (float)player.texture.height };
    Rectangle dest = { player.position.x, player.position.y, (float)player.texture.width, (float)player.texture.height };
    Vector2 origin = { (float)player.texture.width / 2.0f, (float)player.texture.height / 2.0f };
    DrawTexturePro(player.texture, source, dest, origin, player.rotation, WHITE);
}

void DrawScore()
{
    DrawTextEx(font, TextFormat("Puntos: %i", player.score), { 220, 660 }, 34, 2, ORANGE);
}

