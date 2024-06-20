#include <raylib.h>

#include "menu.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Menu::Menu() {
    onePlayer = {(float) screenWidth / 2 - 100, 120, 200, 50};
    twoPlayer = {(float) screenWidth / 2 - 100, 200, 200, 50};
    info = {(float) screenWidth / 2 - 100, 300, 200, 50};

    checkBox = {(float) screenWidth / 2 - 110, 160, 20, 20};
    checkBox2 = {(float) screenWidth / 2 - 100, 200, 20, 20};
    spinBox = {(float) screenWidth / 2 - 100, 270, 200, 50};
    playButton = {(float) screenWidth / 2 - 100, 340, 200, 50};
    backButton = {(float) screenWidth / 2 - 100, 410, 200, 50};

    backButton2 = {(float) screenWidth / 2 - 100, 390, 200, 50};
}

void Menu::drawMenu() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("PONG", screenWidth / 2 - MeasureText("PONG", 40) / 2, 50, 40,
             BLACK);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    if (GuiButton(onePlayer, "One Player")) {
        sett.gameMode = ONE_PLAYER;
        sett.menuState = SETTINGS;
    }
    if (GuiButton(twoPlayer, "Two Player")) {
        sett.gameMode = TWO_PLAYER;
        sett.menuState = SETTINGS;
    }

    if (GuiButton(info, "Info")) {
        sett.menuState = INFO;
    }
    EndDrawing();
}

void Menu::drawSettings() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    DrawText("SETTINGS", screenWidth / 2 - MeasureText("SETTINGS", 40) / 2, 50,
             40, BLACK);
    switch (sett.gameMode) {
        case ONE_PLAYER:
            DrawText("One Player",
                     screenWidth / 2 - MeasureText("One Player", 20) / 2, 100, 20,
                     BLACK);
            break;
        case TWO_PLAYER:
            DrawText("Two Player",
                     screenWidth / 2 - MeasureText("Two Player", 20) / 2, 100, 20,
                     BLACK);
            break;
    }
    if (GuiCheckBox(checkBox, "Changing Bars", &sett.changingBars)) {
        sett.changingBars = !sett.changingBars;
    }
    if (GuiCheckBox(checkBox2, "Endless Game", &sett.score)) {
        sett.score = !sett.score;
    }
    if (!sett.score) {
        DrawText("Max Score", screenWidth / 2 - MeasureText("Max Score", 30) / 2,
                 240, 30, DARKGRAY);
        GuiSpinner(spinBox, nullptr, &sett.maxScore, 1, 100, false);
    }
    if (GuiButton(playButton, "Play")) {
        sett.menuState = PLAY;
    }
    if (GuiButton(backButton, "Back")) {
        sett.menuState = START;
    }
    EndDrawing();
}

void Menu::drawInfo() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("INFO", screenWidth / 2 - MeasureText("INFO", 40) / 2, 50, 40,
             BLACK);
    DrawText("This is a simple Pong game",
             screenWidth / 2 - MeasureText("This is a simple Pong game", 20) / 2,
             100, 20, BLACK);
    DrawText("One Player: Play against the computer",
             screenWidth / 2 -
             MeasureText("One Player: Play against the computer", 20) / 2,
             130, 20, BLACK);
    DrawText("Controls: WS or Arrow Keys",
             screenWidth / 2 - MeasureText("Controls: WS or Arrow Keys", 20) / 2,
             160, 20, BLACK);
    DrawText(
            "Two Player: Player 1 (WS), Player 2 (Arrow Keys)",
            screenWidth / 2 -
            MeasureText("Two Player: Player 1 (WS), Player 2 (Arrow Keys)", 20) /
            2,
            190, 20, BLACK);
    DrawText(
            "Ball speed increases by 10% after each hit",
            screenWidth / 2 -
            MeasureText("Ball speed increases by 10% after each hit", 20) / 2,
            220, 20, BLACK);
    DrawText("Game never ends or set a max score to win",
             screenWidth / 2 -
             MeasureText("Game never ends or set a max score to win", 20) / 2,
             250, 20, BLACK);
    DrawText(
            "Optional: Paddles shrink by 5% after each hit",
            screenWidth / 2 -
            MeasureText("Optional: Paddles shrink by 5% after each hit", 20) / 2,
            280, 20, BLACK);
    if (GuiButton(backButton2, "Back")) {
        sett.menuState = START;
    }
    EndDrawing();
}