#include "Asteroids.h"
#include "Bullet.h"
#include "Player.h"
#include "Utils.h"
#include "raylib.h"
#include <cmath>
#include "Screens.h"
#include "Audio.h"

Asteroid asteroids[MAX_ASTEROIDS];
extern Bullet bullets[MAX_BULLETS];
extern Player player;

Texture2D asteroidBigTex;
Texture2D asteroidMedTex;
Texture2D asteroidSmallTex;


static Vector2 RandomVelocity(float speed)
{
    float angle = GetRandomValue(0, 360) * DEG2RAD;
    return { cosf(angle) * speed, sinf(angle) * speed };
}


void InitAsteroids()
{
   
    asteroidBigTex = LoadTexture("res/asteroidBig.png");
    asteroidMedTex = LoadTexture("res/asteroidMedium.png");
    asteroidSmallTex = LoadTexture("res/asteroidSmall.png");

   
    for (int i = 0; i < MAX_ASTEROIDS; i++)
        asteroids[i].isActive = false;

  
    for (int i = 0; i < 4; i++)
    {
        asteroids[i].isActive = true;
        asteroids[i].size = AsteroidSize::BIG;
        asteroids[i].texture = asteroidBigTex;
        asteroids[i].radius = asteroidBigTex.width / 2.0f; 
        asteroids[i].position = {
            (float)GetRandomValue(0, GetScreenWidth()),
            (float)GetRandomValue(0, GetScreenHeight())
        };
        asteroids[i].velocity = RandomVelocity(150.0f);
    }
}


void SplitAsteroid(int index, AsteroidSize newSize)
{
    Vector2 pos = asteroids[index].position;

    Texture2D newTexture;
    float newRadius = 0.0f;
    switch (newSize)
    {
    case AsteroidSize::BIG:    newTexture = asteroidBigTex;    newRadius = asteroidBigTex.width / 2.0f; break;
    case AsteroidSize::MEDIUM: newTexture = asteroidMedTex;    newRadius = asteroidMedTex.width / 2.0f; break;
    case AsteroidSize::SMALL:  newTexture = asteroidSmallTex;  newRadius = asteroidSmallTex.width / 2.0f; break;
    }

    int created = 0;
    for (int i = 0; i < MAX_ASTEROIDS && created < 2; i++)
    {
        if (!asteroids[i].isActive)
        {
            asteroids[i].isActive = true;
            asteroids[i].size = newSize;
            asteroids[i].texture = newTexture;
            asteroids[i].radius = newRadius;

            
            float angle = (created == 0) ? 45.0f * DEG2RAD : 135.0f * DEG2RAD;
            float offset = newRadius; 
            asteroids[i].position = {
                pos.x + cosf(angle) * offset,
                pos.y + sinf(angle) * offset
            };

            asteroids[i].velocity = RandomVelocity(150.0f);
            created++;
        }
    }

 
    asteroids[index].isActive = false;
}

void UpdateAsteroids()
{
    float delta = GetFrameTime();
    int activeCount = 0;
    float bulletRadius = 4.0f;

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].isActive) continue;

        // mover asteroide
        asteroids[i].position.x += asteroids[i].velocity.x * delta;
        asteroids[i].position.y += asteroids[i].velocity.y * delta;

        // wrap-around
        if (asteroids[i].position.x < -asteroids[i].radius) asteroids[i].position.x = GetScreenWidth() + asteroids[i].radius;
        if (asteroids[i].position.x > GetScreenWidth() + asteroids[i].radius) asteroids[i].position.x = -asteroids[i].radius;
        if (asteroids[i].position.y < -asteroids[i].radius) asteroids[i].position.y = GetScreenHeight() + asteroids[i].radius;
        if (asteroids[i].position.y > GetScreenHeight() + asteroids[i].radius) asteroids[i].position.y = -asteroids[i].radius;

        // Colisiones con balas
        for (int j = 0; j < MAX_BULLETS; j++)
        {
            if (!bullets[j].isActive) continue;

            float actualRadius = asteroids[i].radius;
           
            if (asteroids[i].size == AsteroidSize::SMALL) actualRadius += 6.0f;

            if (CollisionCircles(asteroids[i].position, actualRadius, bullets[j].bulletPos, bulletRadius))
            {
                PlaySound(asteroidExpo);
                bullets[j].isActive = false;

                switch (asteroids[i].size)
                {
                case AsteroidSize::BIG:    player.score += 20; break;
                case AsteroidSize::MEDIUM: player.score += 50; break;
                case AsteroidSize::SMALL:  player.score += 100; break;
                }

                if (asteroids[i].size == AsteroidSize::BIG)
                    SplitAsteroid(i, AsteroidSize::MEDIUM);
                else if (asteroids[i].size == AsteroidSize::MEDIUM)
                    SplitAsteroid(i, AsteroidSize::SMALL);

                asteroids[i].isActive = false;
                break;
            }
        }

        // Colision con el jugador
        float playerRadius = (player.texture.width / player.maxFrames) * 0.4f;
        if (!player.isInvulnerable && CollisionCircles(asteroids[i].position, asteroids[i].radius, player.position, playerRadius))
        {
            PlaySound(explotion);
            player.lives--;
            player.isHit = true;        // activar animacion
            player.hitTimer = 0.0f;    // reinicia temporizador

            player.isInvulnerable = true;
            player.invulnerableTimer = 0.0f;


            if (player.lives <= 0 && !player.isDead)
            {
                player.isDead = true;
                currentScreen = GameScreen::GAMEOVER;
            }
          
        }


        if (asteroids[i].isActive)
            activeCount++;
    }

    if (activeCount < 6)
        SpawnAsteroid();

}


void SpawnAsteroid()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].isActive)
        {
            asteroids[i].isActive = true;
            asteroids[i].size = AsteroidSize::BIG;
            asteroids[i].texture = asteroidBigTex;
            asteroids[i].radius = asteroidBigTex.width / 2.0f;

            int side = GetRandomValue(0, 3);
            switch (side)
            {
            case 0: asteroids[i].position = { -asteroids[i].radius, (float)GetRandomValue(0, GetScreenHeight()) }; break;
            case 1: asteroids[i].position = { GetScreenWidth() + asteroids[i].radius, (float)GetRandomValue(0, GetScreenHeight()) }; break;
            case 2: asteroids[i].position = { (float)GetRandomValue(0, GetScreenWidth()), -asteroids[i].radius }; break;
            case 3: asteroids[i].position = { (float)GetRandomValue(0, GetScreenWidth()), GetScreenHeight() + asteroids[i].radius }; break;
            }

            asteroids[i].velocity = RandomVelocity(100.0f + GetRandomValue(0, 50));
            break;
        }
    }
}


void DrawAsteroids()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].isActive) continue;

        Texture2D tex = asteroids[i].texture;
        Rectangle sourceRec = { 0, 0, (float)tex.width, (float)tex.height }; 
        Rectangle destRec = { asteroids[i].position.x, asteroids[i].position.y, (float)tex.width, (float)tex.height };         
        Vector2 origin = { tex.width / 2.0f, tex.height / 2.0f };          

        DrawTexturePro(tex, sourceRec, destRec, origin, 0.0f, WHITE);
    }
}
//
//void DrawAsteroidBoundingCircle()
//{
//    for (int i = 0; i < MAX_ASTEROIDS; i++)
//    {
//        if (!asteroids[i].isActive) continue;
//
//        float displayRadius = asteroids[i].radius;
//        if (asteroids[i].size == AsteroidSize::SMALL)
//            displayRadius += 6.0f; 
//
//        DrawCircleLines((int)asteroids[i].position.x,
//            (int)asteroids[i].position.y,
//            displayRadius,
//            RED);
//    }
//}

