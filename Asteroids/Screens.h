#pragma once

// Enumeraci�n de todas las pantallas del juego
enum class GameScreen
{
    MENU,
    GAMEPLAY,
    HOWTO,
    CREDITS,
    EXIT
};

// Variable global para saber en qu� pantalla estamos
extern GameScreen currentScreen;
