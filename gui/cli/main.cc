#include <string>

#include "curses_utils.h"
#include "snake_view.h"
#include "tetris_view.h"

int main(void) {
  WinInit();

  std::string games[] = {"Tetris", "Snake", "Exit"};
  int chosen = 0;
  int pressed_key = getch();

  const unsigned y = 10;
  const unsigned x = 10;
  DrawRectangle(0, BOARD_N + 1, 0, BOARD_M + 1);
  while (pressed_key != ENTER_KEY) {
    for (int i = 0; i < 3; ++i) {
      mvprintw(y + i, x - games[i].size() / 2, "    %s    ", games[i].c_str());
    }
    attron(COLOR_PAIR(5));
    mvprintw(y + chosen, x - games[chosen].size() / 2, "<<< %s >>>",
             games[chosen].c_str());
    attroff(COLOR_PAIR(5));

    if (pressed_key == KEY_UP) {
      chosen = (chosen + 2) % 3;
    } else if (pressed_key == KEY_DOWN) {
      chosen = (chosen + 1) % 3;
    }
    pressed_key = getch();
    refresh();
  }

  if (chosen == 1) {
    s21::SnakeGameModel model;
    s21::SnakeGameController controller(model);
    s21::SnakeGameView view(controller);
    view.GameLoop();
  } else if (chosen == 0) {
    GameLoop();
  }

  if (chosen == 0 || chosen == 1) {
    while (getch() != ENTER_KEY) {
    }
  }
  erase();
  endwin();
}