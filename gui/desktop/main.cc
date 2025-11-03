#include <QApplication>
#include <QColor>
#include <QFont>
#include <QPalette>

#include "game_field.h"
#include "main_window.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QFont globalFont("Verdana", 50);
  QApplication::setFont(globalFont);

  s21::MainWindow window;
  window.setWindowTitle("Brick Game v2.0.");
  QPalette palette = window.palette();

  palette.setColor(QPalette::Window, Qt::black);
  window.setAutoFillBackground(true);
  window.setPalette(palette);

  window.show();

  return app.exec();
}