/**
 * @file tetris.h
 * @author kaseltzt
 * @date 2024-04-27
 * @brief Declaration of functions for tetris game
 */

#ifndef BRICK_GAME_TETRIS_TETRIS_H_
#define BRICK_GAME_TETRIS_TETRIS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "common.h"

#define TETRIS_HIGH_SCORE_FILE_NAME "./brick_game/tetris/high_score.txt"

#define CELLS_IN_TETROMINO 4

typedef enum { I = 0, J, L, O, S, T, Z } TetroName_t;

typedef int8_t Coord_t;

/**
 * @brief Cell structure
 *
 * Cell structure with params x, y
 */
typedef struct {
  Coord_t x;
  Coord_t y;
} Cell_t;

/**
 * @brief Figure structure
 *
 * Tetromino structure
 */
typedef struct {
  Cell_t cells[CELLS_IN_TETROMINO];
  TetroName_t name;
  TetroName_t name_next;
} Tetromino_t;

/**
 * @brief Game parameters struct
 *
 * Structure with all game parametres
 */
typedef struct {
  GameInfo_t info;
  Tetromino_t tetromino;
} GameParams_t;

typedef void (*ActionT)(GameParams_t *prms);

/**
 * @brief Change game state depending on user input
 *
 * Change game state depending on user input using FSM
 *
 * @param action Action type value
 * @param hold Bool value of was key hold
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Update current game state
 *
 * Update game state to SHIFTING
 *
 * @param prms Pointer to GameParams_t struct
 */
GameInfo_t updateCurrentState();

/**
 * @brief Update game parameters
 *
 * Update game parameters in static variable.
 *
 * @param prms Pointer to GameParams_t struct
 *
 * @return Pointer to GameParams_t struct
 */
GameParams_t *UpdateParams(GameParams_t *prms);

/**
 * @brief Initialize game parameters
 *
 * Allocate memory for field, set score, high_score, level, speed, pause flag
 *
 * @param prms Pointer to GameParams_t struct
 */
void InitializeParams(GameParams_t *prms);

/**
 * @brief Start game
 *
 * Set game state SPAWN
 *
 * @param prms Pointer to GameParams_t struct
 */
void StartGame(GameParams_t *prms);

/**
 * @brief Pause game
 *
 * Set pause status to the opposite
 *
 * @param prms Pointer to GameParams_t struct
 */
void PauseGame(GameParams_t *prms);

/**
 * @brief Terminate game
 *
 * Free allocated memory, set game state GAMEOVER
 *
 * @param prms Pointer to GameParams_t struct
 */
void TerminateGame(GameParams_t *prms);

/**
 * @brief Spawn new figure
 *
 * Spawn a figure, defined in 'next'
 *
 * @param prms Pointer to GameParams_t struct
 */
void Spawn(GameParams_t *prms);

/**
 * @brief Move figure down
 *
 * Move figure down by one cell
 *
 * @param prms Pointer to GameParams_t struct
 */
void MoveDown(GameParams_t *prms);

/**
 * @brief Move figure right
 *
 * Move figure right by one cell
 *
 * @param prms Pointer to GameParams_t struct
 */
void MoveRight(GameParams_t *prms);

/**
 * @brief Move figure left
 *
 * Move figure left by one cell
 *
 * @param prms Pointer to GameParams_t struct
 */
void MoveLeft(GameParams_t *prms);

/**
 * @brief Attach figure to board cells
 *
 * Figure cells become field cells
 *
 * @param prms Pointer to GameParams_t struct
 */
void Attach(GameParams_t *prms);

/**
 * @brief Rotate figure
 *
 * Rotate figure on 90 degrees right
 *
 * @param prms Pointer to GameParams_t struct
 */
void Rotate(GameParams_t *prms);

/**
 * @brief Check are collided field and figure
 *
 * Check are cells under figure
 *
 * @param prms Pointer to GameParams_t struct
 *
 * @return  True or false
 */
bool IsCollide(GameParams_t *prms);

/**
 * @brief Check is attach
 *
 * Check are cells under figure
 *
 * @param prms Pointer to GameParams_t struct
 *
 * @return  True or false
 */
bool IsAttach(GameParams_t *prms);

/**
 * @brief Remove lines
 *
 * Find for each line is it filled, count removed lines
 *
 * @param field Pointer to tetris field
 *
 * @return Removed lines count
 */
Coord_t LinesDisappeared(int **field);

/**
 * @brief Check can cpawn
 *
 * Check is free space for next figure
 *
 * @param info Pointer to GameInfo_t struct
 *
 * @return True of false
 */
bool CanSpawn(const GameInfo_t *info);

#ifdef __cplusplus
}
#endif

#endif  // BRICK_GAME_TETRIS_TETRIS_H_