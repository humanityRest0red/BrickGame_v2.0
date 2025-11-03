/**
 * @file common.c
 * @author kaseltzt
 * @date 2024-04-27
 * @brief Implementation of common functions for brick games
 */

#include "common.h"

#include <stdio.h>
#include <stdlib.h>

GameInfo_t InitInfo(const char *high_score_file_name) {
  GameInfo_t info;
  info.field = CreateArray2D(HEIGHT, WIDTH);
  info.next = CreateArray2D(TETROMINO_HEIGHT, TETROMINO_WIDTH);
  info.score = 0;
  info.high_score = ReadHighScore(high_score_file_name);
  info.level = 1;
  info.speed = info.level;
  info.pause = INFO_NOT_START;

  return info;
}

void RemoveInfo(GameInfo_t *info, const char *high_score_file_name) {
  // if (info->score > info->high_score) {
  WriteHighScore(high_score_file_name, info->high_score);
  // }
  RemoveArray2D(info->field, HEIGHT);
  RemoveArray2D(info->next, TETROMINO_HEIGHT);
}

int **CreateArray2D(size_t n, size_t m) {
  int **res = (int **)calloc(sizeof(int *), n);
  if (res) {
    for (size_t i = 0; i < n; ++i) {
      res[i] = (int *)calloc(sizeof(int), m);
    }
  }

  return res;
}

void RemoveArray2D(int **array, size_t n) {
  if (array) {
    for (size_t i = 0; i < n; ++i) free(array[i]);
  }
  free(array);
}

unsigned ReadHighScore(const char *file_name) {
  unsigned high_score = 0;
  FILE *f = fopen(file_name, "r");
  if (f) {
    fscanf(f, "%u", &high_score);
    fclose(f);
  }
  return high_score;
}

void WriteHighScore(const char *file_name, const unsigned high_score) {
  FILE *f = fopen(file_name, "w");
  if (f) {
    fprintf(f, "%u", high_score);
    fclose(f);
  }
}
