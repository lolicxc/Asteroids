#include "Audio.h"

Music mainMenuMusic;
Music gameMusicMusic;
Sound shootSound;
Sound clickSound;
Sound shipSound;
Sound explotion;
Sound asteroidExpo;

void InitAudio()
{
    mainMenuMusic = LoadMusicStream("res/mainmenu.wav");
    gameMusicMusic = LoadMusicStream("res/gameplay.wav");
    shootSound = LoadSound("res/shoot.wav");
    clickSound = LoadSound("res/hover.wav");
    shipSound = LoadSound("res/shipSound.wav");
    explotion = LoadSound("res/explotion.wav");
    asteroidExpo = LoadSound("res/asteroidExplotion.wav");
}

void UnloadAudio()
{
    UnloadMusicStream(mainMenuMusic);
    UnloadMusicStream(gameMusicMusic);
    UnloadSound(shootSound);
    UnloadSound(clickSound);
    UnloadSound(shipSound);
}