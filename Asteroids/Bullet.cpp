#include "Bullet.h"
#include "cmath"
#include "Asteroids.h"

Bullet bullets[MAX_BULLETS];
extern Player player;
Texture2D bulletTexture;

void InitBullet()
{
	bulletTexture = LoadTexture("../res/bullet.png"); // ejemplo
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i].isActive = false;
		bullets[i].speed = 500.0f;
	}
}

void UpdateBullet()
{
	Vector2 punta =
	{
	player.position.x + cos(player.rotation * DEG2RAD) * (player.texture.height / 2.0f),
	player.position.y + sin(player.rotation * DEG2RAD) * (player.texture.height / 2.0f)
	};

	// Disparo con espacio (o el botón que elijas)
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!bullets[i].isActive)
			{
				bullets[i].isActive = true;
				bullets[i].bulletPos = punta;
				bullets[i].direction = { cos(player.rotation * DEG2RAD), sin(player.rotation * DEG2RAD) };
				break; // usar solo una bala por frame
			}
		}
	}

	// Actualizar balas activas
	float delta = GetFrameTime();
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].isActive)
		{
			bullets[i].bulletPos.x += bullets[i].direction.x * bullets[i].speed * delta;
			bullets[i].bulletPos.y += bullets[i].direction.y * bullets[i].speed * delta;

			// Si sale de la pantalla, la desactivamos
			if (bullets[i].bulletPos.x < 0 || bullets[i].bulletPos.x > GetScreenWidth() ||
				bullets[i].bulletPos.y < 0 || bullets[i].bulletPos.y > GetScreenHeight())
			{
				bullets[i].isActive = false;
			}
		}
	}

}

void DrawBullet()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].isActive)
		{
			DrawTexture(bulletTexture, bullets[i].bulletPos.x, bullets[i].bulletPos.y, WHITE);

		}
	}

}
