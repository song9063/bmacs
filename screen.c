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




/* Public functions */
BM_WINDOW *bm_newwin(
    const BM_WIN_TYPE wint,
    const BM_RECT rect, 
    const wchar_t *sz_title, 
    const BM_SIZE min_size){
    WINDOW *p_win;
    BM_WINDOW *p_bmwin;
    p_win = newwin(rect.size.h, rect.size.w,
        rect.pos.y, rect.pos.x);
    p_bmwin = malloc(sizeof(BM_WINDOW));
    p_bmwin->p_win = p_win;
    p_bmwin->rect = rect;
    p_bmwin->min_size = min_size;
    p_bmwin->wintype = wint;
    bm_setwin_title(p_bmwin, sz_title);

    return p_bmwin;
}

BM_WINDOW *bm_newwin_editor(const BM_RECT rect, const wchar_t *sz_title){
    BM_SIZE min_size;
    min_size.w = BM_EDITOR_WIN_MIN_W;
    min_size.h = BM_EDITOR_WIN_MIN_H;
    return bm_newwin(BM_WIN_TYPE_EDITOR, rect, sz_title, min_size);
}
BM_WINDOW *bm_newwin_filelist(const BM_RECT rect, const wchar_t *sz_title){
    BM_SIZE min_size;
    min_size.w = BM_EDITOR_WIN_MIN_W;
    min_size.h = BM_EDITOR_WIN_MIN_H;
    return bm_newwin(BM_WIN_TYPE_TEXTLIST, rect, sz_title, min_size);
}
int bm_addsubwin(
    BM_WINDOW *p_parent, BM_WINDOW *p_sub, 
    const BM_WIN_SPLIT_DIR dir){
    BM_RECT prect, srect;
    BM_WINDOW *p_old_next = p_parent->p_next;

    /* test windows size */
    if(bm_canaddwin(p_parent, p_sub, dir) != OK){
        return ERR;
    }
    
    /* Estimate size */
    bm_calc_splitsize(p_parent, &prect, p_sub, &srect, dir);

    /* resize windows */
    if(bm_resizewin(p_parent, prect.size.h, prect.size.w) != OK){
        return ERR;
    }
    if(bm_resizewin(p_sub, srect.size.h, srect.size.w) != OK){
        return ERR;
    }

    /* move windows */
    if(bm_mvwin(p_sub, srect.pos.y, srect.pos.x) != OK){
        return ERR;
    }

    if(p_old_next != NULL){
        p_old_next->p_prev = p_sub;
    }
    p_parent->p_next = p_sub;
    p_parent->nextdir = dir;
    p_sub->p_prev = p_parent;
    p_sub->p_next = p_old_next;
    return OK;
}

void bm_delwin(BM_WINDOW *p_bmwin){
    if(p_bmwin->p_next != NULL){
        p_bmwin->p_next->p_prev = p_bmwin->p_prev;
    }
    if(p_bmwin->p_prev != NULL){
        p_bmwin->p_prev->p_next = p_bmwin->p_next;
    }

    delwin(p_bmwin->p_win);
    free(p_bmwin);
    p_bmwin = NULL;
}

void bm_setwin_title(BM_WINDOW *p_bmwin, const wchar_t *sz_title){
    size_t len = wcslen(sz_title);
    memset(p_bmwin->sz_title, '\0', sizeof(p_bmwin->sz_title));
    if(len >= BM_WIN_TITLE_MAXLEN){
        len = BM_WIN_TITLE_MAXLEN - 1;
    }
    wcsncpy(p_bmwin->sz_title, sz_title, len);
}

int bm_renderwin(BM_WINDOW *p_bmwin){
    int n_ret;
    wclear(p_bmwin->p_win);
    n_ret = bm_renderwin_frame(p_bmwin);
    if(n_ret != OK) return n_ret;

    n_ret = bm_renderwin_stbar(p_bmwin);
    if(n_ret != OK) return n_ret;

    n_ret = wrefresh(p_bmwin->p_win);

    return n_ret;
}

int bm_renderwin_frame(BM_WINDOW *p_bmwin){
    int n_ret = OK;
    if(p_bmwin->nextdir == BM_WIN_SPLIT_DIR_HOR){
        n_ret = mvwvline(p_bmwin->p_win, 0, 
            p_bmwin->rect.size.w-1, ACS_CKBOARD,
            p_bmwin->rect.size.h-1);
    }
    return n_ret;
}
int bm_renderwin_stbar(BM_WINDOW *p_bmwin){
    /*
     * [{Title} {ALL|nn%} {LINES}]
     * */
    wchar_t sz_buf[BM_WIN_STATUSBAR_MAXLEN];
    size_t len;
    int n_ret;
    int bottomy = p_bmwin->rect.size.h-1;
    memset(sz_buf, '\0', sizeof(sz_buf));

    len = wcslen(p_bmwin->sz_title);
    if(len >= p_bmwin->rect.size.w){
        len = p_bmwin->rect.size.w-1;
    }
    if(len >= BM_WIN_STATUSBAR_MAXLEN){
        len = BM_WIN_STATUSBAR_MAXLEN;
    }
    wcsncpy(sz_buf, p_bmwin->sz_title, len);
    swprintf(sz_buf, BM_WIN_STATUSBAR_MAXLEN, L"%ls All L%ld", sz_buf, 1);

    n_ret = mvwprintw(p_bmwin->p_win, bottomy, 0, "%ls", sz_buf);
    if(n_ret != OK) return n_ret;

    wmove(p_bmwin->p_win, bottomy, 0);
    wchgat(p_bmwin->p_win, -1, A_REVERSE, 0, NULL);

    return n_ret;
}


/* Resize, Move */
int bm_mvwin(BM_WINDOW *p_bmwin, const int newy, const int newx){
    int ret=0;
    ret = mvwin(p_bmwin->p_win, newy, newx);
    if(ret == OK){
        p_bmwin->rect.pos.x = newx;
        p_bmwin->rect.pos.y = newy;
    }
    return ret;
}
int bm_resizewin(BM_WINDOW *p_bmwin, const int newh, const int neww){
    int ret = ERR;
    if(p_bmwin->min_size.h > newh || p_bmwin->min_size.w > neww){
        return ERR;
    }

    ret = wresize(p_bmwin->p_win, newh, neww);
    if(ret == OK){
        p_bmwin->rect.size.w = neww;
        p_bmwin->rect.size.h = newh;
    }
    return ret;
}

/* test size 
(parent.min_size+sub.min_size) > parent.size */
int bm_canaddwin(
    BM_WINDOW *p_parent, BM_WINDOW *p_sub, 
    const BM_WIN_SPLIT_DIR dir){
    int pmin, smin, psize;

    if(dir == BM_WIN_SPLIT_DIR_HOR){
        pmin = p_parent->min_size.w;
        smin = p_sub->min_size.w;
        psize = p_parent->rect.size.w;
    }else{
        pmin = p_parent->min_size.h;
        smin = p_sub->min_size.h;
        psize = p_parent->rect.size.h;
    }
    if((pmin+smin)>psize){
        return ERR;
    }
    return OK;
}

void bm_calc_splitsize(const BM_WINDOW *p_parent, BM_RECT *p_prect, 
    const BM_WINDOW *p_sub, BM_RECT *p_srect,
    const BM_WIN_SPLIT_DIR dir){
    int phalf;
    int poldh, poldw;

    p_prect->pos = p_parent->rect.pos;
    poldh = p_parent->rect.size.h;
    poldw = p_parent->rect.size.w;
    if(dir == BM_WIN_SPLIT_DIR_HOR){
        p_prect->size.h = poldh;
        p_srect->size.h = poldh;
        phalf = poldw/2;
        if(phalf >= p_parent->min_size.w && phalf >= p_sub->min_size.w){
            p_srect->size.w = phalf;
            p_prect->size.w = poldw - phalf;
        }else{
            p_prect->size.w = p_parent->min_size.w;
            p_srect->size.w = p_sub->min_size.w;
        }
        p_srect->pos.x = p_prect->size.w;
        p_srect->pos.y = p_parent->rect.pos.y;

    }else{
        p_prect->size.w = poldw;
        p_srect->size.w = poldw;
        phalf = poldh/2;
        if(phalf >= p_parent->min_size.h && phalf >= p_sub->min_size.h){
            p_srect->size.h = phalf;
            p_prect->size.h = poldh - phalf;
        }else{
            p_prect->size.h = p_parent->min_size.h;
            p_srect->size.h = p_sub->min_size.h;
        }
        p_srect->pos.x = p_parent->rect.pos.x;
        p_srect->pos.y = p_prect->size.h;
    }
}
int bm_test_winsize(BM_WINDOW *p_bmwin, const int h, const int w){
    return (p_bmwin->min_size.h <= h && p_bmwin->min_size.w <= w);
}

/* Info Text at Bottom */
void bm_printinfo(const char *sz_text){
    move(LINES-1, 0);
    clrtoeol();

    if(sz_text != NULL){
        mvprintw(LINES-1, 0, sz_text);
    }
    refresh();
}