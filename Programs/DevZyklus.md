## Entwicklungszyklus Lasse_und_Tom

# General Rules
1. In den main-branch werden nur erfolgreiche Builds gepusht, sodass dort immer eine (mehr oder weniger) lauffähige Version des aktuellen Projektes liegt.
fehlerhafte Builds dürfen nur in den eigenen Branch gepusht werden.

2. Alle Fragen hinsichtlich erwarteter und zurückgegebener Parameter sowie Testfälle/Beispielaufrufe werden vor Implementierung geklärt.
Bei der Implementierung werden NUR die quellcode-Dateien, für deren Implementierung man zuständig ist, verändert!!
(main-Modul ist Sonderfall, ggf. diskutieren)
Das soll Anzahl der Merge-Conflicts verringern, bzw. möglichst auf main.c reduzieren!

3. vor jedem Merge nach main muss in jedem eigenen Branch ein erfolgreicher Build des aktuellen Projekts vorhanden sein!!

# 1. Modulkonzept
Aus Projektanforderungen ein vorläufiges Modulkonzept erstellen, also die gegebenen Anforderungen grob auf 
(sinnvolle) Module verteilen.
In Draw.io visualisieren und Abhängigkeiten zwischen Modulen dort darstellen.

# 2. Projekt erstellen
Neues C-Projekt erstellen. 
Für jedes Modul aus dem ersten Modulkonzeptentwurf(Draw.io-file) eine header-Datei erstellen.
Den Zweck jedes Moduls jeweils mit Kommentaren im Doxygen-Format beschreiben.
(Nach jeder Änderung) Prüfen, ob die aktuelle Projektversion bei jedem erfolgreich läuft(buildet)!!

# 3. Modulaufteilung und Deklaration der benötigten Funktionen
Für einzelne Module folgende Fragen beantworten und Antworten im Doxygen-Format in jew. header-files schreiben:
(ggf. Modulaufteilung anpassen)
1. Welche Funktionen werden  benötigt ?
2. Welche Input-Parameter benötigen diese und was geben sie zurück ? (In den Doxygen-Block jeder einzelnen Funktion)
3. Anhand der gewonnenen Erkenntnisse die Input/Output-Anforderungen, ggf. die Aufteilung auf einzelne Funktionen,
anpassen(also @param, etc.)
4. Deklarationen der benötigten Funktionen in den header-files ihrer Module hinzufügen.
5. Arbeitsaufwand aufteilen:
    - In Draw.io-Modulkonzept farblich kenntlich machen (ggf. soweit möglich)
    - In jew. Doxygen-Kommentare der funktionsdeklarationen, den @author-Parameter entsprechend anpassen.
6. Testfälle definieren, d.h. Beispielaufrufe aller Funktionen in main.c hinzufügen(erstmal als Kommentare)

# 4. Module zum Projekt hinzufügen
- passende quellcode-c-files für jedes Modul erstellen.
- c-files und header in cproject.yml schreiben(siehe README.md "Module hinzufügen")

# 5. Prüfen, ob aktuelle Version bei jedem läuft (Build erfolgreich jew. ?)
- ggf. anpassen, Troubleshooting
- auf main pushen

# 6. Aus 1. bis 3. entstandene, erfolgreich buildende Projektversion von main auf jew. Branches pushen.

# 7. Implementierung der Funktionen gemäß Aufteilung und unter Einbehaltung von General Rules

# 8. sofern auf jedem branch ein erfolgreicher Build vorliegt (und alle testfälle erfolgreich), diese gemeinsam in main mergen
1. User1 mergt Branch "User1" in "main".
2. Für erfolgreichen Build sorgen und User1 pusht auf "main"(remote).
3. User2 pullt Branch "main"
4. Gemeinsam evtl. auftretende Merge-Conflicts lösen
5. User2 mergt Branch "User2" mit "main".
6. für erfolgreichen Build  sorgen und User2 pusht auf "main"
7. User1 pullt aktuelle Version von "main".
8. evtl. lokal auftretende Merge-Conflicts lösen, sodass jeder die gleiche lauffähige Projektversion am Ende hat.

# 9. evtl. auftretende Laufzeitfehler(beim Ausführen auf Board) lösen
- Dafür arbeitet jeder in main.
- Möglichst Fehlersuche zusammen, ansonsten:
    1. pull/fetch, um neueste Änderungen zu integrieren.
    2. Änderungen vornehmen.
    3. für erfolgreichen Build sorgen.
    4. auf main pushen.

# 10. letzten Stand vor Abgabe passend taggen.