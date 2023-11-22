#include <stdio.h>

#include "board.h"
#include "consoleutil.h"

int main() {
    const size_t rows = 8;
    const size_t cols = 8;
    board_t board = board_create(rows, cols);

    player_t curr = PLAYER1;
    player_t winner = NONE;

    while ((winner = board_is_full(&board)) == NONE) {
        clear_console();

        board_update(&board, curr);
        // if (!board_has_valid_spot(&board, curr)) {
        //     curr ^= SWITCH_PLAYER;
        //     continue;
        // }

        board_print(&board, curr);

        switch (getchar_no_echo()) {
        case 'h': board_move_cursor(&board, LEFT); break;
        case 'j': board_move_cursor(&board, DOWN); break;
        case 'k': board_move_cursor(&board, UP); break;
        case 'l': board_move_cursor(&board, RIGHT); break;

#ifdef _WIN32
        case '\r':
#else
        case '\n':
#endif
                   if (board_is_valid_spot(&board, curr)) {
                       board_set(&board, curr);
                       curr ^= SWITCH_PLAYER;
                   }
                   break;

        case 'q': goto while_end;
        }
    }
while_end:;

    clear_console();
    board_print(&board, curr);

    for (size_t i = 0; i < rows; i++) {
        printf("===");
    }
    printf("\nDone!\n");

    return 0;
}
