#ifndef __BOARD_H
#define __BOARD_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "config.h"

#if BOARD_ROWS % 2 == 1 || BOARD_ROWS_COLS % 2 == 1
#error BOARD_ROWS and BOARD_ROWS must be an even integer.
#endif

#define ROWS (size_t)BOARD_ROWS
#define COLS (size_t)BOARD_COLS

typedef enum {
    NONE,
    PLAYER1,
    PLAYER2,
    ELSE,
    NUM_PLAYER_KIND
} player_t;

typedef struct {
    size_t row;
    size_t col;
} cursor_t;

static const char player_symbols[NUM_PLAYER_KIND] = {
    [NONE] = ' ',
    [PLAYER1] = 'O',
    [PLAYER2] = 'X',
    [ELSE] = 'E'
};

extern player_t board[ROWS][COLS];
extern cursor_t cursor;

void board_init();
void board_print();

bool board_set(size_t row, size_t col, player_t player);

player_t board_check_winner();

#endif
