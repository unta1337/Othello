#ifndef __CONSOLEUTIL_H
#define __CONSOLEUTIL_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termio.h>
#endif

int getchar_no_echo();
void clear_console();

void set_color_red();
void set_color_blue();
void set_color_reset();

#endif
