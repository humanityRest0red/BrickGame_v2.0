/**
 * @file game_field.h
 * @author kaseltzt
 * @date 2025-10-10
 * @brief Declaration of the desktop field brickgame view.
 */

#ifndef CPP3_BRICKGAME_V2_0_GUI_DESKTOP_GAME_FIELD_H_
#define CPP3_BRICKGAME_V2_0_GUI_DESKTOP_GAME_FIELD_H_

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "controller.h"
#include "tetris.h"

#define TILE 50

namespace s21 {

class GameField : public QWidget {
  Q_OBJECT

 public:
  GameField(Game_t game, QWidget *parent = nullptr);
  ~GameField();

  void UpdateTetris();
  void UpdateSnake();

  GameInfo_t updateCurrentState() { return controller_.updateCurrentState(); }

  void DrawGUI(QPainter &painter);
  void DrawInfo(QPainter &painter);
  void DrawField(QPainter &painter);
  void DrawTetromino(QPainter &painter);
  void DrawNextTetromino(QPainter &painter);
  void DrawS21Logo(QPainter &painter);

  void DrawGameOver();

  QBrush GetColor(int8_t cell);

 protected:
  void paintEvent(QPaintEvent *e);
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 private:
  SnakeGameModel model_;
  SnakeGameController controller_;
  GameParams_t tetris_prms_;

  Game_t game_;
  GameInfo_t info_;
  UserAction_t action_ = Action;
  bool key_pressed = false;
  QTimer *timer_;
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_GUI_DESKTOP_GAME_FIELD_H_
