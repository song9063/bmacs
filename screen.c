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
#include "screen.h"
#include <stdlib.h>

void bm_calc_half_rect_of_window(
    WINDOW *p_win, 
    BM_WINDOW_SPLIT_DIRECTION dir, 
    BM_RECT *p_rect_out){
    int h=0, w=0;
    int x=0, y=0;
    
    getmaxyx(p_win, h, w); // Size of p_win
    getbegyx(p_win, y, x); // Position of p_win
    p_rect_out->x = x;
    p_rect_out->y = y;

    if(dir == BM_WINDOW_SPLIT_VERTICAL){
        p_rect_out->w = w/2;
        p_rect_out->h = h;
    }else if(dir == BM_WINDOW_SPLIT_HORIZONTAL){
        p_rect_out->w = w;
        p_rect_out->h = h/2;
    }
}

BM_EDITOR_WINDOW *bm_new_editor_window(const BM_RECT *p_rect, wchar_t *sz_title){
    WINDOW *p_win = newwin(p_rect->h, p_rect->w,
        p_rect->y, p_rect->x);
    //box(p_win, 0, 0);

    BM_EDITOR_WINDOW *p_editor_win = malloc(sizeof(BM_EDITOR_WINDOW));
    p_editor_win->p_win = p_win;
    bm_set_editor_window_title(p_editor_win, sz_title);
    wrefresh(p_win);
    return p_editor_win;
}

void bm_destroy_editor_window(BM_EDITOR_WINDOW *p_editor_win){
    delwin(p_editor_win->p_win);
    free(p_editor_win);
    p_editor_win = NULL;
}

void bm_set_editor_window_title(BM_EDITOR_WINDOW *p_editor_win, wchar_t *sz_title){
    size_t n_title_len = wcslen(sz_title);
    mvwprintw(p_editor_win->p_win, 10, 1, "Length: %d", n_title_len);
    memset(p_editor_win->sz_title, 0x00, sizeof(p_editor_win->sz_title));
    if(n_title_len > (p_editor_win->rect.w-2)){
        n_title_len = p_editor_win->rect.w-2;
    }else if(n_title_len > BM_MAX_WINDOW_TITLE_LENGTH){
        n_title_len = BM_MAX_WINDOW_TITLE_LENGTH;
    }
    wcsncpy(p_editor_win->sz_title, sz_title, n_title_len);
    mvwprintw(p_editor_win->p_win, 1, 0, "%ls", p_editor_win->sz_title);
}