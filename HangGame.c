/*
Projekt             : Hangman
Dateiname           : HangmanFinale.c
Author              : Mehmet Çam
Version             : 1.0
Inhaltsbeschreibung : Galgenmännchen spiel, Main
*/

#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "HangMenu.h"       //Menu integriert
#include "HangFile.h"       //Einlesen von einer Wortliste(FILE)


/*Bewusst keine Struct erzeugt, da meiner Meinung nach überflüssig wäre*/
char Eingabe_Wort[20] = {'\0'};         //19 Buchstaben max eingeben
char Eingabe_Buchstabe;
char Aktuelles_Wort[20];                //output
int erlaubte_Fehler = 10;
int begangene_Fehler = 0;
char benutze_Buchstabe[11];             //falsche buchstaben output


int array_check(char* arr, char c){     //guckt ob ein Wort im Array vorkommt

    for (int i=0;arr[i] !='\0';i++){    //die schleife geht bis zur terminierten Null
        if (arr[i]==c){
            return 1;
        }
    }
    return 0;
}

/*Hangman Grafik Print*/
void print_Man(){
    switch(begangene_Fehler){
        case 1:
            mvprintw(6, 60, "_______");
            break;
        case 2:
            mvprintw(6, 63, "|");
            mvprintw(5, 63, "|");
            mvprintw(4, 63, "|");
            mvprintw(3, 63, "|");
            mvprintw(2, 63, "|");
            break;
        case 3:
            mvprintw(1, 64, "________");
            break;
        case 4:
            mvprintw(2, 72, "|");
            break;
        case 5:
            mvprintw(3, 72, "O");
            break;
        case 6:
            mvprintw(4, 72, "|");
            break;
        case 7:
            mvprintw(3, 74, "/");
            break;
        case 8:
            mvprintw(3, 70, "\\");
            break;
        case 9:
            mvprintw(5, 74, "\\");
            break;
        case 10:
            mvprintw(5, 70, "/");
            break;
    }
    refresh();
}


/*Funktion prüft, ob der eingegebene Buchstabe, ein Buchstabe ist oder nicht*/
char getCharInput(){
    char c;
    move(3, 28);    //die dritte Zeile und 28 Spalte, ist der Bereich, wo der Buchstabe eingetippt wird.
    c = getch();

    while(!isalpha(c)){ //Eingabe!= Buchstabe
        move(10,0);
        clrtoeol();
        mvprintw(10, 1, "Buchstabe ungültig");
        move(3, 28);
        c = getch();
    }
    move(10,0);
    clrtoeol();
    return tolower(c);
}

/*Abfrage, wenn man Buchstaben eingeben will*/
void pvp(){
    mvprintw(1, 1, "Geben sie ihr zu erratenes Wort ein: ");
    refresh(); // Aktualisiere den Bildschirm
    getstr(Eingabe_Wort);
    clear();
    // Überprüft den eingegebenen String auf ungültige Zeichen
    for (int i = 0; Eingabe_Wort[i] != '\0'; i++) {
        if (!isalpha(Eingabe_Wort[i])) {
            mvprintw(2, 1, "Unzulässige Eingabe. Bitte nur Klein und Grossbuchstaben");
            pvp();//startet die Funktion von neu, wenn eingabe=unzulässig
        }
    }

}

int main(){
    initscr(); // Initialisiere ncurses
    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol); // Ermittle die Größe des Bildschirms

    /*Menü wird geprintet*/
    if(menuprint())//Wenn die ausgabe der Funktion menuprint=1 ist, dann startet es den PVP Modus
        pvp();
    else//Wenn die ausgabe gleich 0 ist, dann wird ein Wort Zufällig ausgesucht, aus der vorhandenen Liste
        listeZufall(Eingabe_Wort);

    int laenge = strlen(Eingabe_Wort); // Länge des Wortes wird ermittelt

    //Visuelle Überschrift, für die schon versuchten Buchstaben
    attrset(A_UNDERLINE);
    mvprintw(12, 1, "Versuchte Buchstaben");
    attroff(A_UNDERLINE);

    for(int i=0; i<laenge;i++){ //schleife in länge des Wortes
        mvprintw(7, 2*i, "_"); //printet _ striche, um das Spielfeld zu generieren, mit einem Abstand von einer Spalte
        refresh();
        Eingabe_Wort [i]=tolower(Eingabe_Wort[i]); //Alle Eingegebenen Buchstaben werden verkleinert.

    }
    /*Schleife, die bis zum ende des Codes läuft. Läuft so lange, bis man gewinnt, oder bis man verliert*/
    while(begangene_Fehler < erlaubte_Fehler){
        mvprintw(3, 1, "Gebe einen Buchstaben ein: ");
        refresh();

        Eingabe_Buchstabe = getCharInput(); //Buchstaben eingabe, automatische überprüfung auf gültigkeit


        if(array_check(benutze_Buchstabe, Eingabe_Buchstabe)){
            mvprintw(10, 1, "Den Buchstaben haben sie schon versucht");
            refresh();
        }
        else{
            int gefunden = 0;
                    /* Prüft, ob der Buchstabe im Wort vorkommt*/
            for (int i = 0; i < laenge; i++) {
                if (Eingabe_Buchstabe == Eingabe_Wort[i]) {
                    Aktuelles_Wort[i] = Eingabe_Buchstabe;
                    gefunden = 1;
                    mvprintw(7, 2*i, "%c", Eingabe_Buchstabe);
                }
            }

            /*Wenn Buchstaben eingabe falsch ist*/
            if (!gefunden) {
                benutze_Buchstabe[begangene_Fehler] = Eingabe_Buchstabe;    //Buchstabe wird gespeichert
                mvprintw(15, begangene_Fehler*2+1, "%c", benutze_Buchstabe[begangene_Fehler]); //geprintet
                begangene_Fehler++;
                refresh();
                print_Man();    //Galgenmännchen wird weiter geprintet.
            }

            /*Wenn man die Niederlagen bedingung erreicht*/
            if (begangene_Fehler == erlaubte_Fehler) {
                attrset(A_BOLD);
                mvprintw(1, 1, "Sie haben das Spiel verloren.Das gesuchte Wort war: %s", Eingabe_Wort);
                 attroff(A_BOLD);
                mvprintw(4, 72, "|");
                mvprintw(4, 63, "|");
                mvprintw(4, 1, "Drücke eine Taste zum Beenden");
                refresh();
                getch(); // Warte auf Benutzereingabe, bevor das Programm beendet wird
                endwin(); // Beende ncurses
                return 0;

            }

            /*überprüft, ob der string des aktuelle Wort gleich des Eingabe Wortes ist. */
            else if(strcmp (Aktuelles_Wort, Eingabe_Wort)==0){
                attrset(A_BOLD);
                mvprintw(1, 1, "Gratulation, Sie haben das Spiel gewonnen");
                attroff(A_BOLD);
                mvprintw(4, 1, "Drücke eine Taste zum Beenden");
                refresh();
                getch(); // Warte auf Benutzereingabe, bevor das Programm beendet wird
                endwin(); // Beende ncurses
                return 0;
            }

        }

    }

}
