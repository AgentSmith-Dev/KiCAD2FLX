# Nomenklaturen

Die Benennung von Variablen folgt dem Prinzip der ungarischen Notation von Charles Simonyi.
Nachstehend sind Ergänzungen/Erweiterungen/Abweichungen definiert, die zu verwenden sind.

## Basistypen
b	Ein bool-Wert
Beispiel	enum	enTafficLight{RED, GREEN, ORANGE};

en	Ein enum Wert

f	Ein Float-Wert

i	Ein Integer

l	Ein long-Wert

c	Ein character-Wert

p	Ein Pointer
Beispiel	void*	pNoTypePointer

up	Ein Unique Pointer
Beispiel	std::unique<class>	up	std::make<class>()

mp	Ein managed Pointer (C# with C++)
Beispiel	tbd

r	Eine Referenz
Beispiel	int&	riAnRefToAnInt

x	Ein winrt-Pointer/Referenz oder winrt-Instanz

Die Präfixe sind auch Funktionsnamen voranzustellen, die einen entsprechenden Variablentypen zurückgeben. 

Auf zusammengesetzte Präfixe ist zu achten - so wird ein "r" vorangestellt, wenn es eine Referenz ist, gefolgt vom eigentlichen Variablennamen.

Strings werden damit i.d.R. als pcStringName gekennzeichnet.

void Funktionen haben keinen Prefix.

## Standardtypen
CS	Ein CString (aus der MFC)
Beispiel	CString	CSAnMFCString

CSW	Ein CStringW (Unicode-String aus der MFC)
Beispiel	CStringW	CSAnMFCUnicodeString

## Zusammengesetzte Daten und Container
a	Ein Array
Beispiel	int[]	aiAnArrayOfInts

vec	Ein Vektor vom Typ std::vector
Beispiel	vector<int>	veciAVectorField



##	Erläuternde Präfixe
m_	leitet eine Membervariable ein. D.h. die betreffende Variable gehört zu einem Objekt, das in einer Klasse/Struktur definiert wurde.
Beispiel	int	m_iAnIntValue

cl	Eine Klassendeklaration
Beispiel	class	clMyClass
Wichtig: eine Instanz einer Klasse hat kein vorangestelltes "cl". Auch der Dateiname zur Implementierung einer Klasse hat kein vorangestelltes "cl".

st	Deklaration eine Struktur
Beispiel	struct	clMyStruct
Wichtig: die Instanz einer Struktur hat kein vorangestelltes "st".


# Dokumentation der Datei-, Klassen-, Funktionsköpfe
Die Dokumentation erfolgt grundsätzlich auf englisch (american english).

## Funktionen
Funktionen werden in der Implementierungsdatei (.cpp) dokumentiert.
Jede Funktion erhält einen Dokumentationskopf. Ausnahme: Konstruktoren, Destruktoren.
1. Ein Dokumentationskopf beginnt (und enndet auch) mit:
```
//  ----------------------------------------------------------------------------------------------------
```

Die Formatierung ist so gewählt, dass sie von Doxygen ignoriert wird. Sie dient nur der visuellen Strukturierung des Sourcecodes.

2. Es folgt eine Ziele mit "\brief". Hier wird die Funktion kurz beschrieben (eine Zeile).

3. Es folgt die Beschreibung der Funktion (nur notwendig für längere Funktionen).
Sie kann über mehrere Zeilen gehen. Damit Doxygen eine Beschreibung als solche erkennt, ist vor der Beschreibung eine Leerzeile (besteht nur aus ///) einzfügen.
Die Beschreibung wird ebenfalls mit einer Leerzeile beendet (wiederum mit ///).

4. Es kommt der Verfasser des Codes mit der \author Anweisung. KI-Generierter Code trägt hier "ChatGPT", "Claude", ... ein.

5. Es folgt das Datum, an dem der Code geschrieben wurde mit der \date Anweisung. Das Datum wird in angloamerikanischer Schreibweise eingetragen: MM/DD/YYYY. Nach einem Tab folgt wiederun das Kürzel des Autors, sowie das Wort "Start".
Änderungen am Code fügen (VOR der letzten Zeile mit einer \date Anweisung - d.h. Neueste zuoberst) eine weitere \date Zeile ein, mit Datum der Änderung, Autorenkürzel und Kurzbeschreibung der Änderung.

6. Nach einer Leerzeile folgen die Parameter für die Funktion mit der \param Anweisung.

7. Es folgt der Rückgabewert der Funktion mit der \return Anweisung.

Die Zeilen zu den Position 2., 3., 4., 5. beginnen mit /// damit Doxygen diese als Dokumentationszeilen erkennt.

Beispiel:
```
//  ----------------------------------------------------------------------------------------------------
/// \brief  return the EB box from the database by the given MAC address. If there is no such entry it will be created
///
///	This is the function description. This text here serves only as an example.
///
/// \author AGS
///	\date	01/30/2025  AGS Start
///
///	\param	iValue1	First value for the function
///	\param	sText1	Example for text for the function
///	\return	0	ok, !0 nok
//  ----------------------------------------------------------------------------------------------------
```

## Klassen
Der Dokumentationsblock für eine Klasse steht in der Header (.h)-Datei. Er steht vor dem "class" Schlüsselwort.

1. Ein Dokumentationskopf für Klassen beginnt (und enndet auch) mit:
```
//  ****************************************************************************************************
```

Weitere Erläuterungen siehe unter Dokumentation zu Funktionsköpfen

2. Es folgt eine \brief Anweisung mit einer Kurzbeschreibung der Klasse.

3. Analog zu den Funktionsköpfen (siehe dort) kann ein Beschreibungsblock folgen.
`
Beispiel:
```Doxygen
//  ****************************************************************************************************
///  @brief   represents a record set in a SQL table
//  ****************************************************************************************************
```

## Dateien
Jede Implementierungsdatei (.cpp) erhält zu Beginn eine kurze Dokumentation:

1. Ein Dokumentationskopf für Dateien beginnt (und endet auch) mit:
```
//  ****************************************************************************************************
```

2.	Es folgt ein Copyright-Hinweis mit der \copyright Anweisung. I.d.R. ist dies "Agent Smith, Dresden, Germany". In der Folgezeile "www.agent-smith.dev".

3.	Es folgt eine Beschreibungsblock (siehe Funktionen). Diesen Block gibt es immer. Er besteht mindestens aus der Zeile "Initial Code by `Namenskürzel des Autors`, `Jahr in dem die Datei begonnen wurde`".

```Doxygen
// *******************************************************************************
///	\copyright  Agent Smith, Dresden Germany
///             www.agent-smith.dev
///
///  Initial code by AGS, 2025
///
//  *******************************************************************************
```



# Programmiergrundsätze

## Über return statements
Jede Funktion hat EINEN Eingang (Funktionskopf) und EINEN Ausgang (return-Anweisung am Ende). Es gibt nicht mehrere return-Anweisungen. Auch void Funktionen werden mit einem return; abgeschlossen.

Wenn eine Funktion den Inhalt einer externenVariablen verändert, dann wird die Funktion mit einem Pointer auf die Variable aufgerufen. Verändert sie den Wert nicht, so erfolgt der Aufruf via call by reference.
Als Faustregel lässt sich sagen: call by reference immer nur mit const.

Warum?	So sieht der Programmierer bereits dem Aufruf einer Funktion an, welche Variablen modifiziert werden.
```cpp
int	iMyVar=5;
CallMyFuncThatModifies(&iMyVar);
CallMyFuncThatDoesNotModify(iMyVar);

void CallMyFuncThatModifies (int*	piMyVar)
{
 	*piMyVar=6;
 	return;
}

void CallMyFuncThatDoesNotModify (int&	riMyVar)
{
 	int	iMyLocalVar;
 	iMyLocalVar=iMyVar;
 	return;
}
```