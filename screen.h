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
    along with Bmacs.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef _BM_BMACS_SCREEN_H_
#define _BM_BMACS_SCREEN_H_

#include <ncurses.h>
#include <string.h>
#include <wchar.h>
#include "bmtypes.h"

/* Max length of title string */
#define BM_WIN_TITLE_MAXLEN 20

/* 
    Minimum size of Editor 
    - Bottom status bar: 1 lines
    - Code editor: 2 lines, 4 columns
    - Right vetical line: 1 columns
*/
#define BM_EDITOR_WIN_MIN_W 5
#define BM_EDITOR_WIN_MIN_H 3

typedef enum _BM_WIN_SPLIT_DIR {
    BM_WIN_SPLIT_DIR_VER = 0, /* Vertical */
    BM_WIN_SPLIT_DIR_HOR      /* Horizontal */
} BM_WIN_SPLIT_DIR;


typedef struct _BM_WINDOW {
    WINDOW *p_win;
    BM_RECT rect;
    wchar_t sz_title[BM_WIN_TITLE_MAXLEN];

    /* Minimum size */
    BM_SIZE min_size;

    WINDOW *p_child;
} BM_WINDOW;

/*
void bm_calc_half_winrect(
    WINDOW *p_win, 
    BM_WIN_SPLIT_DIR dir, 
    BM_RECT *p_rect_out
);
*/

/* Window */
BM_WINDOW *bm_newwin(const BM_RECT, const wchar_t *, const BM_SIZE); /* Normal window */
BM_WINDOW *bm_newwin_editor(const BM_RECT, const wchar_t *);
void bm_delwin(BM_WINDOW *);
void bm_set_win_title(BM_WINDOW *, const wchar_t *);

void bm_renderwin(BM_WINDOW *);

/* Resize, Move */
int bm_mvwin(BM_WINDOW *, const int newy, const int newx);
int bm_resizewin(BM_WINDOW *, const int newh, const int neww);
int bm_splitwin(BM_WINDOW *, const BM_WIN_SPLIT_DIR);

#endif
