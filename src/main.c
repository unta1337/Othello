#include <stdio.h>

#include "board.h"

int main() {
    board_init();

    player_t curr = PLAYER1;
    player_t winner = NONE;

    // while ((winner = board_check_winner()) == NONE) {
    if ((winner = board_check_winner()) == NONE) {
        board_print();
    }

    return 0;
}
