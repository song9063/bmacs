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
#include <ncurses.h>
#include <locale.h>


int main(int argc, char *argv[]){
    BM_WINDOW *p_win_root;
    BM_RECT rect_root;

    setlocale(LC_ALL,"");

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    /* Root Window */
    getbegyx(stdscr, rect_root.pos.y, rect_root.pos.x);
    getmaxyx(stdscr, rect_root.size.h, rect_root.size.w);
    p_win_root = bm_newwin_editor(NULL, rect_root, L"Root");
    bm_renderwin(p_win_root);

    getch();
    bm_mvwin(p_win_root, 0, 0);
    bm_resizewin(p_win_root, LINES, 40);
    bm_renderwin(p_win_root);
    
    getch();
    bm_delwin(p_win_root);
    endwin();

    return 0;
}