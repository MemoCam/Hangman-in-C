/*
Projekt             : Hangman
Dateiname           : HHangMenu.c
Author              : Mehmet Çam
Version             : 1.0
Inhaltsbeschreibung : Galgenmännchen spiel, Menü
*/
#include <ncurses.h>
#include <string.h>
#include "HangMenu.h"

int menuprint(){

    initscr(); // Initialisiere ncurses
    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol); // Ermittle die Größe des Bildschirms

    /*einfaches Menu wird geprintet*/
    mvprintw(1, 1, "Menü");

    mvprintw(3, 1, "Play Modi:");

    mvprintw(5, 1, "Player vs Player");
    mvprintw(6, 1, "press (P)");

    mvprintw(8, 1, "KI vs Player");
    mvprintw(9, 1, "press (K)");



    refresh();

    /*unendlich schleife, bis p oder k eingegeben wird.*/
    while (1) {
        int e;
        e = getch();
        if (e == 'p'||e=='P'){
            clear();
            return 1;
            
        }

        else if (e == 'k'||e=='K'){           
            clear();
            return 0;
        }
    }

}