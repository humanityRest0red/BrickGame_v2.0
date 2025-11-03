/**
 * @file main_window.cc
 * @author kaseltzt
 * @date 2025-10-10
 * @brief Implementation of the desktop brickgame window.
 */

#include "main_window.h"

#include <functional>

s21::MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  widget = new QWidget(this);
  setCentralWidget(widget);
  layout = new QVBoxLayout(widget);

  btn_tetris_ = new QPushButton("Tetris", widget);
  btn_snake_ = new QPushButton("Snake", widget);
  btn_exit_ = new QPushButton("Exit", widget);

  btn_tetris_->setGeometry(300, 130, BUTTON_WIDTH, BUTTON_HEIGHT);
  btn_snake_->setGeometry(300, 430, BUTTON_WIDTH, BUTTON_HEIGHT);
  btn_exit_->setGeometry(300, 730, BUTTON_WIDTH, BUTTON_HEIGHT);

  btn_tetris_->setPalette(Qt::green);

  connect(btn_tetris_, &QPushButton::clicked, this,
          std::bind(&MainWindow::GameClick, this, Game_t::TETRIS));
  connect(btn_snake_, &QPushButton::clicked, this,
          std::bind(&MainWindow::GameClick, this, Game_t::SNAKE));
  connect(btn_exit_, &QPushButton::clicked, this, &MainWindow::ExitClick);

  setFixedSize((WIDTH + 6 + 1) * TILE, (HEIGHT + 1) * TILE);
}

s21::MainWindow::~MainWindow() {}

void s21::MainWindow::GameClick(Game_t game) {
  DeleteButtons();
  game_field_ = new GameField(game);
  game_field_->setFocusPolicy(Qt::StrongFocus);
  layout->addWidget(game_field_);
  game_field_->setFocus();
}

void s21::MainWindow::ExitClick() { close(); }

void s21::MainWindow::DeleteButtons() {
  delete btn_tetris_;
  delete btn_snake_;
  delete btn_exit_;
}