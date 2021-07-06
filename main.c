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
    int ret;

    BM_WINDOW *p_win_right;
    BM_WINDOW *p_win_rightbottom;

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
    p_win_root = bm_newwin_editor(rect_root, L"Root");
    refresh();
    bm_renderwin(p_win_root);
    //wgetch(p_win_root->p_win);

    p_win_right = bm_newwin_editor(rect_root, L"Sub");
    ret = bm_addsubwin(p_win_root, p_win_right, BM_WIN_SPLIT_DIR_HOR);
    bm_renderwin(p_win_root);
    bm_renderwin(p_win_right);
    //wgetch(p_win_root->p_win);

    p_win_rightbottom = bm_newwin_filelist(rect_root, L"BottomRight");
    ret = bm_addsubwin(p_win_right, p_win_rightbottom, BM_WIN_SPLIT_DIR_VER);
    bm_renderwin(p_win_root);
    bm_renderwin(p_win_right);
    bm_renderwin(p_win_rightbottom);

    wgetch(p_win_root->p_win);

/*
    bm_mvwin(p_win_root, 0, 0);
    ret = bm_resizewin(p_win_root, LINES, 16);
    mvwprintw(p_win_root->p_win, 1, 1, "Ret: %d", ret);
    bm_renderwin(p_win_root);
    getch();*/


    bm_delwin(p_win_root);
    bm_delwin(p_win_right);
    bm_delwin(p_win_rightbottom);
    endwin();

    return 0;
}