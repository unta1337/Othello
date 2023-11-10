#ifndef __PLAYER_H
#define __PLAYER_H

typedef enum {
    NONE,
    PLAYER1,
    PLAYER2,
    ELSE,
    NUM_PLAYER_T
} player_t;

static const char* player_names[NUM_PLAYER_T] = {
    [NONE] = "None",
    [PLAYER1] = "Player 1",
    [PLAYER2] = "Player 2",
    [ELSE] = "Else"
};

static const char player_symbols[NUM_PLAYER_T] = {
    [NONE] = ' ',
    [PLAYER1] = 'O',
    [PLAYER2] = 'X',
    [ELSE] = 'E'
};

#endif
