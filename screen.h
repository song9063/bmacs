/*
    This file is part of Bmacs
    Bmacs=Bolt-Emacs(Bolt is my dog's name)

    Bmacs was written by Song Junwoo
    Bmacs (c) Copyright 2021 Song Junwoo
    - busang.song@gmail.com
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

#define BM_MAX_WINDOW_TITLE_LENGTH 20
#include <ncurses.h>
#include <string.h>
#include <wchar.h>

typedef struct _BM_RECT {
    int h;
    int w;
    int y;
    int x;
} BM_RECT;

typedef enum _BM_WINDOW_SPLIT_DIRECTION {
    BM_WINDOW_SPLIT_VERTICAL = 0,
    BM_WINDOW_SPLIT_HORIZONTAL
} BM_WINDOW_SPLIT_DIRECTION;

typedef struct _BM_EDITOR_WINDOW {
    WINDOW *p_win;
    BM_RECT rect;
    wchar_t sz_title[BM_MAX_WINDOW_TITLE_LENGTH];
} BM_EDITOR_WINDOW;

void bm_calc_half_rect_of_window(
    WINDOW *p_win, 
    BM_WINDOW_SPLIT_DIRECTION dir, 
    BM_RECT *p_rect_out);

BM_EDITOR_WINDOW *bm_new_editor_window(const BM_RECT *, wchar_t *);
void bm_destroy_editor_window(BM_EDITOR_WINDOW *);

void bm_set_editor_window_title(BM_EDITOR_WINDOW *, wchar_t *);

void bm_split_buffer(BM_WINDOW_SPLIT_DIRECTION);

#endif
