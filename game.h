#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <raylib.h>
#include "sprites.h"
#include "menu.h"


class Game {
public:
    explicit Game(struct settings* settings);

    void initialize();
    void updateDrawFrame();
    [[nodiscard]] bool getGameOver() const { return gameOver; };
    void setGameOver(bool status) { Game::gameOver = status; };
    void restart();
private:
    void initGame();
    void setPosition();
    void updateGame();
    void drawGame() const;
    void checkCollision(int player);

    bool gameOver;
    bool pause;
    bool intro;
    bool direction;
    double offset;
    int winner;
    Ball ball;
    Bar bar1;
    Bar bar2;
    Player player1;
    Player player2;
    settings* settings;
};


#endif //PONG_GAME_H
