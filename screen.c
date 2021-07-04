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
#include "screen.h"
#include <stdlib.h>

/*
void bm_calc_half_winrect(
    WINDOW *p_win, 
    BM_WIN_SPLIT_DIR dir, 
    BM_RECT *p_rect_out){
    int h=0, w=0;
    int x=0, y=0;
    
    getmaxyx(p_win, h, w);
    getbegyx(p_win, y, x);
    p_rect_out->x = x;
    p_rect_out->y = y;

    if(dir == BM_WIN_SPLIT_DIR_VER){
        p_rect_out->w = w/2;
        p_rect_out->h = h;
    }else if(dir == BM_WIN_SPLIT_DIR_HOR){
        p_rect_out->w = w;
        p_rect_out->h = h/2;
    }
}
*/

BM_WINDOW *bm_newwin(const BM_RECT rect, 
    const wchar_t *sz_title, 
    const BM_SIZE min_size){
    WINDOW *p_win = newwin(rect.size.h, rect.size.w,
        rect.pos.y, rect.pos.x);

    BM_WINDOW *p_editor_win = malloc(sizeof(BM_WINDOW));
    p_editor_win->p_win = p_win;
    p_editor_win->rect = rect;
    p_editor_win->min_size = min_size;
    bm_set_win_title(p_editor_win, sz_title);

    /* Init child */
    p_editor_win->p_child = NULL;

    return p_editor_win;
}

BM_WINDOW *bm_newwin_editor(const BM_RECT rect, const wchar_t *sz_title){
    BM_SIZE min_size;
    min_size.w = BM_EDITOR_WIN_MIN_W;
    min_size.h = BM_EDITOR_WIN_MIN_H;
    return bm_newwin(rect, sz_title, min_size);
}

void bm_delwin(BM_WINDOW *p_editor_win){
    delwin(p_editor_win->p_win);
    free(p_editor_win);
    p_editor_win = NULL;
}

void bm_set_win_title(BM_WINDOW *p_editor_win, const wchar_t *sz_title){
    size_t len = wcslen(sz_title);
    memset(p_editor_win->sz_title, 0x00, BM_WIN_TITLE_MAXLEN);
    if(len > (p_editor_win->rect.size.w-2)){
        len = p_editor_win->rect.size.w-2;
    }else if(len > BM_WIN_TITLE_MAXLEN){
        len = BM_WIN_TITLE_MAXLEN;
    }

    wcsncpy(p_editor_win->sz_title, sz_title, len);
}

void bm_renderwin(BM_WINDOW *p_win){
    size_t len;
    int title_x;
    len = wcslen(p_win->sz_title);
    title_x = (p_win->rect.size.w-len)/2;

    box(p_win->p_win, 0 ,0);

    /* title */
    mvwprintw(p_win->p_win, 0, title_x, "%ls", p_win->sz_title);
    wrefresh(p_win->p_win);
}


/* Resize, Move */
int bm_mvwin(BM_WINDOW *p_win, const int newy, const int newx){
    int ret=0;
    ret = mvwin(p_win->p_win, newy, newx);
    if(ret == OK){
        p_win->rect.pos.x = newx;
        p_win->rect.pos.y = newy;
    }
    return ret;
}
int bm_resizewin(BM_WINDOW *p_win, const int newh, const int neww){
    int ret=0;
    ret = wresize(p_win->p_win, newh, neww);
    if(ret == OK){
        p_win->rect.size.w = neww;
        p_win->rect.size.h = newh;
    }
    return ret;
}

int bm_splitwin(BM_WINDOW *p_win_parent, const BM_WIN_SPLIT_DIR dir){
    /*
    BM_RECT rect_p, rect_c;
    BM_WINDOW p_win_child;
    */
    return OK;
}