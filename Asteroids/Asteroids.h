#pragma once
#include "raylib.h"

enum class AsteroidSize
{
    BIG,
    MEDIUM,
    SMALL 
};

struct Asteroid
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    bool isActive;
    AsteroidSize size;
    Texture2D texture;
};

constexpr int MAX_ASTEROIDS = 30;

extern Asteroid asteroids[MAX_ASTEROIDS];
extern Texture2D asteroidBigTex;
extern Texture2D asteroidMedTex;
extern Texture2D asteroidSmallTex;

void InitAsteroids();
void UpdateAsteroids();
void SpawnAsteroid();
void DrawAsteroids();
void SplitAsteroid(int index, AsteroidSize newSize);
//void DrawAsteroidBoundingCircle();
