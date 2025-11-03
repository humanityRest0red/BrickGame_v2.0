/**
 * @file model.cc
 * @author kaseltzt
 * @date 2025-09-27
 * @brief Implementation of the snake game model class.
 */

#include "model.h"

#include <algorithm>
#include <ctime>
#include <random>

#define SNAKE_HIGH_SCORE_FILE_NAME "./brick_game/snake/high_score.txt"

namespace s21 {

SnakeGameModel::SnakeGameModel() : SnakeGameModel(WIDTH, HEIGHT) {}

SnakeGameModel::SnakeGameModel(Coord_t board_width, Coord_t board_height)
    : board_width_(board_width), board_height_(board_height) {
  info_ = InitInfo(SNAKE_HIGH_SCORE_FILE_NAME);
}

SnakeGameModel::~SnakeGameModel() {
  RemoveInfo(&info_, SNAKE_HIGH_SCORE_FILE_NAME);
}

void SnakeGameModel::userInput(UserAction_t action, bool hold) {
  SnakeActionT func = fsmTable[info_.pause][action];
  if (func) {
    if (hold) {
      (this->*func)();
    } else {
      (this->*func)();
    }
  }
}

void SnakeGameModel::Start() {
  info_.pause = INFO_START;
  std::srand(std::time(0));
  for (uint8_t i = 0; i < START_SNAKE_LEN; ++i) {
    snake_.push_front({static_cast<Coord_t>(board_width_ / 2),
                       static_cast<Coord_t>(board_height_ / 2 - 1 + i)});
  }
  Spawn();
}

void SnakeGameModel::Spawn() {
  do {
    fruit_ = Point(std::rand() % board_width_, std::rand() % board_height_);
  } while (std::any_of(snake_.begin(), snake_.end(),
                       [&](const auto& elem) { return elem == fruit_; }));
}

void SnakeGameModel::MoveLeft() {
  if (direction_ != Direction::RIGHT) {
    direction_ = Direction::LEFT;
  }
  Shift();
}

void SnakeGameModel::MoveRight() {
  if (direction_ != Direction::LEFT) {
    direction_ = Direction::RIGHT;
  }
  Shift();
}

void SnakeGameModel::MoveUp() {
  if (direction_ != Direction::DOWN) {
    direction_ = Direction::UP;
  }
  Shift();
}

void SnakeGameModel::MoveDown() {
  if (direction_ != Direction::UP) {
    direction_ = Direction::DOWN;
  }
  Shift();
}

void SnakeGameModel::Shift() {
  Point head = snake_.front();
  switch (direction_) {
    case Direction::UP:
      head.y--;
      break;
    case Direction::DOWN:
      head.y++;
      break;
    case Direction::RIGHT:
      head.x++;
      break;
    case Direction::LEFT:
      head.x--;
      break;
  }

  snake_.push_front(head);

  if (IsCollide()) {
    snake_.pop_front();
    Terminate();
  } else if (IsAttach()) {
    Spawn();
  } else {
    snake_.pop_back();
  }
}

void SnakeGameModel::Terminate() { info_.pause = INFO_FINISH; }

void SnakeGameModel::Pause() {
  info_.pause = info_.pause == INFO_PAUSE ? INFO_START : INFO_PAUSE;
}

bool SnakeGameModel::IsAttach() const { return snake_.front() == fruit_; }

bool SnakeGameModel::IsCollide() const {
  return IsCollideWithWall() || (IsCollideWithOwnBody() && snake_.size() != 4);
}

bool SnakeGameModel::IsCollideWithOwnBody() const {
  const Point& head = snake_.front();
  auto it = std::find(snake_.begin() + 1, snake_.end(), head);
  return it != snake_.end();
}

bool SnakeGameModel::IsCollideWithWall() const {
  const Point& head = snake_.front();
  return head.x < 0 || head.x >= board_width_ || head.y < 0 ||
         head.y >= board_height_;
}

GameInfo_t SnakeGameModel::updateCurrentState() {
  if (info_.pause != INFO_NOT_START) {
    for (Coord_t i = 0; i < board_height_; ++i) {
      for (Coord_t j = 0; j < board_width_; ++j) {
        info_.field[i][j] = 0;
      }
    }
    info_.field[fruit_.y][fruit_.x] = CELL_FRUIT;
    for (const Point& segment : snake_) {
      info_.field[segment.y][segment.x] = CELL_SNAKE;
    }
    info_.score = snake_.size() - 4;
    info_.high_score = std::max(info_.score, info_.high_score);
    info_.level = std::max(std::min(info_.score / 5 + 1, 10), info_.level);
    info_.speed = info_.level;
  }
  return info_;
}

}  // namespace s21
