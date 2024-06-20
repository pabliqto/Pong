#ifndef PONG_MENU_H
#define PONG_MENU_H

#include "enums.h"
#include "game.h"


static const int screenWidth = 1000;
static const int screenHeight = 500;


class Menu{
public:
    Menu();
    void drawMenu();
    void drawSettings();
    void drawInfo();
    [[nodiscard]] MenuState getMenuState() const { return settings.menuState; };
    void setMenuState(MenuState state) { settings.menuState = state; };
    settings* getSettings() { return &settings; };

private:
    settings settings;
    Rectangle onePlayer;
    Rectangle twoPlayer;
    Rectangle info;
    Rectangle checkBox;
    Rectangle checkBox2;
    Rectangle spinBox;
    Rectangle playButton;
    Rectangle backButton;
    Rectangle backButton2;
};

#endif // PONG_MENU_H