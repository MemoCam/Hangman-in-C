Vergewissern, dass der FILE Pfad, in das richtige Verzeichnis zeigt.
änderbar in HangFile.c, Zeile 18.

Programm verwendet Ncurses. Es läuft ohne Probleme auf Linux, worauf ncurses installiert ist.
Das Spiel kann man alternativ auch über das Terminal starten, mit der HangGame datei

Wortliste erweiterbar in der Wortliste.txt

Zum erweitern, neue Wörter untereinander reinschreiben.

Bsp:
Maus
Haus
Hund

und nicht
Bsp
Maus Haus
Hund

Keine leere Zeile erzeugen, da ansonsten ein Leeres Wort eingesetzt wird. Daher sollte man sich auch vergewissern, dass die letzte Zeile nicht leer ist.

Keine Sonderzeichen und maximale Wortlänge von 19 Buchstaben.

Bei der Eingabe von Buchstaben, werden sonderzeichen als ungültig deklariert werden.
 
Groß und kleinschreibung, wird gleichermaßen gewertet.


Je nach Compiler, bitte vor dem Spielen, vergewissern, dass das Terminal groß genug ist. Mindestens 16 Zeilen.
