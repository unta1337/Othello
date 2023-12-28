#include <stdio.h>

#include "board.h"
#include "consoleutil.h"
#include "framebuffer.h"

#include <time.h>
#include <errno.h>

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

int main() {
    int32_t rows = 40;
    int32_t cols = 120;

    cursor_t top_left = { .row = 0, .col = 0 };
    cursor_t bottom_right = { .row = rows - 1, .col = cols - 1 };

    framebuffer_t fb = fb_create(rows, cols);

    int32_t r = 0;
    int32_t c = 0;

    int32_t w = 5;
    int32_t h = 5;

    int32_t vr = 1;
    int32_t vc = 1;

    while (true) {
        fb_clear(fb);
        // fb_rect(fb, top_left, bottom_right, '*', false);
        fb_rect(fb,
                (cursor_t){ .row = r, .col = c },
                (cursor_t){ .row = r + h - 1, .col = c + w - 1 },
                '#', false);

        clear_console();
        fb_draw(fb);
        msleep(16);

        r += vr;
        c += vc;

        if (r >= fb.rows) {
            r = -h + 1;
        }
        if (c >= fb.cols) {
            c = -w + 1;
        }
        if (r + h - 1 < 0) {
            r = rows + 1;
        }
        if (c + w - 1 < 0) {
            c = cols + 1;
        }
    }

    fb_destroy(fb);

    return 0;
}

int main2() {
    const size_t rows = 8;
    const size_t cols = 8;
    board_t board = board_create(rows, cols);

    player_t curr = PLAYER1;

    while (!board_is_full(&board)) {
        clear_console();

        board_update(&board, curr);
        if (!board_has_valid_spot(&board, curr)) {
            curr ^= SWITCH_PLAYER;
            continue;
        }

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
                       flip(&board, curr);
                       curr ^= SWITCH_PLAYER;
                   }
                   break;

        case 'q': goto while_end;
        }
    }
while_end:;
    player_t winner = board_has_winner(&board);

    clear_console();
    board_print(&board, curr);

    for (size_t i = 0; i < rows; i++) {
        printf("===");
    }
    printf("\nDone!\n");
    printf("Winner: ");
    switch (winner) {
    case NONE:
        printf("NONE!\n");
        break;
    default:
        printf("%c!\n", player_symbols[winner]);
        break;
    }

    return 0;
}
