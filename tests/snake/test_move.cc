#include "tests.h"

#define START_Y 9
#define END_Y START_Y + START_SNAKE_LEN - 1

// ========================================================
// MoveDown
TEST(MoveDown, Common) {
  s21::SnakeGameModel model;
  model.Start();
  GameInfo_t info = model.updateCurrentState();

  uint8_t start = START_Y;
  uint8_t end = END_Y;
  EXPECT_NE(info.field[start - 1][WIDTH / 2], CELL_SNAKE);
  for (uint8_t i = start; i <= end; ++i) {
    EXPECT_EQ(info.field[i][WIDTH / 2], CELL_SNAKE);
  }
  EXPECT_NE(info.field[end + 1][WIDTH / 2], CELL_SNAKE);

  model.MoveDown();
  info = model.updateCurrentState();
  ++start, ++end;

  EXPECT_NE(info.field[start - 1][WIDTH / 2], CELL_SNAKE);
  for (uint8_t i = start; i <= end; ++i) {
    EXPECT_EQ(info.field[i][WIDTH / 2], CELL_SNAKE);
  }
  EXPECT_NE(info.field[end + 1][WIDTH / 2], CELL_SNAKE);
}

TEST(MoveDown, Border) {
  s21::SnakeGameModel model;
  model.Start();
  for (uint8_t i = 0; i < HEIGHT - END_Y - 7; ++i) {
    model.MoveDown();
  }
  EXPECT_NE(model.updateCurrentState().pause, INFO_FINISH);

  model.MoveDown();
  EXPECT_EQ(model.updateCurrentState().pause, INFO_FINISH);
}

// ========================================================
// MoveLeft
TEST(MoveLeft, Common) {
  s21::SnakeGameModel model;
  model.Start();
  model.MoveLeft();
  GameInfo_t info = model.updateCurrentState();

  uint8_t start = START_Y + 1;
  uint8_t end = END_Y;
  for (uint8_t i = start; i <= end; ++i) {
    EXPECT_EQ(info.field[i][WIDTH / 2], CELL_SNAKE);
  }
  EXPECT_EQ(info.field[end][WIDTH / 2 - 1], CELL_SNAKE);
}

TEST(MoveLeft, border) {
  s21::SnakeGameModel model;
  model.Start();
  for (uint8_t i = 0; i < WIDTH / 2; ++i) {
    model.MoveLeft();
  }
  EXPECT_NE(model.updateCurrentState().pause, INFO_FINISH);

  model.MoveLeft();
  EXPECT_EQ(model.updateCurrentState().pause, INFO_FINISH);
}

// ========================================================
// MoveRight
TEST(MoveRight, Common) {
  s21::SnakeGameModel model;
  model.Start();
  model.MoveRight();
  GameInfo_t info = model.updateCurrentState();

  uint8_t start = START_Y + 1;
  uint8_t end = END_Y;
  for (uint8_t i = start; i <= end; ++i) {
    EXPECT_EQ(info.field[i][WIDTH / 2], CELL_SNAKE);
  }
  EXPECT_EQ(info.field[end][WIDTH / 2 + 1], CELL_SNAKE);
}

TEST(MoveRight, border) {
  s21::SnakeGameModel model;
  model.Start();
  for (uint8_t i = 0; i < WIDTH / 2 - 1; ++i) {
    model.MoveRight();
  }
  EXPECT_NE(model.updateCurrentState().pause, INFO_FINISH);

  model.MoveRight();
  EXPECT_EQ(model.updateCurrentState().pause, INFO_FINISH);
}

// ========================================================
// MoveUp
TEST(MoveUp, Common) {
  s21::SnakeGameModel model;
  model.Start();
  model.MoveRight();
  model.MoveUp();
  GameInfo_t info = model.updateCurrentState();

  uint8_t start = START_Y + 2;
  uint8_t end = END_Y;
  for (uint8_t i = start; i <= end; ++i) {
    EXPECT_EQ(info.field[i][WIDTH / 2], CELL_SNAKE);
    EXPECT_EQ(info.field[i][WIDTH / 2 + 1], CELL_SNAKE);
  }
  /*
  []^
  [][]
  */
}

TEST(MoveUp, Opposite) {
  s21::SnakeGameModel model;
  model.Start();
  model.MoveUp();

  uint8_t start = START_Y + 1;
  uint8_t end = END_Y + 1;
  GameInfo_t info = model.updateCurrentState();

  for (uint8_t i = start; i <= end; ++i) {
    EXPECT_EQ(info.field[i][WIDTH / 2], CELL_SNAKE);
  }
}

TEST(MoveUp, Border) {
  s21::SnakeGameModel model;
  model.Start();
  model.MoveRight();
  model.MoveUp();
}

// void Print(int **field) {
//   for (uint8_t i = 0; i < HEIGHT; ++i) {
//     for (uint8_t j = 0; j < WIDTH; ++j) {
//       printf("%d", field[i][j]);
//     }
//     printf("\n");
//   }
//   printf("\n");
// }