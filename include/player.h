#ifndef __PLAYER_H
#define __PLAYER_H

typedef enum {
    NONE,
    PLAYER1,
    PLAYER2,
    NUM_PLAYER_T
} player_t;

static const char player_symbols[NUM_PLAYER_T] = {
    [NONE] = ' ',
    [PLAYER1] = 'O',
    [PLAYER2] = 'X'
};

#endif
