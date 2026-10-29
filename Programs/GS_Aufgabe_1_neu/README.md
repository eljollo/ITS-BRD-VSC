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
- "2 4 +" == 6: S 
-> sub(): 
- "" == :
-> mul():
- "" == :
-> div():
- "" == :
stack-Modul:

Input-tests(depend on multiple modules):
