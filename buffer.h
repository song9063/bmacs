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
#ifndef _BM_BMACS_BUFFER_H_
#define _BM_BMACS_BUFFER_H_

#include <wchar.h>
#include "bmtypes.h"
#include "screen.h"

typedef struct _BM_WIN_REF_NODE {
    struct _BM_WINDOW *p_bmwin;
    struct _BM_WIN_REF_NODE *p_next;
} BM_WIN_REF_NODE;

typedef struct _BM_BUFFER {
    wchar_t *lines[100];

    struct _BM_WIN_REF_NODE *p_winref; /* Screens those displaying this buffer.  */
} BM_BUFFER;

BM_BUFFER *bm_newbuff(void);
void bm_delbuff(BM_BUFFER *);
void bm_addbuff_ref(BM_BUFFER *, struct _BM_WINDOW *);

#endif