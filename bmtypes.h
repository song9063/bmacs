/*
    This file is part of Bmacs
    BoltEMACS(Bolt is my dog's name)


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
#ifndef _BM_BMACS_TYPES_H_
#define _BM_BMACS_TYPES_H_

#include <ncurses.h>

typedef struct _BM_POS {
    int y;
    int x;
} BM_POS;

typedef struct _BM_SIZE {
    int h;
    int w;
} BM_SIZE;

typedef struct _BM_RECT {
    BM_POS pos;
    BM_SIZE size;
} BM_RECT;


#endif