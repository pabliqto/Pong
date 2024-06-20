#ifndef PONG_ENUMS_H
#define PONG_ENUMS_H
enum MenuState {
    START,
    SETTINGS,
    INFO,
    PLAY
};

enum GameMode {
    ONE_PLAYER,
    TWO_PLAYER
};

struct settings {
    MenuState menuState = START;
    int maxScore = 5;
    bool changingBars = false;
    bool score = true;
    GameMode gameMode = ONE_PLAYER;
};

#endif //PONG_ENUMS_H
