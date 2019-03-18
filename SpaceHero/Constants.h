#pragma once

#include <windows.h>
#include <string>

const wchar_t CLASS_NAME[] = L"MyWindowClass";
const wchar_t GAME_TITLE[] = L"SPACE HERO";

// Width and height of game in pixels
const UINT GAME_WIDTH{ 800 };
const UINT GAME_HEIGHT{ 600 };

// Objects IDs
const int playerID { 0 };
const int asteroidID { 1 };
const int projectileID { 2 };
const int startbuttonID { 3 };
const int gameLogoID { 4 };
const int explosionID{ 5 };
const int hudID{ 6 };
const int energyUI_ID{ 7 };
const int energybarID{ 8 };
const int fuelbarID{ 9 };
const int scoreBarID{ 10 };

// Asteroids masses
const float sAsteroidMass{ 15.0f };
const float mAsteroidMass{ 30.0f };
const float xlAsteroidMass{ 60.0f };

// Player stats
int const MaxPlayerHealth{ 130 };
int const MaxShipFuel{ 130 };

enum class GameState { Run, Pause, MainManu, GameOver, ResetLevel, LevelComplete, TheEnd };
enum class PlayerState { active, crashed, invulnerable, dead, reset, pause };

const float GravityCoef{0.5f};


