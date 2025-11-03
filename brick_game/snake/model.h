/**
 * @file model.h
 * @author kaseltzt
 * @date 2025-09-27
 * @brief Class declaration for the snake game model.
 */

#ifndef CPP3_BRICKGAME_V2_0_MODEL_H_
#define CPP3_BRICKGAME_V2_0_MODEL_H_

#include <cstdint>
#include <deque>

#include "common.h"

#define START_SNAKE_LEN 4
#define MAX_SCORE WIDTH* HEIGHT - START_SNAKE_LEN

#define CELL_SNAKE 5
#define CELL_FRUIT 7

namespace s21 {

class SnakeGameModel;
using Coord_t = int8_t;

struct Point {
  Coord_t x = 0, y = 0;

  Point(Coord_t x, Coord_t y) : x(x), y(y) {}

  bool operator==(const Point& other) const {
    return this->x == other.x && this->y == other.y;
  }
};

enum class Direction { UP, DOWN, LEFT, RIGHT };

using Snake = std::deque<Point>;

class SnakeGameModel {
 public:
  SnakeGameModel();
  SnakeGameModel(Coord_t board_width, Coord_t board_height);
  ~SnakeGameModel();

  void userInput(UserAction_t action, bool hold);
  GameInfo_t updateCurrentState();

  void Start();
  void Spawn();
  void MoveLeft();
  void MoveRight();
  void MoveUp();
  void MoveDown();
  void Shift();
  void Terminate();
  void Pause();

  bool IsAttach() const;
  bool IsCollide() const;
  bool IsCollideWithOwnBody() const;
  bool IsCollideWithWall() const;

 private:
  using SnakeActionT = void (SnakeGameModel::*)();
  const SnakeActionT fsmTable[4][8] = {
      {&SnakeGameModel::Start, nullptr, &SnakeGameModel::Terminate, nullptr,
       nullptr, nullptr, nullptr, nullptr},
      {&SnakeGameModel::Shift, &SnakeGameModel::Pause,
       &SnakeGameModel::Terminate, &SnakeGameModel::MoveLeft,
       &SnakeGameModel::MoveRight, &SnakeGameModel::MoveUp,
       &SnakeGameModel::MoveDown, &SnakeGameModel::Shift},
      {
          nullptr,
          &SnakeGameModel::Pause,
          &SnakeGameModel::Terminate,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
      },
      {
          nullptr,
          nullptr,
          &SnakeGameModel::Terminate,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
      },
  };
  const Coord_t board_width_;
  const Coord_t board_height_;

  Snake snake_;
  Direction direction_ = Direction::DOWN;
  Point fruit_{0, 0};
  GameInfo_t info_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_MODEL_H_