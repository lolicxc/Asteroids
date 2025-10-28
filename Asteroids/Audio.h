#pragma once
#include "raylib.h"

extern Music mainMenuMusic;
extern Music gameMusicMusic;
extern Sound shootSound;
extern Sound clickSound;
extern Sound shipSound;
extern Sound explotion;
extern Sound asteroidExpo;

void InitAudio();   // Para cargar todos los sonidos
void UnloadAudio(); // Para liberar sonidos al cerrar

