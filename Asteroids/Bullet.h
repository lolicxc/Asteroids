#pragma once
#include "Player.h"

const int MAX_BULLETS = 20;

struct Bullet
{
	Vector2 bulletPos;
	Vector2 direction;
	Texture2D bulletText;
	bool isActive;
	float speed;
};

void InitBullet();
void UpdateBullet();
void DrawBullet();