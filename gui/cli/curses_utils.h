/**
 * @file curses_utils.h
 * @author kaseltzt
 * @date 2024-04-27
 * @brief Declaration of functions for ncurses tetris view
 */

#ifndef CPP3_BRICKGAME_V2_0_GUI_CLI_CURSES_UTILS_H_
#define CPP3_BRICKGAME_V2_0_GUI_CLI_CURSES_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ncurses.h>
#include <stdint.h>

#include "common.h"

#define DRAW_ON_BOARD(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#define ESCAPE_KEY 27  // esc
#define ENTER_KEY 10   // enter
#define PAUSE_KEY 112  // P
#define ACTION_KEY 32  // space

#define INTRO_MESSAGE "Press ENTER to start"
#define INTRO_MESSAGE_LEN 21

#define BOARDS_BEGIN 2

#define BOARD_N HEIGHT
#define BOARD_M 2 * WIDTH

#define HUD_WIDTH 16

#define Y_NEXT 2
#define Y_SCORE (Y_NEXT + 5 + 2)
#define Y_HIGH_SCORE (Y_SCORE + 5)
#define Y_LEVEL (Y_HIGH_SCORE + 5)

#define X_INSTRUCTIONS (BOARD_N * 2 + 2)

/**
 * @brief ncurses initialization
 *
 * Init ncurses settings
 */
void WinInit();

/**
 * @brief Get user action
 *
 * Get user action enum value depending on pressed button
 * @param user_input Pressed key button
 * @param default_action Default action for each brick game
 */
UserAction_t GetAction(int user_input, UserAction_t default_action);

/**
 * @brief Draw GUI
 *
 * Draw static part of GUI
 */
void DrawGUI(Game_t game);

/**
 * @brief Draw rectangle
 *
 * Draw rectangle
 *
 * @param top_y Top y value
 * @param bottom_y Bottom y value
 * @param left_x Left x value
 * @param right_x Right x value
 */
void DrawRectangle(int top_y, int bottom_y, int left_x, int right_x);

/**
 * @brief Draw game info
 *
 * Draw next figure, score, high score, level, speed
 *
 * @param info Game logic data struct
 */
void DrawInfo(GameInfo_t *info);

/**
 * @brief Draw game field
 *
 * Draw game field
 * @param field 2D array of cells values
 */
void DrawField(int **field);

/**
 * @brief Draw cell
 *
 * Draw cell
 * @param i Vertical coord value
 * @param j Horizontal coord value
 * @param color Color of cell
 */
void DrawEntityCell(uint8_t i, uint8_t j, int8_t color);

/**
 * @brief Draw pause info
 *
 * Draw pause info
 */
void DrawPause();

/**
 * @brief Draw game over info
 *
 * Draw game over info
 */
void DrawGameOver();

#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICKGAME_V2_0_GUI_CLI_CURSES_UTILS_H_
