#include "board.h"

bool __is_valid_spot_dir(const board_t* ths,
                         size_t row, size_t col,
                         const player_t current_player, const direction_t dir) {
    row += directions[dir][0];
    col += directions[dir][1];

    player_t opposite_player = current_player == PLAYER1 ? PLAYER2 : PLAYER1;
    size_t count = 0;

    while (row < ths->rows && col < ths->cols
           && ths->board[row][col] == opposite_player) {
        count += ths->board[row][col] == opposite_player;

        row += directions[dir][0];
        col += directions[dir][1];
    }

    if (!(row < ths->rows && col < ths->cols)) {
        return false;
    } else if (ths->board[row][col] == NONE) {
        return false;
    }

    return count > 0;
}

bool __is_valid_spot(const board_t* ths,
                     size_t row, size_t col,
                     const player_t current_player) {
    if (ths->board[row][col] != NONE) {
        return false;
    }

    return __is_valid_spot_dir(ths, row, col, current_player, LEFT)
           || __is_valid_spot_dir(ths, row, col, current_player, UP)
           || __is_valid_spot_dir(ths, row, col, current_player, DOWN)
           || __is_valid_spot_dir(ths, row, col, current_player, RIGHT)

           || __is_valid_spot_dir(ths, row, col, current_player, UP | LEFT)
           || __is_valid_spot_dir(ths, row, col, current_player, UP | RIGHT)
           || __is_valid_spot_dir(ths, row, col, current_player, DOWN | LEFT)
           || __is_valid_spot_dir(ths, row, col, current_player, DOWN | RIGHT);
}

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
    printf("Current Player: %c\n\n", player_symbols[current_player]);

    for (size_t r = 0; r < ths->rows; r++) {
        for (size_t c = 0; c < ths->cols; c++) {
            char curr_symbol = __is_valid_spot(ths, r, c, current_player)
                               ? player_symbols[current_player] ^ 32
                               : player_symbols[ths->board[r][c]];

            if (r == ths->cursor.row && c == ths->cursor.col) {
                printf("<");
            } else {
                printf("[");
            }

            if (curr_symbol == player_symbols[PLAYER1]) {
                set_color_red();
            } else if (curr_symbol == player_symbols[PLAYER2]) {
                set_color_blue();
            }

            if (r == ths->cursor.row && c == ths->cursor.col) {
                printf("%c", curr_symbol);
            } else {
                printf("%c", curr_symbol);
            }

            set_color_reset();

            if (r == ths->cursor.row && c == ths->cursor.col) {
                printf(">");
            } else {
                printf("]");
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

bool board_is_valid_spot(const board_t* ths, const player_t current_player) {
    return __is_valid_spot(ths, ths->cursor.row, ths->cursor.col, current_player);
}

bool board_is_full(const board_t* ths) {
    for (size_t r = 0; r < ths->rows; r++) {
        for (size_t c = 0; c < ths->cols; c++) {
            if (ths->board[r][c] == NONE) {
                return false;
            }
        }
    }

    return true;
}
