/**
 * @file snake_view.cc
 * @author kaseltzt
 * @date 2025-09-27
 * @brief Implementation of functions for ncurses snake view
 */

#include "snake_view.h"

#include <ctime>

#include "curses_utils.h"

s21::SnakeGameView::SnakeGameView(SnakeGameController &controller)
    : controller_(controller) {}

void s21::SnakeGameView::GameLoop() {
  UserAction_t action = Action;
  erase();
  DrawGUI(Game_t::SNAKE);
  while (action != Start) {
    action = GetAction(getch(), Action);
  }
  controller_.userInput(action, false);

  GameInfo_t info = updateCurrentState();
  for (long start = clock(); info.pause != INFO_FINISH;) {
    if (clock() - start > 1500000 / ((long unsigned)info.speed + 15)) {
      DrawSnake(info);
      bool hold = false;
      action = GetAction(getch(), Action);
      controller_.userInput(action, hold);
      info = updateCurrentState();
      start = clock();
    }
  }
  clear();
  DrawGameOver();
  refresh();
}

void s21::SnakeGameView::DrawSnake(GameInfo_t &info) {
  erase();
  DrawGUI(Game_t::SNAKE);
  DrawInfo(&info);
  DrawField(info.field);
  if (info.pause == INFO_PAUSE) {
    DrawPause();
  }
}