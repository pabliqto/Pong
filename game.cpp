#include "game.h"
#include "menu.h"

#include <cmath>
#include <random>

#define BALL_SIZE 20.0f
#define BALL_SPEED 7.0f
#define BAR_SPEED 3.0f
#define BAR_WIDTH 20.0f
#define BAR_HEIGHT 100.0f

Game::Game(struct settings* sett) : sett(sett){
    gameOver = false;
    pause = true;
    intro = true;
    direction = true;
    offset = 0.5;
    winner = 0;
    player1.score = 0;
    player2.score = 0;
}


void Game::initialize() {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);
    Image icon = LoadImage("../image.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    initGame();
}

void Game::initGame() {
    pause = true;

    ball.radius = BALL_SIZE / 2;
    ball.color = DARKPURPLE;

    bar1.color = BLUE;
    bar2.color = RED;

    setPosition();
}

double GenerateRandomNumber(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

Vector2 GenerateRandomStartSpeed() {
    double angle = GenerateRandomNumber(-M_PI_4, M_PI_4);
    if (rand() % 2 == 0) angle += M_PI;

    return (Vector2){(float)cos(angle), (float)sin(angle)};
}

void Game::setPosition() {
    pause = true;
    ball.position = (Vector2){(float)screenWidth / 2, (float)screenHeight / 2};
    ball.speed = (Vector2){GenerateRandomStartSpeed().x * BALL_SPEED,
                           GenerateRandomStartSpeed().y * BALL_SPEED};
    if (ball.speed.x > 0) direction = false;
    bar1.rect = (Rectangle){10, (float)screenHeight / 2 - BAR_HEIGHT / 2,
                            BAR_WIDTH, BAR_HEIGHT};
    bar2.rect = (Rectangle){(float)screenWidth - BAR_WIDTH - 10,
                            (float)screenHeight / 2 - BAR_HEIGHT / 2, BAR_WIDTH,
                            BAR_HEIGHT};
}

void Game::updateDrawFrame() {
    updateGame();
    drawGame();
}

void Game::checkCollision(int player) {
    Bar bar = player % 2 == 0 ? bar2 : bar1;
    if (CheckCollisionCircleRec(ball.position, ball.radius, bar.rect)) {
        float hitPos = (ball.position.y - bar.rect.y) / BAR_HEIGHT - 0.5f;
        float angle = hitPos * M_PI_4;
        ball.speed.x = BALL_SPEED * cos(angle);
        ball.speed.y = BALL_SPEED * sin(angle);
        if (pow(-1, player)*ball.speed.x > 0) ball.speed.x *= -1;
        if (player == 2) direction = true;
        ball.speed.x *= 1.1f;
        ball.speed.y *= 1.1f;
        if (sett->changingBars && bar1.rect.height > 20) {
            float size = bar1.rect.height * 0.05f;
            bar1.rect.height *= 0.95f;
            bar1.rect.y += size / 2;
            bar2.rect.height *= 0.95f;
            bar2.rect.y += size / 2;
        }
    }
}

void Game::updateGame() {
    if (!gameOver) {
        if (sett->gameMode == ONE_PLAYER) {
            if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && bar2.rect.y > 0)
                bar2.rect.y -= BAR_SPEED;
            if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) &&
                bar2.rect.y + bar2.rect.height < screenHeight)
                bar2.rect.y += BAR_SPEED;
            if (direction) {
                offset = GenerateRandomNumber(0, 1);
                direction = !direction;
            }
            if (ball.speed.x < 0 && !pause) {
                if (bar1.rect.y + bar1.rect.height < screenHeight &&
                    ball.position.y > bar1.rect.y + bar1.rect.height * offset)
                    bar1.rect.y += BAR_SPEED;
                if (bar1.rect.y > 0 &&
                    ball.position.y < bar1.rect.y + bar1.rect.height * offset)
                    bar1.rect.y -= BAR_SPEED;
            } else {
                if (bar1.rect.y + bar1.rect.height / 2 < (float)screenHeight / 2)
                    bar1.rect.y += BAR_SPEED;
                if (bar1.rect.y + bar1.rect.height / 2 > (float)screenHeight / 2)
                    bar1.rect.y -= BAR_SPEED;
            }
        } else {
            if (IsKeyDown(KEY_W) && bar1.rect.y > 0) bar1.rect.y -= BAR_SPEED;
            if (IsKeyDown(KEY_S) && bar1.rect.y + bar1.rect.height < screenHeight)
                bar1.rect.y += BAR_SPEED;

            if (IsKeyDown(KEY_UP) && bar2.rect.y > 0) bar2.rect.y -= BAR_SPEED;
            if (IsKeyDown(KEY_DOWN) && bar2.rect.y + bar2.rect.height < screenHeight)
                bar2.rect.y += BAR_SPEED;
        }

        if (IsKeyPressed(KEY_SPACE) && pause) {
            if (intro) intro = !intro;
            pause = !pause;
        }

        if (!pause) {
            ball.position.x += ball.speed.x;
            ball.position.y += ball.speed.y;

            if (ball.position.y >= screenHeight - ball.radius ||
                ball.position.y <= ball.radius)
                ball.speed.y *= -1;

            checkCollision(1);
            checkCollision(2);

            if (ball.position.x >= screenWidth) {
                player1.score++;
                if (!sett->score && player1.score >= sett->maxScore) {
                    gameOver = true;
                    winner = 1;
                }
                setPosition();
            }
            if (ball.position.x <= 0) {
                player2.score++;
                if (!sett->score && player2.score >= sett->maxScore) {
                    gameOver = true;
                    winner = 2;
                }
                setPosition();
            }
        }
    }
}

void Game::drawGame() const {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){173, 216, 230, 255});
    DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight,
                  (Color){255, 192, 203, 255});
    DrawRectangle(screenWidth / 2 - 2, 0, 4, screenHeight, RAYWHITE);
    if (!gameOver) {
        DrawCircleV(ball.position, ball.radius, ball.color);
        DrawRectangleRounded(bar1.rect, 2, 10, bar1.color);
        DrawRectangleRounded(bar2.rect, 2, 10, bar2.color);
        int score1Width = MeasureText(TextFormat("%i", player1.score), 40);
        DrawText(TextFormat("%i", player1.score),
                 screenWidth / 2 - score1Width - 30, 20, 40, DARKGRAY);
        DrawText(TextFormat("%i", player2.score), screenWidth / 2 + 30, 20, 40,
                 DARKGRAY);

        if (intro) {
            DrawText("PRESS Space TO START",
                     screenWidth / 2 - MeasureText("PRESS Space TO START", 20) / 2,
                     screenHeight / 2 + 20, 20, DARKGRAY);
            DrawText("OR ESC TO EXIT",
                     screenWidth / 2 - MeasureText("OR ESC TO EXIT", 20) / 2,
                     screenHeight / 2 + 40, 20, DARKGRAY);
        }
    } else {
        DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2,
                 screenHeight / 2 - 80, 40, DARKGRAY);
        DrawText(TextFormat("Player %i wins", winner),
                 screenWidth / 2 -
                 MeasureText(TextFormat("Player %i wins", winner), 20) / 2,
                 screenHeight / 2 - 40, 20, DARKGRAY);
        DrawText(
                "PRESS Space TO RETURN TO MENU",
                screenWidth / 2 - MeasureText("PRESS Space TO RETURN TO MENU", 20) / 2,
                screenHeight / 2, 20, DARKGRAY);
        DrawText("Enter TO RESTART",
                 screenWidth / 2 - MeasureText("Enter TO RESTART", 20) / 2,
                 screenHeight / 2 + 20, 20, DARKGRAY);
        DrawText("OR ESC TO EXIT",
                 screenWidth / 2 - MeasureText("OR ESC TO EXIT", 20) / 2,
                 screenHeight / 2 + 40, 20, DARKGRAY);
    }
    EndDrawing();
}

void Game::restart() {
    gameOver = false;
    pause = true;
    intro = true;
    player1.score = 0;
    player2.score = 0;
    setPosition();
}