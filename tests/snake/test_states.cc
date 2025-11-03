#include "tests.h"

// ========================================================
// PredStart
TEST(Start, PredStart) {
  s21::SnakeGameModel model;
  EXPECT_EQ(model.updateCurrentState().pause, INFO_NOT_START);
}

// ========================================================
// Start
TEST(Start, Start) {
  s21::SnakeGameModel model;
  EXPECT_EQ(model.updateCurrentState().pause, INFO_NOT_START);
  model.Start();
  EXPECT_EQ(model.updateCurrentState().pause, INFO_START);
}

// ========================================================
// Pause
TEST(Pause, Pause) {
  s21::SnakeGameModel model;
  model.Start();
  model.Pause();
  EXPECT_EQ(model.updateCurrentState().pause, INFO_PAUSE);
}

TEST(Pause, UnPause) {
  s21::SnakeGameModel model;
  model.Start();
  model.Pause();
  model.Pause();
  EXPECT_NE(model.updateCurrentState().pause, INFO_PAUSE);
}

// ========================================================
// Finish
TEST(Terminate, Terminate) {
  s21::SnakeGameModel model;
  model.Start();
  for (uint8_t i = 0; i < HEIGHT; ++i) {
    model.MoveDown();
  }
  EXPECT_EQ(model.updateCurrentState().pause, INFO_FINISH);
}