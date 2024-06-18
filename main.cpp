#include <raylib.h>
#include <iostream>
#include <cmath>
#include <random>

#define BALL_SIZE 20.0f
#define BALL_SPEED 0.1f
#define BAR_SPEED 0.05f
#define BAR_WIDTH 20.0f
#define BAR_HEIGHT 100.0f

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
} Ball;

typedef struct Bar {
    Rectangle rect;
    Color color;
} Bar;

typedef struct Player {
    int score;
} Player;


static const int screenWidth = 1000;
static const int screenHeight = 500;

static bool gameOver = false;
static bool pause = true;
static bool intro = true;
static Ball ball;
static Bar bar1;
static Bar bar2;
static Player player1;
static Player player2;

static void InitGame();
static void UpdateGame();
static void DrawGame();
static void UpdateDrawFrame();
static double GenerateRandomStartPosition();
static Vector2 GenerateRandomStartSpeed();

int main() {
    InitWindow(screenWidth, screenHeight, "Pong");
    InitGame();

    while (!WindowShouldClose())
        UpdateDrawFrame();

    CloseWindow();
    return 0;
}

static double GenerateRandomStartPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-M_PI_4, M_PI_4);
    return dis(gen);
}

static Vector2 GenerateRandomStartSpeed() {
    double angle = GenerateRandomStartPosition();
    if (rand() % 2 == 0) angle += M_PI;

    return (Vector2){(float)cos(angle), (float)sin(angle)};
}

static void RestartPosition() {
    pause = true;
    ball.position = (Vector2){(float)screenWidth / 2, (float)screenHeight / 2};
    ball.speed = (Vector2){GenerateRandomStartSpeed().x * BALL_SPEED, GenerateRandomStartSpeed().y * BALL_SPEED};

    bar1.rect = (Rectangle){10, (float)screenHeight / 2 - BAR_HEIGHT / 2, BAR_WIDTH, BAR_HEIGHT};
    bar2.rect = (Rectangle){(float)screenWidth - BAR_WIDTH - 10, (float)screenHeight / 2 - BAR_HEIGHT / 2, BAR_WIDTH, BAR_HEIGHT};
}

static void InitGame(){
    pause = true;

    ball.radius = BALL_SIZE / 2;
    ball.color = DARKPURPLE;

    bar1.color = BLUE;

    bar2.color = RED;

    RestartPosition();
}

static void UpdateGame() {
    if (!gameOver) {
        if (IsKeyDown(KEY_W) && bar1.rect.y > 0) bar1.rect.y -= BAR_SPEED;
        if (IsKeyDown(KEY_S) && bar1.rect.y + bar1.rect.height < screenHeight) bar1.rect.y += BAR_SPEED;

        if (IsKeyDown(KEY_UP) && bar2.rect.y > 0) bar2.rect.y -= BAR_SPEED;
        if (IsKeyDown(KEY_DOWN) && bar2.rect.y + bar2.rect.height < screenHeight) bar2.rect.y += BAR_SPEED;

        if (IsKeyPressed(KEY_SPACE) && pause) {
            if (intro) intro = !intro;
            pause = !pause;
        }

//        std::cout << "Ball motion: " << ball.speed.x << " " << ball.speed.y << std::endl;

        if (!pause) {
            ball.position.x += ball.speed.x;
            ball.position.y += ball.speed.y;

            if (ball.position.y >= screenHeight - ball.radius || ball.position.y <= ball.radius) ball.speed.y *= -1;

            if (CheckCollisionCircleRec(ball.position, ball.radius, bar1.rect)) {
                float hitPos = (ball.position.y - bar1.rect.y) / BAR_HEIGHT - 0.5f;
                float angle = hitPos * M_PI_4;
                ball.speed.x = BALL_SPEED * cos(angle);
                ball.speed.y = BALL_SPEED * sin(angle);
                if (ball.speed.x < 0) ball.speed.x *= -1;
            }

            if (CheckCollisionCircleRec(ball.position, ball.radius, bar2.rect)) {
                float hitPos = (ball.position.y - bar2.rect.y) / BAR_HEIGHT - 0.5f;
                float angle = hitPos * M_PI_4;
                ball.speed.x = BALL_SPEED * cos(angle);
                ball.speed.y = BALL_SPEED * sin(angle);
                if (ball.speed.x > 0) ball.speed.x *= -1;
            }

            if (ball.position.x >= screenWidth) {
                player1.score++;
                RestartPosition();
            }
            if (ball.position.x <= 0) {
                player2.score++;
                RestartPosition();
            }
        }

    }
}

static void DrawGame(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){173, 216, 230, 255});
    DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, (Color){255, 192, 203, 255});
    DrawRectangle(screenWidth / 2 - 2, 0, 4, screenHeight, RAYWHITE);
    if (!gameOver){
        DrawCircleV(ball.position, ball.radius, ball.color);
//        DrawRectangle(bar1.rect.x, bar1.rect.y, bar1.rect.width, bar1.rect.height, bar1.color);
//        DrawRectangle(bar2.rect.x, bar2.rect.y, bar2.rect.width, bar2.rect.height, bar2.color);
        DrawRectangleRounded(bar1.rect, 2, 10, bar1.color);
        DrawRectangleRounded(bar2.rect, 2, 10, bar2.color);
        int score1Width = MeasureText(TextFormat("%i", player1.score), 40);
        DrawText(TextFormat("%i", player1.score), screenWidth / 2 - score1Width - 30, 20, 40, DARKGRAY);
        DrawText(TextFormat("%i", player2.score), screenWidth / 2 + 30, 20, 40, DARKGRAY);

        if (intro) {
            DrawText("PRESS Space TO START", screenWidth / 2 - MeasureText("PRESS Space TO START", 20) / 2, screenHeight / 2 + 20, 20, DARKGRAY);
            DrawText("OR ESC TO EXIT", screenWidth / 2 - MeasureText("OR ESC TO EXIT", 20) / 2, screenHeight / 2 + 40, 20, DARKGRAY);
        }
    } else {
        DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, DARKGRAY);
    }
    EndDrawing();
}

void UpdateDrawFrame(){
    UpdateGame();
    DrawGame();
}