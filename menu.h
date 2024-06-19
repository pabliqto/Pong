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

void drawMenu(MenuState *menuState, GameMode *gameMode);
void drawSettings(MenuState *menuState, const GameMode *gameMode, int *maxScore, bool *changingBars, bool *score);
void drawInfo(MenuState *menuState);

#endif // PONG_MENU_H