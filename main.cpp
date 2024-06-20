#include "enums.h"
#include "game.h"
#include "menu.h"

int main() {
    Menu menu;
    Game game(menu.getSettings());

    game.initialize();

    while (!WindowShouldClose()) {
        switch (menu.getMenuState()) {
            case START:
                menu.drawMenu();
                break;
            case SETTINGS:
                menu.drawSettings();
                break;
            case INFO:
                menu.drawInfo();
                break;
            case PLAY:
                game.updateDrawFrame();
                if (game.getGameOver() && IsKeyPressed(KEY_SPACE)) {
                    menu.setMenuState(START);
                    game.restart();
                }
                if (game.getGameOver() && IsKeyPressed(KEY_ENTER)) {
                    game.restart();
                }
                break;
        }
    }

    CloseWindow();
    return 0;
}