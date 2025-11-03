/**
 * @file common.h
 * @author kaseltzt
 * @date 2024-04-27
 * @brief Declaration of common functions for brick games
 */

#ifndef CPP3_BRICKGAME_V2_0_COMMON_H_
#define CPP3_BRICKGAME_V2_0_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#define HEIGHT 20
#define WIDTH 10

#define TETROMINO_HEIGHT 2
#define TETROMINO_WIDTH 4

typedef enum {
  INFO_NOT_START = 0,
  INFO_START,
  INFO_PAUSE,
  INFO_FINISH
} InfoPause_t;

/**
 * @brief Signals for fsm
 *
 * User input, used as signals (columns) for finite state machine table
 */
typedef enum {
  Start = 0,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief Game data struct
 *
 * Game logic data
 *
 * @param field Game field
 * @param next Next spawn figure for preview
 * @param score Game score
 * @param high_score Game high score from file
 * @param level Gamel level, min 1, max 10
 * @param speed Game speed, min 1, max 10
 * @param pause Pause flag
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum { TETRIS = 0, SNAKE } Game_t;

/**
 * @brief Init Info
 *
 * Info Info struct, allocates memory for **field and **next
 *
 * @param high_score_file_name File containing high score
 *
 * @return Game Info struct
 */
GameInfo_t InitInfo(const char *high_score_file_name);

/**
 * @brief Remove info
 *
 * Allocate memory array of pointers, then memory for each pointer
 *
 * @param info Game Info struct
 * @param high_score_file_name File containing high score
 *
 */
void RemoveInfo(GameInfo_t *info, const char *high_score_file_name);

/**
 * @brief Allocate matrix
 *
 * Allocate memory array of pointers, then memory for each pointer
 *
 * @param n Rows count
 * @param m Columns count
 *
 * @return Pointer to matrix
 */
int **CreateArray2D(size_t n, size_t m);

/**
 * @brief Free matrix
 *
 * Free pointers, then free pointer to array of pointers
 *
 * @param array Matrix
 * @param n Rows count
 */
void RemoveArray2D(int **array, size_t n);

/**
 * @brief Read high score
 *
 * Read number from defined file
 *
 * @param file_name Name of file with high score
 *
 * @return Read number
 */
unsigned ReadHighScore(const char *file_name);

/**
 * @brief Write high score
 *
 * Write number in defined file

 * @param high_score New high score
 * @param file_name Name of file with high score
 *
 */
void WriteHighScore(const char *file_name, const unsigned high_score);

#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICKGAME_V2_0_COMMON_H_