#include <stdio.h>

#include "board.h"
#include "consoleutil.h"

int main() {
    const size_t rows = 8;
    const size_t cols = 8;
    board_t board = board_create(rows, cols);

    player_t curr = PLAYER1;
    player_t winner = NONE;

    while ((winner = board_check_winner(&board)) == NONE) {
        clear_console();

        board_print(&board, curr);

        switch (getchar_no_echo()) {
        case 'h': board_move_cursor(&board, LEFT); break;
        case 'j': board_move_cursor(&board, DOWN); break;
        case 'k': board_move_cursor(&board, UP); break;
        case 'l': board_move_cursor(&board, RIGHT); break;

        case '\n': board_set(&board, curr);
                   curr = curr == PLAYER1
                          ? PLAYER2
                          : PLAYER1;
                   break;

        case 'q': goto while_end;
        }
    }
while_end:;

    return 0;
}
