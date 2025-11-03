#include "tests.h"

TEST(UserInput, Prev) {
  s21::SnakeGameModel model;
  EXPECT_EQ(model.updateCurrentState().pause, INFO_NOT_START);
}

TEST(UserInput, Start) {
  s21::SnakeGameModel model;
  model.userInput(Start, false);
  EXPECT_EQ(model.updateCurrentState().pause, INFO_START);
}

TEST(UserInput, Terminate) {
  s21::SnakeGameModel model;
  model.userInput(Terminate, false);
  EXPECT_EQ(model.updateCurrentState().pause, INFO_FINISH);
}

TEST(UserInput, Action) {
  s21::SnakeGameModel model;
  model.userInput(Start, false);
  model.userInput(Action, true);

  GameInfo_t info = model.updateCurrentState();

  uint8_t start_y = 10, end_y = 13;
  for (uint8_t i = start_y; i <= end_y; ++i) {
    EXPECT_EQ(info.field[i][WIDTH / 2], CELL_SNAKE);
  }
}
