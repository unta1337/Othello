#ifndef __BOARD_H
#define __BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "player.h"

typedef struct {
    size_t row;
    size_t col;
} cursor_t;

typedef struct {
    player_t** board;
    size_t rows;
    size_t cols;
    cursor_t cursor;
} board_t;

typedef enum {
    LEFT,
    DOWN,
    UP,
    RIGHT,
    NUM_DIRECTION_T
} direction_t;

static const int directions[NUM_DIRECTION_T][2] = {
    [LEFT] = { 0, -1 },
    [DOWN] = { 1, 0 },
    [UP] = { -1, 0 },
    [RIGHT] = { 0, 1 }
};

board_t board_create(const size_t rows, const size_t cols);
void board_delete(board_t* ths);

void board_print(const board_t* ths, player_t current_player);

void board_set(board_t* ths, const player_t player);
void board_move_cursor(board_t* ths, const direction_t dir);

player_t board_check_winner(const board_t* ths);

#endif
