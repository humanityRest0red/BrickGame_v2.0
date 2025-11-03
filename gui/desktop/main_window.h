/**
 * @file main_window.h
 * @author kaseltzt
 * @date 2025-10-10
 * @brief Declaration of the desktop brickgame window.
 */

#ifndef CPP3_BRICKGAME_V2_0_GUI_DESKTOP_MAIN_WINDOW_H_
#define CPP3_BRICKGAME_V2_0_GUI_DESKTOP_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include "game_field.h"

#define BUTTON_HEIGHT 150
#define BUTTON_WIDTH 250

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  QWidget *widget = nullptr;
  QVBoxLayout *layout = nullptr;
  GameField *game_field_ = nullptr;

  QPushButton *btn_tetris_;
  QPushButton *btn_snake_;
  QPushButton *btn_exit_;

  void GameClick(Game_t game);
  void ExitClick();

  void DeleteButtons();
};

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_GUI_DESKTOP_MAIN_WINDOW_H_
