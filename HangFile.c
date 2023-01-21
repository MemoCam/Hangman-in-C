/*
Projekt             : Hangman
Dateiname           : HangFile.c
Author              : Mehmet Çam
Version             : 1.0
Inhaltsbeschreibung : Galgenmännchen spiel, Liste auslesen und durch zufall wort bestimmen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <time.h>
#include "HangFile.h"

/*Funktion, die aus einer txt FILE liest, eine zufällige Zeile aus der FILE aussucht und diese dann als String speichert*/
void listeZufall(char *wort){

    char *Dateien_Pfad = "/home/mehmet/Dokumente/Hangman/Game/WortListe.txt";   //Pfad gegebenfalls ändern
    FILE *fp = fopen(Dateien_Pfad, "r");


    if(fp==NULL) {//wenn nicht geöffnet, dann gibt sie eine Fehlermeldung
        mvprintw(1, 1, "datei konnte nicht geöffnet werden ");
        return;
    }
    /*Anzahl der Zeilen in der Datei gezählt*/
    int counter=0;
    char c;
    while ((c=fgetc(fp))!=EOF){
        if (c=='\n')
            counter++;
    }

    rewind(fp);

    /*Zufällige Reihe bestimmen*/
    srand(time(NULL));
    int zufall=rand()%counter;
    counter=0;
    while (counter < zufall) {
        if ((c=fgetc(fp)) == '\n')
            counter++;
    }

    char zufallWort[20];   
    fscanf(fp,"%s\n",zufallWort);//Wort aus der Zeile gelesen und in eine Variable gespeichert
    strcpy(wort, zufallWort);//das herausgesuchte Wort in den übergebenen String kopiert 

    fclose(fp);
}
