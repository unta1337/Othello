#include "board.h"

player_t board[ROWS][COLS] = { 0, };
cursor_t cursor = { 0, };

void board_init() {
    memset(board, 0, ROWS * COLS * sizeof(player_t));
    memset(&cursor, 0, sizeof(cursor_t));

    board[ROWS / 2 - 1][COLS / 2 - 1] = PLAYER1;
    board[ROWS / 2][COLS / 2] = PLAYER1;

    board[ROWS / 2 - 1][COLS / 2] = PLAYER2;
    board[ROWS / 2][COLS / 2 - 1] = PLAYER2;

    cursor.row = ROWS / 2 - 1;
    cursor.col = COLS / 2 - 1;
}

void board_print() {
    for (size_t r = 0; r < ROWS; r++) {
        for (size_t c = 0; c < COLS; c++) {
            if (r == cursor.row && c == cursor.col) {
                printf("<%c>", player_symbols[board[r][c]]);
            } else {
                printf("[%c]", player_symbols[board[r][c]]);
            }
        }
        printf("\n");
    }
}

bool board_set(size_t row, size_t col, player_t player) {
    if (row >= ROWS) {
        fprintf(stderr, "Error: Board row out of bound: %zu, %zu.\n", row, ROWS);
        return false;
    }
    if (col >= COLS) {
        fprintf(stderr, "Error: Board row out of bound: %zu, %zu.\n", col, COLS);
        return false;
    }

    board[row][col] = player;

    return true;
}

player_t board_check_winner() {
    size_t p1 = 0;
    size_t p2 = 0;

    for (size_t r = 0; r < ROWS; r++) {
        for (size_t c = 0; c < COLS; c++) {
            p1 += board[r][c] == PLAYER1;
            p2 += board[r][c] == PLAYER2;
        }
    }

    if (p1 + p2 < ROWS * COLS) {
        return NONE;
    } else if (p1 == p2) {
        return ELSE;
    }

    return p1 > p2 ? PLAYER1 : PLAYER2;
}
