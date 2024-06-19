#include <raylib.h>
#include "menu.h"

#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 450

static bool changingBars = false;

void DrawX(Rectangle rect, Color color) {
    DrawLineEx((Vector2){rect.x + 5, rect.y + 5}, (Vector2){rect.x + rect.width - 5, rect.y + rect.height - 5}, 5.0f, color);
    DrawLineEx((Vector2){rect.x + rect.width - 5, rect.y + 5}, (Vector2){rect.x + 5, rect.y + rect.height - 5}, 5.0f, color);
}

int menu() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);
    Image icon = LoadImage("../image.png");
    SetWindowIcon(icon);

    Rectangle onePlayer = {(float)SCREEN_WIDTH/2 - 100, 100, 200, 50};
    Rectangle twoPlayer = {(float)SCREEN_WIDTH/2 - 100, 170, 200, 50};
    Rectangle fullBox = {(float)SCREEN_WIDTH/2 - 100, 240, 150, 50};
    Rectangle checkBox = {(float)SCREEN_WIDTH/2 - 100, 240, 20, 20};
    Rectangle info = {(float)SCREEN_WIDTH/2 - 100, 310, 200, 50};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Pong", SCREEN_WIDTH/2 - MeasureText("Pong", 40)/2, 20, 40, GRAY);
        if (CheckCollisionPointRec(GetMousePosition(), onePlayer)) {
            DrawRectangleRec(onePlayer, DARKGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 1;
            }
        } else {
            DrawRectangleRec(onePlayer, LIGHTGRAY);
        }
        DrawText("One Player", (int)onePlayer.x + 50, (int)onePlayer.y + 15, 20, GRAY);
        if (CheckCollisionPointRec(GetMousePosition(), twoPlayer)) {
            DrawRectangleRec(twoPlayer, DARKGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 2;
            }
        } else {
            DrawRectangleRec(twoPlayer, LIGHTGRAY);
        }
        DrawText("Two Player", (int)twoPlayer.x + 50, (int)twoPlayer.y + 15, 20, GRAY);
        DrawRectangleRec(fullBox, LIGHTGRAY);
        DrawText("Descending\nPaddles", (int)fullBox.x + 10, (int)fullBox.y + 10, 20, GRAY);
        if (changingBars) {
            DrawX(checkBox, RED);
        } else {
            DrawRectangleRec(checkBox, LIGHTGRAY);
        }

        EndDrawing();
    }


    CloseWindow();
    return 0;
}