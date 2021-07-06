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
#define BM_WIN_TITLE_MAXLEN 33

#define BM_WIN_STATUSBAR_MAXLEN 33

/* 
    Minimum size of Editor 
    - Bottom status bar: 1 lines
    - Code editor: 2 lines, 4 columns
    - Right vetical line: 1 columns
*/
#define BM_EDITOR_WIN_MIN_W 15
#define BM_EDITOR_WIN_MIN_H 5

typedef enum _BM_WIN_SPLIT_DIR {
    BM_WIN_SPLIT_DIR_VER = 0, /* Vertical */
    BM_WIN_SPLIT_DIR_HOR      /* Horizontal */
} BM_WIN_SPLIT_DIR;

typedef struct _BM_WINDOW {
    BM_WIN_TYPE wintype;

    WINDOW *p_win;
    BM_RECT rect;
    BM_SIZE min_size;
    wchar_t sz_title[BM_WIN_TITLE_MAXLEN];

    struct _BM_WINDOW *p_prev;
    struct _BM_WINDOW *p_next;
    BM_WIN_SPLIT_DIR nextdir;
} BM_WINDOW;


/* Window Life cycle */
BM_WINDOW *bm_newwin(const BM_WIN_TYPE, const BM_RECT, 
    const wchar_t *, const BM_SIZE); /* Normal window */
BM_WINDOW *bm_newwin_editor(const BM_RECT, const wchar_t *);
BM_WINDOW *bm_newwin_filelist(const BM_RECT, const wchar_t *);
void bm_delwin(BM_WINDOW *);

int bm_addsubwin(
    BM_WINDOW *, BM_WINDOW *, 
    const BM_WIN_SPLIT_DIR);

/* Window Properties */
void bm_setwin_title(BM_WINDOW *, const wchar_t *);

/* Window Render */
int bm_renderwin(BM_WINDOW *);

int bm_renderwin_frame(BM_WINDOW *p_bmwin);
int bm_renderwin_stbar(BM_WINDOW *p_bmwin);

/* Resize, Move */
int bm_mvwin(BM_WINDOW *, const int newy, const int newx);
int bm_resizewin(BM_WINDOW *, const int newh, const int neww);

/* Utilities */
int bm_canaddwin(
    BM_WINDOW *, BM_WINDOW *, 
    const BM_WIN_SPLIT_DIR);
void bm_calc_splitsize(const BM_WINDOW *, BM_RECT *, 
    const BM_WINDOW *, BM_RECT *,
    const BM_WIN_SPLIT_DIR);
int bm_test_winsize(BM_WINDOW *, const int, const int);

#endif
