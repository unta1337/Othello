#ifndef __BOARD_H
#define __BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "player.h"
#include "consoleutil.h"

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
    LEFT = 0b0001,
    DOWN = 0b0010,
    UP = 0b0100,
    RIGHT = 0b1000,
    CAP_DIRECTION_T = 0b10000
} direction_t;

static const int directions[CAP_DIRECTION_T][2] = {
    [LEFT] = { 0, -1 },
    [DOWN] = { 1, 0 },
    [UP] = { -1, 0 },
    [RIGHT] = { 0, 1 },

    [UP | LEFT] = { -1, -1 },
    [UP | RIGHT] = { -1, 1 },
    [DOWN | LEFT] = { 1, -1 },
    [DOWN | RIGHT] = { 1, 1 }
};

board_t board_create(const size_t rows, const size_t cols);
void board_delete(board_t* ths);

void board_print(const board_t* ths, player_t current_player);

void board_set(board_t* ths, const player_t player);
void board_move_cursor(board_t* ths, const direction_t dir);

bool board_is_valid_spot(const board_t* ths, const player_t current_player);
bool board_is_full(const board_t* ths);

#endif
