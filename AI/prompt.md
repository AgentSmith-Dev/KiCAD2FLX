# Projektname
KiCAD2FLX

# Präambel und Beschreibung des Problems
Mit dem Konstruktionswerkzeug KiCAD werden Daten für die Herstellung von PCBs (Printed Circuit Boards erstellt). Damit die PCBs später von einer Bestückungsmaschine bestückt werden können, kann KiCAD ".pos" (für Position) Dateien erzeugen. Jedes zu bestückende Bauteil hat in der .pos Datei (diese ist ein Textformat) genau eine Zeile, diese enthält: 
- eine Referenz (eindeutige Bezeichnung des Bauteils auf dem PCB)
- einen Wert (charakterisiert das Bauteil technisch)
- Package (Geometrie des Bauteils)
- x, y, z Koordinaten, an denen das Bauteil platziert werden soll
- Side (top für Vorderseite, back für Rückseite)
Die Bestückungsmaschine liest die .pos Datei ein und konfiguriert damit die Bestückung. Im vorliegenden Fall wird eine Bestückungsmaschine vom Typ Essemtec FLX 2011 verwendet (kurz: "FLX").
Der Eintrag "Package" darf bei der FLX maximal 32 Zeichen haben, längere Zeichenketten führen zu einer Fehlermeldung beim Einlesen. In den Konstruktionsdaten von KiCAD sind häufig Daten enthalten, die zu einer Package-Angabe von mehr als 32 Zeichen führen. 

# Ziel
Zu programmieren ist eine Software zur Bedienung auf der Kommandozeile, die eine .pos-Datei von KiCAD einliest und eine neue .pos-Datei für die FLX erstellt.
Dabei werden die Einträge Package so verändert, dass sie nur noch maximal 32 Zeichen haben. Dazu verwendet die zu programmierende Software eine Datei KiCADPackage2FLX.txt. Diese enthält (pro Zeile) einen Eintrag für das Package, wie er in KiCAD verwendet wird und einen weiteren Eintrag, wie er von der FLX verwendet werden kann. 

# Nicht-Ziele
Es werden keine "Vorschläge" für den Package-Eintrag gemacht. Package-Einträge aus KiCAD, die nicht in der KiCADPackage2FLX.txt vorkommen werden unverändert übernommen und es kommt zur Ausgabe einer Fehlermeldung (aber nicht zum Programmabbruch).


# Zielgruppe
Zielgruppe sind Einrichter ("Arbeitsvorbereitung") einer FLX.

# Kernfunktionen
1. Einlesen von drei Argumenten auf der Befehlszeile. 1. Parameter: Name der .pos Datei, die von KiCAD kommt (im Folgenden "KiCAD.pos" genannt), 2.Parameter: Name der .pos Datei für die FLX (im Folgenden "FLX.pos" genannt), 3. Parameter (optional): Name der Konvertierungsdatei (im Folgenden "KiCADPackage2FLX.txt" genannt). Fehlt der Parameter wird "KiCADPackage2FLX.txt" genommen. 
2. Einlesen der KiCAD.pos
3. Einlesen der KiCADPackage2FLX.txt
4. Zeilenweise Durchgehen der KiCAD.pos (bis Dateiende erreicht ist). Für jeden Package-Eintrag prüfen, ob er in der KiCADPackage2FLX.txt enhalten ist. Wenn nicht, Eintrag unverändert übernehmen und - falls er mehr als 32 Zeichebn hat - Fehlermeldung am Bildschirm ausgeben. Wenn ja, den zugehörigen Eintrag für die FLX übernehmen. Dann eine entsprechend modifizierte Zeile in die internen Daten für die FLX.pos-Datei schreiben.
5. Speichern der generierten Daten in der Flx.pos.
6. Ausgabe am Bildschirm, wenn fertig.

# Technische Rahmenbedingungen
- Sprache: C++ (Version 17)
- Zielsystem: Kommandozeilenwerkzeug unter Linux
- Framework: cmake, gcc

## Zieldateien
Die Hauptfunktion main() wird in der Datei main.cpp gespeichert.
Jede erzeugte Klasse bekommt eine eigene Implementierungsdatei.

## Format der .pos Dateien
Zeilen, die mit # (Hash) beginnen sind Kommentarzeilen. Sie werden unverändert übernommen.
Jede Zeile beschreibt genau ein Bauteil.
Die Spalten sind durch Leerzeichen (eines oder mehrere) getrennt.
Als Beispiel habe ich die Datei "CurrentSensor-top.pos" hochgeladen.

## Format der KiCADPackage2FLX.txt Datei
Zeilen, die mit # (Hash) beginnen sind Kommentarzeilen. Sie werden unverändert übernommen.
Jede Zeile beschreibt genau ein Package.
Die erste Spalte ist die Package-Bezeichnung aus KiCAD, die zweite Spalte ist die Package Spalte für die FLX.
Die Spalten sind durch Leerzeichen (eines oder mehrere) getrennt.
Als Beispiel habe ich die Datei "KiCADPackage2FLX.txt" hochgeladen.


# Architekturpräferenz
Die Verwendung der C++ Standardlibrary ist sinnvoll. Zum Verwaltung der einzelnen Zeilen der KiCAD.pos, FLX.pos, KiCADPackage2FLX.txt könnte die std::vector-Klasse zum Einsatz kommen. 
Die Software ist objektorientiert aufzubauen. Zur Verwaltung der Daten von KiCAD.pos, FLX.pos, KiCADPackage2FLX.txt sind einzelne Klassen zu generieren. Die Zeilen der einzelnen Dateien sind ebenfalls in einzelnen Klassen zu verwalten.

# Qualitätsanforderungen
- Performance: keine besonderen Anforderungen 
- Sicherheit: Best Practice für ein C++ Programm - keine weiteren Anforderungen
- Testabdeckung: Erfolgreiche Konvertierung der Beispieldatei CurrentSensor-top.pos
- Dokumentation: DoxyGen konforme Dokumentation
- Die Festlegungen für den Code sind in Datei "CodingStyles.md" aufgeführt, sie sind anzuwenden.

# UI / UX Anforderungen (falls relevant)
Kommandozeilenwerkzeug unter Linux. Ausgabe am Bildschirm über std:cout. Keine Rückfragen während des Programmlaufes.

# Offene Fragen
Keine.