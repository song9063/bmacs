/*
    This file is part of Bmacs
    Bmacs=Bolt-Emacs(Bolt is my dog's name)

    Bmacs was written by Song Junwoo
    Bmacs (c) Copyright 2021 Song Junwoo
    - busang.song@gmail.com
    - https://www.github.com/song9063

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
#include <ncurses.h>
#include <locale.h>


int main(int argc, char *argv[]){
    BM_EDITOR_WINDOW *p_win_left;
    BM_RECT rect_win_left;

    setlocale(LC_ALL,"");

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    bm_calc_half_rect_of_window(stdscr, 
        BM_WINDOW_SPLIT_VERTICAL, 
        &rect_win_left);
    p_win_left = bm_new_editor_window(&rect_win_left, L"윈도우");
  
    mvwprintw(p_win_left->p_win, 0, 0, "Hello Left");
    mvwprintw(p_win_left->p_win, 1, 0, "%ls", p_win_left->sz_title);
    wrefresh(p_win_left->p_win);

/*
    printw("Screen H: %d, W: %d", LINES, COLS);
    mvprintw(1,0,"Left Window: H:%d, W:%d, X:%d, Y:%d", 
        rect_win_left.h, rect_win_left.w,
        rect_win_left.x, rect_win_left.y);
    mvprintw(2,0,"Right Window: H:%d, W:%d, X:%d, Y:%d", 
        rect_win_left.h, rect_win_left.w,
        rect_win_left.x + rect_win_left.w, rect_win_left.y);*/
    
    getch();
    bm_destroy_editor_window(p_win_left);
    endwin();

    return 0;
}