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
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

BM_BUFFER *bm_newbuff(void){
    BM_BUFFER *p_buf;
    p_buf = (BM_BUFFER *)malloc(sizeof(BM_BUFFER));
    if(p_buf == NULL) return NULL;

    /* Init someting */

    return p_buf;
}

void bm_delbuff(BM_BUFFER *p_buf){
    /* Delete nodes of BM_BUFFER */
    BM_WIN_REF_NODE *p_headref = p_buf->p_winref;
    BM_WIN_REF_NODE *p_tmp;
    while(p_headref){
        p_tmp = p_headref;
        p_headref = p_headref->p_next;
        free(p_tmp);
    }

    /* Delete lines of BM_BUFFER */


    free(p_buf);
    p_buf = NULL;
}

/* Attach buffer to window */
void bm_addbuff_ref(BM_BUFFER *p_buf, struct _BM_WINDOW *p_bmwin){
    /* Remove previous link */
    if(p_bmwin->p_buf != NULL){
        /* Todo */
        /* remove p_bmwin from p_bm_win->p_buf->p_winref */
        
    }

    /* add p_bmwin to p_buf->p_winref */


}