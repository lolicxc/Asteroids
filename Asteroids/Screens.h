#pragma once

// Enumeración de todas las pantallas del juego
enum class GameScreen
{
    MENU,
    GAMEPLAY,
    HOWTO,
    CREDITS,
    EXIT
};

// Variable global para saber en qué pantalla estamos
extern GameScreen currentScreen;
