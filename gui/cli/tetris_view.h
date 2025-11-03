/**
 * @file tetris_view.h
 * @author kaseltzt
 * @date 2024-04-27
 * @brief Declaration of functions for ncurses tetris view
 */

#ifndef BRICK_GAME_GUI_TETRIS_VIEW_H_
#define BRICK_GAME_GUI_TETRIS_VIEW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tetris.h"

void GameLoop();

void DrawTetris(GameParams_t *prms);

void DrawNextTetromino(GameInfo_t *info, int color);

/**
 * @brief Draw figure
 *
 * Draw tetromino
 *
 * @param tetromino Pointer on figure
 */
void DrawTetromino(Tetromino_t *tetromino);

#ifdef __cplusplus
}
#endif

#endif  // BRICK_GAME_GUI_TETRIS_VIEW_H_