#include "framebuffer.h"

framebuffer_t fb_create(int32_t rows, int32_t cols) {
    framebuffer_t fb = {
        .buffer = (char*)calloc(rows * cols, sizeof(char)),
        .rows = rows,
        .cols = cols
    };

    memset(fb.buffer, ' ', rows * cols * sizeof(char));

    return fb;
}

void fb_destroy(framebuffer_t fb) {
    free(fb.buffer);
}

void fb_draw(framebuffer_t fb) {
    for (int32_t i = 0; i < fb.rows; i++) {
        for (int32_t j = 0; j < fb.cols; j++) {
            printf("%c", FB_GET_BUFFER(fb, i, j));
        }
        printf("\n");
    }
}

void fb_clear(framebuffer_t fb) {
    memset(fb.buffer, ' ', fb.rows * fb.cols * sizeof(char));
}

void fb_rect(framebuffer_t fb, cursor_t begin, cursor_t end, char chr, bool fill) {
    cursor_t b = {
        .row = fmax(0, begin.row),
        .col = fmax(0, begin.col),
    };
    cursor_t e = {
        .row = fmin(fb.rows - 1, end.row),
        .col = fmin(fb.cols - 1, end.col),
    };

    for (int32_t i = b.row; i <= e.row; i++) {
        for (int32_t j = b.col; j <= e.col; j++) {
            if (fill || i == begin.row || i == end.row || j == begin.col || j == end.col) {
                FB_GET_BUFFER(fb, i, j) = chr;
            }
        }
    }
}
