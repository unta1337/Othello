#ifndef __FRAMEBUFFER_H
#define __FRAMEBUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#define FB_GET_BUFFER(fb, row, col) (fb).buffer[(row) * (fb).cols + (col)]

typedef struct {
    char* buffer;
    int32_t rows;
    int32_t cols;
} framebuffer_t;

typedef struct {
    int32_t row;
    int32_t col;
} cursor_t;

framebuffer_t fb_create(int32_t rows, int32_t cols);
void fb_destroy(framebuffer_t fb);

void fb_draw(framebuffer_t fb);
void fb_clear(framebuffer_t fb);
void fb_rect(framebuffer_t fb, cursor_t begin, cursor_t end, char chr, bool fill);

#endif
