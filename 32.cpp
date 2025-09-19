
#include <vector>
#include <algorithm>

//--- Game Objects Structures ---
struct Player {
    Rectangle rect;
    Vector2 speed;
    bool alive = true;
};

struct Laser {
    Rectangle rect;
    bool active = false;
};

struct Alien {
    Rectangle rect;
    bool alive = true;
    Vector2 speed = { 1.0f, 0.0f }; // Initial speed
    bool movingRight = true;
};

//--- Global Variables and Game State ---
const int screenWidth = 800;
const int screenHeight = 600;
const int alienRows = 5;
const int alienCols = 10;
int score = 0;

Player player;
std::vector<Laser> playerLasers;
std::vector<Alien> aliens;

//--- Function Prototypes ---
void InitGame();
void UpdateGame();
void DrawGame();
void CheckCollisions();
void ShootPlayerLaser();
void UpdatePlayer();
void UpdateLasers();
void UpdateAliens();

//--- Main Game Function ---
int main() {
    InitWindow(screenWidth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }

    CloseWindow();
    return 0;
}

//--- Game Logic Functions ---
void InitGame() {
    // Initialize Player
    player.rect = { (float)screenWidth / 2 - 25, (float)screenHeight - 50, 50, 50 };
    player.speed = { 5.0f, 0.0f };

    // Initialize Aliens
    aliens.clear(); // Clear any previous aliens
    for (int row = 0; row < alienRows; row++) {
        for (int col = 0; col < alienCols; col++) {
            Alien newAlien;
            newAlien.rect = { 50.0f + col * 60, 50.0f + row * 40, 40, 30 };
            aliens.push_back(newAlien);
        }
    }
}

void UpdateGame() {
    if (player.alive) {
        UpdatePlayer();
        ShootPlayerLaser();
        UpdateLasers();
        UpdateAliens();
        CheckCollisions();
    }
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw Score
    DrawText(TextFormat("SCORE: %04i", score), 10, 10, 20, WHITE);

    // Draw Player
    if (player.alive) {
        DrawRectangleRec(player.rect, BLUE);
    } else {
        DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, RED);
    }

    // Draw Player Lasers
    for (const auto& laser : playerLasers) {
        if (laser.active) {
            DrawRectangleRec(laser.rect, YELLOW);
        }
    }

    // Draw Aliens
    for (const auto& alien : aliens) {
        if (alien.alive) {
            DrawRectangleRec(alien.rect, GREEN);
        }
    }

    EndDrawing();
}

void CheckCollisions() {
    // Check player lasers against aliens
    for (auto& laser : playerLasers) {
        if (laser.active) {
            for (auto& alien : aliens) {
                if (alien.alive && CheckCollisionRecs(laser.rect, alien.rect)) {
                    alien.alive = false;
                    laser.active = false;
                    score += 10;
                }
            }
        }
    }

    // After checking, remove dead aliens and inactive lasers to save memory
    aliens.erase(std::remove_if(aliens.begin(), aliens.end(), [](const Alien& a){ return !a.alive; }), aliens.end());
    playerLasers.erase(std::remove_if(playerLasers.begin(), playerLasers.end(), [](const Laser& l){ return !l.active; }), playerLasers.end());
}

void UpdatePlayer() {
    if (IsKeyDown(KEY_LEFT) && player.rect.x > 0) {
        player.rect.x -= player.speed.x;
    }
    if (IsKeyDown(KEY_RIGHT) && player.rect.x < screenWidth - player.rect.width) {
        player.rect.x += player.speed.x;
    }
}

void ShootPlayerLaser() {
    if (IsKeyPressed(KEY_SPACE)) {
        Laser newLaser;
        newLaser.rect = { player.rect.x + player.rect.width / 2 - 2.5f, player.rect.y, 5, 10 };
        newLaser.active = true;
        playerLasers.push_back(newLaser);
    }
}

void UpdateLasers() {
    for (auto& laser : playerLasers) {
        if (laser.active) {
            laser.rect.y -= 5;
            if (laser.rect.y < 0) {
                laser.active = false;
            }
        }
    }
}

void UpdateAliens() {
    bool dropDown = false;
    for (auto& alien : aliens) {
        if (alien.alive) {
            if (alien.movingRight) {
                alien.rect.x += alien.speed.x;
                if (alien.rect.x + alien.rect.width >= screenWidth - 10) {
                    dropDown = true;
                }
            } else {
                alien.rect.x -= alien.speed.x;
                if (alien.rect.x <= 10) {
                    dropDown = true;
                }
            }
        }
    }
    
    // Drop down and reverse direction if boundary is hit
    if (dropDown) {
        for (auto& alien : aliens) {
            if (alien.alive) {
                alien.rect.y += 20; // Drop down
                alien.movingRight = !alien.movingRight; // Reverse direction
            }
        }
    }
    
    // Check if aliens have reached the player's level
    for (auto& alien : aliens) {
        if (alien.alive && alien.rect.y + alien.rect.height >= player.rect.y) {
            player.alive = false;
            break;
        }
    }
}