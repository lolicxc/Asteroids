#include "Asteroids.h"
#include "Bullet.h"
#include "Utils.h"
#include "raylib.h"
#include <cmath>

Asteroid asteroids[MAX_ASTEROIDS];
extern Bullet bullets[MAX_BULLETS];
extern Player player;

// ----------------------------------------------------
// ?? Genera un vector aleatorio con velocidad constante
// ----------------------------------------------------
static Vector2 RandomVelocity(float speed)
{
    float angle = GetRandomValue(0, 360) * DEG2RAD;
    return { cosf(angle) * speed, sinf(angle) * speed };
}

// ----------------------------------------------------
// ?? Inicialización de todos los asteroides
// ----------------------------------------------------
void InitAsteroids()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        asteroids[i].isActive = false;
        asteroids[i].texture = LoadTexture("../res/asteroid.png");
    }

    // Crear algunos asteroides grandes al inicio
    for (int i = 0; i < 4; i++)
    {
        asteroids[i].isActive = true;
        asteroids[i].size = AsteroidSize::BIG;
        asteroids[i].radius = 40.0f;
        asteroids[i].position = {
            (float)GetRandomValue(0, GetScreenWidth()),
            (float)GetRandomValue(0, GetScreenHeight())
        };
        asteroids[i].velocity = RandomVelocity(150.0f);
    }
}

// ----------------------------------------------------
// ?? Función para dividir un asteroide en 2 más pequeños
// ----------------------------------------------------
void SplitAsteroid(int index, AsteroidSize newSize)
{
    Vector2 pos = asteroids[index].position;
    asteroids[index].isActive = false; // destruir el original

    float newRadius = 0.0f;
    switch (newSize)
    {
    case AsteroidSize::MEDIUM: newRadius = 20.0f; break;
    case AsteroidSize::SMALL:  newRadius = 10.0f; break;
    }

    // Crear dos nuevos asteroides del siguiente tamaño
    int created = 0;
    for (int i = 0; i < MAX_ASTEROIDS && created < 2; i++)
    {
        if (!asteroids[i].isActive)
        {
            asteroids[i].isActive = true;
            asteroids[i].size = newSize;
            asteroids[i].radius = newRadius;
            asteroids[i].position = pos;
            asteroids[i].velocity = RandomVelocity(150.0f);
            created++;
        }
    }
}

// ----------------------------------------------------
// ?? Actualizar posición y manejar colisiones
// ----------------------------------------------------
void UpdateAsteroids()
{
    float delta = GetFrameTime();
    int activeCount = 0;

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].isActive) continue;

        activeCount++;

        // --- Mover ---
        asteroids[i].position.x += asteroids[i].velocity.x * delta;
        asteroids[i].position.y += asteroids[i].velocity.y * delta;

        // --- Wrap-around con radio ---
        if (asteroids[i].position.x < -asteroids[i].radius)
            asteroids[i].position.x = GetScreenWidth() + asteroids[i].radius;

        if (asteroids[i].position.x > GetScreenWidth() + asteroids[i].radius)
            asteroids[i].position.x = -asteroids[i].radius;

        if (asteroids[i].position.y < -asteroids[i].radius)
            asteroids[i].position.y = GetScreenHeight() + asteroids[i].radius;

        if (asteroids[i].position.y > GetScreenHeight() + asteroids[i].radius)
            asteroids[i].position.y = -asteroids[i].radius;

        // --- Colisiones con balas ---
        for (int j = 0; j < MAX_BULLETS; j++)
        {
            if (!bullets[j].isActive) continue;

            if (CheckCollisionCircleCustom(
                asteroids[i].position, asteroids[i].radius,
                bullets[j].bulletPos, 4.0f))
            {
                bullets[j].isActive = false;

                switch (asteroids[i].size)
                {
                case AsteroidSize::BIG:    player.score += 20; break;
                case AsteroidSize::MEDIUM: player.score += 50; break;
                case AsteroidSize::SMALL:  player.score += 100; break;
                }

                // Dividir según tamaño
                if (asteroids[i].size == AsteroidSize::BIG)
                    SplitAsteroid(i, AsteroidSize::MEDIUM);
                else if (asteroids[i].size == AsteroidSize::MEDIUM)
                    SplitAsteroid(i, AsteroidSize::SMALL);
                else
                    asteroids[i].isActive = false; // Pequeño ? destruido

                break; // Evitar múltiples impactos
            }
        }
    }

    // --- Generar asteroides grandes infinitos ---
    // Siempre mantener al menos 4 asteroides activos
    if (activeCount < 4)
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
            asteroids[i].radius = 40.0f;

            // Aparece en borde aleatorio
            int side = GetRandomValue(0, 3);
            switch (side)
            {
            case 0: // Izquierda
                asteroids[i].position = { -asteroids[i].radius, (float)GetRandomValue(0, GetScreenHeight()) }; break;
            case 1: // Derecha
                asteroids[i].position = { GetScreenWidth() + asteroids[i].radius, (float)GetRandomValue(0, GetScreenHeight()) }; break;
            case 2: // Arriba
                asteroids[i].position = { (float)GetRandomValue(0, GetScreenWidth()), -asteroids[i].radius }; break;
            case 3: // Abajo
                asteroids[i].position = { (float)GetRandomValue(0, GetScreenWidth()), GetScreenHeight() + asteroids[i].radius }; break;
            }

            asteroids[i].velocity = RandomVelocity(100.0f + GetRandomValue(0, 50)); // Velocidad aleatoria
            break;
        }
    }
}
// ----------------------------------------------------
// ?? Dibujar todos los asteroides
// ----------------------------------------------------
void DrawAsteroids()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (asteroids[i].isActive)
            DrawCircleLines(asteroids[i].position.x, asteroids[i].position.y, asteroids[i].radius, RED);
    }
}




// ----------------------------------------------------
// ?? Liberar memoria al salir
// ----------------------------------------------------
void UnloadAsteroids()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        UnloadTexture(asteroids[i].texture);
    }
}
