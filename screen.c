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

void bm_calc_half_winrect(
    WINDOW *p_win, 
    BM_WIN_DIR dir, 
    BM_RECT *p_rect_out){
    int h=0, w=0;
    int x=0, y=0;
    
    getmaxyx(p_win, h, w); // Size of p_win
    getbegyx(p_win, y, x); // Position of p_win
    p_rect_out->x = x;
    p_rect_out->y = y;

    if(dir == BM_WIN_DIR_VER){
        p_rect_out->w = w/2;
        p_rect_out->h = h;
    }else if(dir == BM_WIN_DIR_HOR){
        p_rect_out->w = w;
        p_rect_out->h = h/2;
    }
}

BM_WINDOW *bm_newwin(const BM_RECT *p_rect, wchar_t *sz_title){
    WINDOW *p_win = newwin(p_rect->h, p_rect->w,
        p_rect->y, p_rect->x);
    box(p_win, ACS_VLINE, ' ');

    BM_WINDOW *p_editor_win = malloc(sizeof(BM_WINDOW));
    p_editor_win->p_win = p_win;
    p_editor_win->rect = *p_rect;
    bm_set_win_title(p_editor_win, sz_title);
    wrefresh(p_win);
    return p_editor_win;
}

void bm_delwin(BM_WINDOW *p_editor_win){
    delwin(p_editor_win->p_win);
    free(p_editor_win);
    p_editor_win = NULL;
}

void bm_set_win_title(BM_WINDOW *p_editor_win, wchar_t *sz_title){
    int titlex = 0;
    size_t len = wcslen(sz_title);
    memset(p_editor_win->sz_title, 0x00, BM_WIN_TITLE_MAXLEN);
    if(len > (p_editor_win->rect.w-2)){
        len = p_editor_win->rect.w-2;
    }else if(len > BM_WIN_TITLE_MAXLEN){
        len = BM_WIN_TITLE_MAXLEN;
    }

    titlex = (p_editor_win->rect.w-len)/2;
    wcsncpy(p_editor_win->sz_title, sz_title, len);
    mvwprintw(p_editor_win->p_win, 0, titlex, "%ls", p_editor_win->sz_title);
}