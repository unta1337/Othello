#include "board.h"

board_t board_create(const size_t rows, const size_t cols) {
    board_t ths = {
        .board = (player_t**)malloc(rows * cols * sizeof(player_t*)),
        .rows = rows,
        .cols = cols,
        .cursor = {
            .row = rows / 2 - 1,
            .col = cols / 2 - 1
        }
    };

    for (size_t i = 0; i < rows; i++) {
        ths.board[i] = (player_t*)calloc(cols, sizeof(player_t));
    }

    ths.board[rows / 2 - 1][cols / 2 - 1] = PLAYER1;
    ths.board[rows / 2][cols / 2] = PLAYER1;

    ths.board[rows / 2 - 1][cols / 2] = PLAYER2;
    ths.board[rows / 2][cols / 2 - 1] = PLAYER2;

    ths.cursor.row = rows / 2 - 1;
    ths.cursor.col = cols / 2 - 1;

    return ths;
}

void board_delete(board_t* ths) {
    for (size_t i = 0; i < ths->rows; i++) {
        free(ths->board[i]);
    }
    free(ths->board);
}

void board_print(const board_t* ths, const player_t current_player) {
    printf("Current Player: %s\n\n", player_names[current_player]);

    for (size_t r = 0; r < ths->rows; r++) {
        for (size_t c = 0; c < ths->cols; c++) {
            if (r == ths->cursor.row && c == ths->cursor.col) {
                printf("<%c>", player_symbols[ths->board[r][c]]);
            } else {
                printf("[%c]", player_symbols[ths->board[r][c]]);
            }
        }
        printf("\n");
    }
}

void board_set(board_t* ths, const player_t player) {
    ths->board[ths->cursor.row][ths->cursor.col] = player;
}

void board_move_cursor(board_t* ths, const direction_t dir) {
    ths->cursor.row += directions[dir][0];
    ths->cursor.row %= ths->rows;

    ths->cursor.col += directions[dir][1];
    ths->cursor.col %= ths->cols;
}

player_t board_check_winner(const board_t* ths) {
    size_t p1 = 0;
    size_t p2 = 0;

    for (size_t r = 0; r < ths->rows; r++) {
        for (size_t c = 0; c < ths->cols; c++) {
            p1 += ths->board[r][c] == PLAYER1;
            p2 += ths->board[r][c] == PLAYER2;
        }
    }

    if (p1 + p2 < ths->rows * ths->cols) {
        return NONE;
    } else if (p1 == p2) {
        return ELSE;
    }

    return p1 > p2 ? PLAYER1 : PLAYER2;
}
