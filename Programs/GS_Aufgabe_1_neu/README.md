ToDos:
Overflow-Checks implementieren:
-> arith_div: erledigt.
-> arith_mul: erledigt(sofern evtl. seiteneffekte nicht berücksichtigt werden müssen)
-> arith_sub: erledigt.
-> arith_add: erledigt.

Error-handling für arith-funktionen jeweils implementieren:
-> arith_div: erledigt.
-> arith_mul: erledigt.
-> arith_sub: erledigt.
-> arith_add: erledigt.

Modulkonzept "ordentlich" aufzeichnen:
-> arith-functions in arithmetics-Modul zusammenfassen(arithmetics.h, arithmetics.c): erledigt.
-> danach die Modulbeschreibungen in den jew. header-files im doxygen-Format anpassen
-> testfälle-matrix(tabelle) erstellen
-> main-funktion-Konzept überlegen: (erledigt).
-> main-funktion sourcecode hinzufügen: erledigt.

Pretty-Printer und Linter testen/konfigurieren:

/****************************************************************/

Testfälle (nach Modulen gruppiert, Legende: S = "test successfull", F = "test failed", N = "test not executed yet"):

Beispiel-Eingabesequenz:
- "25 8 67+r/p" == 3: S

arithmetics-Modul:
-> add(): 
- "2 4 +p" == 6: S 
-> sub(): 
- "9 10-p" == -1: S
-> mul():
- "6 10*p" == 60: S
- "1024 10*p" == 10240: S
-> div():
- "4 2/p" == 2: S
- "11 3/p" == 3: S
- "12 5/p" == 2: S
- "56 0/p" == DIVISION durch Null: S

stack-Modul:

Bereichsueberschreitungs-Tests:
- "1 2-p 1024*p 1024*p 1024*p" == Bereichsueberschreitung": F (overflow schon nach "1 2-p 1024*p")
- "2147483648*p" == 2147483648: S
- "1 2-p 2147483648*p" == : F("Ungueltige Eingabe")
