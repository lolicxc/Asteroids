#include "Player.h"
#include "raymath.h"
#include "Utils.h"
#include "Audio.h"

Player player;

void InitPlayer()
{
    player.position = { 400, 300 };
    player.velocity = { 0, 0 };
    player.acceleration = { 0, 0 };
    player.speed = 100.0f;
    player.rotation = 0.0f;
    player.texture = LoadTexture("../res/animationExplo.png");

    player.lives = 5; 
    player.livesText = LoadTexture("../res/life.png"); 
    player.isDead = false;

   
    player.isHit = false;
    player.currentFrame = 0;
    player.frameTimer = 0.0f;
    player.hitTimer = 0.0f;

    player.isInvulnerable = false;
    player.invulnerableTimer = 0.0f;
}

void UpdatePlayer()
{
  
    if (player.isHit)
    {
        player.hitTimer += GetFrameTime();
        player.frameTimer += GetFrameTime();

        if (player.frameTimer >= player.frameTime)
        {
            player.frameTimer = 0.0f;
            player.currentFrame++;
            if (player.currentFrame >= player.maxFrames) player.currentFrame = player.maxFrames - 1; 
        }

       
        player.isInvulnerable = true;
        player.invulnerableTimer += GetFrameTime();

        if (player.hitTimer >= player.hitDuration)
        {
            player.isHit = false;
            player.isInvulnerable = false;   
            player.hitTimer = 0.0f;
            player.currentFrame = 0;

         
            player.position = { 460, 300 };
            player.velocity = { 0, 0 };
            player.acceleration = { 0, 0 };
        }

        return; 
    }

   
    Vector2 posMouse = GetMousePosition();
    Vector2 vectorDireccion = Vector2Subtract(posMouse, player.position);
    player.rotation = atan2(vectorDireccion.y, vectorDireccion.x) * RAD2DEG;

    PlaySound(shipSound);

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

    float halfWidth = player.texture.width / player.maxFrames / 2.0f;
    float halfHeight = player.texture.height / 2.0f;

    if (player.position.x < -halfWidth) player.position.x = screenWidth + halfWidth;
    if (player.position.x > screenWidth + halfWidth) player.position.x = -halfWidth;
    if (player.position.y < -halfHeight) player.position.y = screenHeight + halfHeight;
    if (player.position.y > screenHeight + halfHeight) player.position.y = -halfHeight;


    if (player.isInvulnerable)
    {
        player.invulnerableTimer += GetFrameTime();
        if (player.invulnerableTimer >= player.invulnerableDuration)
            player.isInvulnerable = false;
    }
}




void DrawPlayer()
{
    Rectangle source = { player.currentFrame * (player.texture.width / player.maxFrames), 0, player.texture.width / player.maxFrames, (float)player.texture.height };

    Rectangle dest = { player.position.x, player.position.y, (float)player.texture.width / player.maxFrames, (float)player.texture.height };
    Vector2 origin = { (float)(player.texture.width / player.maxFrames) / 2.0f, (float)player.texture.height / 2.0f };

    DrawTexturePro(player.texture, source, dest, origin, player.rotation, WHITE);
}

void DrawScore()
{
    DrawTextEx(font, TextFormat("Score: %i", player.score), { 220, 660 }, 34, 2, ORANGE);
}

void DrawLives()
{
    for (int i = 0; i < player.lives; i++)
    {
        DrawTexture(player.livesText, 580, 650 + i * (player.livesText.height + 10), WHITE);
    }
}