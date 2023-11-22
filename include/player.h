#ifndef __PLAYER_H
#define __PLAYER_H

typedef enum {
    NONE = 0b0000,
    PLAYER1 = 0b0001,
    PLAYER2 = 0b0010,
    IS_VALID = 0b1000,
    SWITCH_PLAYER = 0b0011,
    CAP_PLAYER_T = 0b10000
} player_t;

static const char player_symbols[CAP_PLAYER_T] = {
    [NONE] = ' ',
    [PLAYER1] = 'O',
    [PLAYER2] = 'X',
    [PLAYER1 | IS_VALID] = 'o',
    [PLAYER2 | IS_VALID] = 'x'
};

#endif
