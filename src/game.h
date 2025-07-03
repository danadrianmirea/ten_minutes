#pragma once

#include <string>
#include <vector>
#include "raylib.h"
#include "globals.h"

// Forward declarations for game entities
class Bullet;
class Enemy;

class Game
{
public:
    Game(int width, int height);
    ~Game();
    void InitGame();
    void Reset();
    void Update(float dt);
    void HandleInput();
    void UpdateUI();
    void UpdateMenu();

    void Draw();
    void DrawUI();
    void DrawMainMenu();
    void DrawOptionsMenu();
    std::string FormatWithLeadingZeroes(int number, int width);
    void Randomize();

    static bool isMobile;

private:
    // Survival game entities
    struct Player {
        float x, y;
        float radius;
        float speed;
        float angle;
        float gunEndX, gunEndY;
        float edgeX, edgeY;
    };

    struct Bullet {
        float x, y;
        float angle;
        float speed;
        float radius;
        
        void Update(float dt);
        bool IsOffScreen(int screenWidth, int screenHeight);
        void Draw() const;
    };

    struct Enemy {
        float x, y;
        float radius;
        float speed;
        
        Enemy(float playerX, float playerY, int screenWidth, int screenHeight);
        void Update(float dt, float playerX, float playerY);
        void Draw() const;
        bool CollidesWithPlayer(float playerX, float playerY, float playerRadius);
        bool CollidesWithBullet(const Bullet& bullet);
    };

    // Survival game state
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    bool gameActive;
    float gameOverTimer;
    float gameOverDelay;
    bool autoFire;
    float shootTimer;
    float fireRate;
    float enemySpawnRate;
    float lastEnemySpawn;
    int maxEnemies;
    float crosshairSize;
    float crosshairThickness;
    float crosshairGap;

    // Survival game methods
    void SpawnEnemy();
    void ResetSurvivalGame();
    void UpdateSurvivalGame(float dt);
    void DrawSurvivalGame();
    void DrawCrosshair(float mouseX, float mouseY);

    bool isInitialLaunch = true;
    bool isInExitMenu;
    bool lostWindowFocus = false;
    bool gameOver;
    bool isInMainMenu = false;
    bool isInOptionsMenu = false;
    int currentMenuSelection = 0;
    int optionsMenuSelection = 0;
    float soundVolume = 1.0f;
    float musicVolume = 1.0f;
    bool isDraggingSoundSlider = false;
    bool isDraggingMusicSlider = false;
    bool isInExitConfirmation = false;
    bool isMusicPlaying = false;

    // Key repeat variables for options menu
    float keyRepeatDelay = 0.2f;  // Initial delay before repeat starts
    float keyRepeatInterval = 0.03f;  // Interval between repeats
    float leftKeyTimer = 0.0f;
    float rightKeyTimer = 0.0f;
    float upKeyTimer = 0.0f;
    float downKeyTimer = 0.0f;
    bool leftKeyPressed = false;
    bool rightKeyPressed = false;
    bool upKeyPressed = false;
    bool downKeyPressed = false;

    float screenScale;
    RenderTexture2D targetRenderTex;
    Font font;

    int width;
    int height;

    Music backgroundMusic;
    Sound actionSound;
};