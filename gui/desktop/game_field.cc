/**
 * @file game_field.cc
 * @author kaseltzt
 * @date 2025-10-10
 * @brief Implementation of the desktop brickgame field view.
 */

#include "game_field.h"

#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QPen>

s21::GameField::GameField(Game_t game, QWidget *parent)
    : QWidget(parent), model_(), controller_(model_), game_(game) {
  timer_ = new QTimer(this);
  timer_->start(500);

  if (game_ == Game_t::TETRIS) {
    InitializeParams(&tetris_prms_);
    UpdateParams(&tetris_prms_);
    info_ = tetris_prms_.info;
    connect(timer_, &QTimer::timeout, this, &GameField::UpdateTetris);
  } else if (game_ == Game_t::SNAKE) {
    info_ = controller_.updateCurrentState();
    connect(timer_, &QTimer::timeout, this, &GameField::UpdateSnake);
  }
}

s21::GameField::~GameField() {}

void s21::GameField::UpdateTetris() {
  if (info_.pause != INFO_FINISH) {
    if (!key_pressed) {
      action_ = Down;
    }
    updateCurrentState();
    userInput(action_, false);
    info_ = tetris_prms_.info;
    timer_->setInterval(300 - info_.speed * 20);
  } else {
    timer_->stop();
    disconnect(timer_, &QTimer::timeout, this, &GameField::UpdateTetris);
  }
  repaint();
  key_pressed = false;
}

void s21::GameField::UpdateSnake() {
  if (info_.pause != INFO_FINISH) {
    if (!key_pressed) {
      action_ = Action;
    }
    controller_.userInput(action_, false);
    info_ = controller_.updateCurrentState();
    timer_->setInterval(300 - info_.speed * 20);
  } else {
    timer_->stop();
    disconnect(timer_, &QTimer::timeout, this, &GameField::UpdateSnake);
  }
  repaint();
  key_pressed = false;
}

void s21::GameField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter painter(this);
  if (info_.pause != INFO_FINISH) {
    DrawGUI(painter);
    DrawField(painter);
    DrawInfo(painter);
    DrawS21Logo(painter);
    if (game_ == Game_t::TETRIS) {
      DrawTetromino(painter);
      DrawNextTetromino(painter);
    }
  } else {
    if (game_ == Game_t::SNAKE && info_.score == MAX_SCORE) {
      painter.setPen(QPen(Qt::green, 0.4));
      painter.drawText(270, 460, "YOU WIN");
    } else {
      painter.setPen(QPen(Qt::red, 0.4));
      painter.drawText(270, 460, "YOU DIED");
    }
  }
}

void s21::GameField::DrawGUI(QPainter &painter) {
  painter.setPen(QPen(Qt::white, 0.2));
  for (Coord_t y = 0; y <= HEIGHT; ++y) {
    painter.drawLine(0, y * TILE, WIDTH * TILE, y * TILE);
  }
  for (Coord_t x = 0; x <= WIDTH; ++x) {
    painter.drawLine(x * TILE, 0, x * TILE, HEIGHT * TILE);
  }
}

void s21::GameField::DrawField(QPainter &painter) {
  painter.setPen(QPen(Qt::black, 0.2));
  for (Coord_t y = 0; y < HEIGHT; ++y) {
    for (Coord_t x = 0; x < WIDTH; ++x) {
      if (info_.field[y][x]) {
        painter.setBrush(GetColor(info_.field[y][x]));
        painter.drawRect(x * TILE, y * TILE, TILE, TILE);
      }
    }
  }
}

void s21::GameField::DrawTetromino(QPainter &painter) {
  painter.setBrush(GetColor(tetris_prms_.tetromino.name + 1));
  for (uint8_t i = 0; i < CELLS_IN_TETROMINO; ++i) {
    painter.drawRect(tetris_prms_.tetromino.cells[i].x * TILE,
                     tetris_prms_.tetromino.cells[i].y * TILE, TILE, TILE);
  }
}

void s21::GameField::DrawNextTetromino(QPainter &painter) {
  painter.setBrush(GetColor(tetris_prms_.tetromino.name_next + 1));
  painter.setPen(QPen(Qt::black, 0.2));
  for (uint8_t y = 0; y < TETROMINO_HEIGHT; ++y) {
    for (uint8_t x = 0; x < TETROMINO_WIDTH; ++x) {
      if (info_.next[y][x]) {
        painter.drawRect((x + WIDTH + 1) * TILE, (y + 1) * TILE, TILE, TILE);
      }
    }
  }
}

void s21::GameField::DrawInfo(QPainter &painter) {
  QFont verdanaFont("Verdana", 15);
  painter.setFont(verdanaFont);
  painter.setPen(QPen(Qt::white, 0.4));

  painter.setBrush(QBrush(Qt::black));
  painter.drawRect(WIDTH * TILE, 0 * TILE, 6 * TILE, HEIGHT * TILE);
  painter.drawText(630, 25, "Next");
  painter.drawLine(WIDTH * TILE, 4 * TILE, (WIDTH + 6) * TILE, 4 * TILE);

  painter.drawText(630, 230, "Score");
  painter.drawText(650, 280, QString::number(info_.score));
  painter.drawLine(WIDTH * TILE, 6 * TILE, (WIDTH + 6) * TILE, 6 * TILE);

  painter.drawText(610, 330, "High Score");
  painter.drawText(650, 380, QString::number(info_.high_score));
  painter.drawLine(WIDTH * TILE, 8 * TILE, (WIDTH + 6) * TILE, 8 * TILE);

  painter.drawText(630, 430, "Level");
  painter.drawText(650, 480, QString::number(info_.level));
  painter.drawLine(WIDTH * TILE, 10 * TILE, (WIDTH + 6) * TILE, 10 * TILE);

  painter.drawText(600, 650, "Enter - Start");
  if (game_ == Game_t::TETRIS) {
    painter.drawText(600, 700, "<   > - Move");
    painter.drawText(600, 715, "   v");
    painter.drawText(600, 750, "Space - Rotate");
  } else {
    painter.drawText(598, 690, "   ^");
    painter.drawText(600, 700, "<   > - Move");
    painter.drawText(600, 715, "   v");
    painter.drawText(600, 750, "Space - Speed Up");
  }
  painter.drawText(600, 800, "P - Pause");
  painter.drawText(600, 850, "Esc - Quite");
}

void s21::GameField::DrawS21Logo(QPainter &painter) {
  painter.setPen(QPen(Qt::white, 0.1));
  painter.setBrush(Qt::green);
  const static unsigned logo[5][7] = {{1, 1, 1, 0, 0, 1, 0},
                                      {0, 0, 0, 1, 0, 0, 1},
                                      {0, 1, 1, 0, 0, 0, 1},
                                      {1, 0, 0, 0, 0, 0, 1},
                                      {0, 1, 1, 1, 0, 0, 1}};
  for (uint8_t y = 0; y < 5; ++y) {
    for (uint8_t x = 0; x < 7; ++x) {
      if (logo[y][x]) {
        painter.drawRect(740 + x * 5, 950 + y * 5, 5, 5);
      }
    }
  }
}

QBrush s21::GameField::GetColor(int8_t cell) {
  static const QBrush array[] = {
      QBrush(Qt::white),           QBrush(Qt::darkCyan), QBrush(Qt::darkBlue),
      QBrush(QColor(255, 165, 0)), QBrush(Qt::yellow),   QBrush(Qt::darkGreen),
      QBrush(Qt::darkMagenta),     QBrush(Qt::darkRed)};
  return array[cell];
}

void s21::GameField::keyPressEvent(QKeyEvent *event) {
  key_pressed = true;
  switch (event->key()) {
    case Qt::Key_Return:
      action_ = Start;
      break;
    case Qt::Key_P:
      action_ = Pause;
      break;
    case Qt::Key_Escape:
      action_ = Terminate;
      break;
    case Qt::Key_Up:
      action_ = Up;
      break;
    case Qt::Key_Right:
      action_ = Right;
      break;
    case Qt::Key_Left:
      action_ = Left;
      break;
    case Qt::Key_Down:
      action_ = Down;
      break;
    case Qt::Key_Space:
      action_ = Action;
      break;
    default:
      key_pressed = false;
      break;
  }
  QWidget::keyPressEvent(event);
}

void s21::GameField::keyReleaseEvent(QKeyEvent *event) {
  // qDebug() << "Отпущена клавиша";
  QWidget::keyReleaseEvent(event);
}
