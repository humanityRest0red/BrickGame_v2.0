/**
 * @file controller.h
 * @author kaseltzt
 * @date 2025-09-27
 * @brief Class declaration for the snake game controller.
 */

#ifndef CPP3_BRICKGAME_V2_0_CONTROLLER_H_
#define CPP3_BRICKGAME_V2_0_CONTROLLER_H_

#include "model.h"

namespace s21 {

class SnakeGameController {
 public:
  explicit SnakeGameController(SnakeGameModel& model) : model_(model) {}
  void userInput(UserAction_t action, bool hold) {
    model_.userInput(action, hold);
  }
  GameInfo_t updateCurrentState() { return model_.updateCurrentState(); }

 private:
  SnakeGameModel& model_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_CONTROLLER_H_
