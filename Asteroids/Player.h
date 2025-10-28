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

    int lives;
    Texture2D livesText;
    bool isDead;

    // Animaci�n choque
    int currentFrame = 0;
    int maxFrames = 4;
    float frameTime = 0.1f;    // cada frame dura 0.1 segundos
    float frameTimer = 0.0f;
    bool isHit = false;
    float hitTimer = 0.0f;       // temporizador de duraci�n de la animaci�n
    float hitDuration = 0.8f;    // duraci�n total de la animaci�n (segundos)

    bool isInvulnerable = false;
    float invulnerableTimer = 0.0f;
    float invulnerableDuration = 4.0f;
};

extern Player player;

void InitPlayer();
void UpdatePlayer();
void DrawPlayer();
void DrawScore();
void DrawLives();

