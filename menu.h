#ifndef PONG_MENU_H
#define PONG_MENU_H

enum GameMode {
    ONE_PLAYER,
    TWO_PLAYER
};

enum MenuState {
    START,
    SETTINGS,
    INFO,
    PLAY
};

static const int screenWidth = 1000;
static const int screenHeight = 500;

static bool changingBars = false;
static GameMode gameMode = ONE_PLAYER;
static bool score = true;
static int maxScore = 5;

void drawMenu(MenuState *menuState);
void drawSettings(MenuState *menuState);
void drawInfo(MenuState *menuState);

#endif // PONG_MENU_H