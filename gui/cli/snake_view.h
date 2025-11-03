/**
 * @file snake_view.h
 * @author kaseltzt
 * @date 2025-09-27
 * @brief Declaration of functions for ncurses snake view
 */

#ifndef CPP3_BRICKGAME_V2_0_GUI_CLI_SNAKE_VIEW_H_
#define CPP3_BRICKGAME_V2_0_GUI_CLI_SNAKE_VIEW_H_

#include "controller.h"

namespace s21 {

class SnakeGameView {
 public:
  explicit SnakeGameView(SnakeGameController &controller);

  void userInput(UserAction_t action, bool hold) {
    controller_.userInput(action, hold);
  }
  GameInfo_t updateCurrentState() { return controller_.updateCurrentState(); }
  void GameLoop();
  void DrawSnake(GameInfo_t &info);

 private:
  SnakeGameController &controller_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_GUI_CLI_SNAKE_VIEW_H_
