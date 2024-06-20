#ifndef PONG_SPRITES_H
#define PONG_SPRITES_H
#include <raylib.h>

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


#endif //PONG_SPRITES_H
