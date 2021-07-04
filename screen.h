/*
    This file is part of Bmacs
    Bmacs=Bolt-Emacs(Bolt is my dog's name)

    Bmacs was written by Song Junwoo
    Bmacs (c) Copyright 2021 Song Junwoo
    - https://github.com/song9063/bmacs

    Bmacs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    Bmacs is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef _BM_BMACS_SCREEN_H_
#define _BM_BMACS_SCREEN_H_

#define BM_WIN_TITLE_MAXLEN 20
#include <ncurses.h>
#include <string.h>
#include <wchar.h>

typedef struct _BM_RECT {
    int h;
    int w;
    int y;
    int x;
} BM_RECT;

typedef enum _BM_WIN_DIR {
    BM_WIN_DIR_VER = 0, /* Vertical */
    BM_WIN_DIR_HOR      /* Horizontal */
} BM_WIN_DIR;

typedef struct _BM_WINDOW {
    WINDOW *p_win;
    BM_RECT rect;
    wchar_t sz_title[BM_WIN_TITLE_MAXLEN];
} BM_WINDOW;

void bm_calc_half_winrect(
    WINDOW *p_win, 
    BM_WIN_DIR dir, 
    BM_RECT *p_rect_out);

BM_WINDOW *bm_newwin(const BM_RECT *, wchar_t *);
void bm_delwin(BM_WINDOW *);

void bm_set_win_title(BM_WINDOW *, wchar_t *);

void bm_split_buffer(BM_WIN_DIR);

#endif
