# Protokoll 2 vom 05.04.17

## Top
* Protokoll 1
* .gitignore
* Globale Timerklasse
* EnumHeader
* Test in C++
* HAL Zuordnung
* Namespaces
* Milestones
* Debugging/ Logging
* Code Conventions
* Architektur

*Start*: 8:42 Uhr

*Ende*: 11:30 Uhr

## Protokoll 1

* Protokolle in LateX übertragen --> Matthis, Stephan
* IDEv7 Kompatibilität überprüfen -->
* Requirements und drucharbeiten --> alle
* Requirements überarbeiten, Pareigis nach extra Aufgabe fragen --> alle
* Use Cases finden --> Dennis

## HAL

Die HAL sollen in die Ordner, also keine Globale HAL.

## .gitignore

Es soll eine gitignore erstellt werden. Nur .h,.cpp,.txt,.md Datein
sollen von der Versionskontrolle erfasst werden. --> Sebastian

## Timer Klasse

* Wrapping
* PulseMessages
* Eine Methode mit übergabe einer Zeit.
* Eine Methode mit übergabe einer Distanz

## enum Header

* Extra H-Datei in den Ordnern --> alle (jeweils die Person, die eine Komponente bearbeitet)
* Ein globaler Enum-Header für Debug und Warnings

## Testen in c++

* Wird auf das nächste Treffen verschoben.
* E-Mail an Herrn Lehmann Einheit Testframework in Momentics. --> Dennis/Sebastian
* Es soll einen PowerUp Selftest geben.

## Code Conventions

* Die besprochenen Code Conventions aus Protokoll 1 sollen in das GitHub
Wiki eingetragen werden. --> done
* Abstrakte Klassen für die Boundery Klassen beginnen mit einem großen B für Base

## Namespaces

* Namespaces HAL und INTERFACE sollen benutzt werden.

## Milestones --> Rene

* Milestones sollen auf Github mit den Issues eingebunden werden.
* Neues Label Workpackeges.
* 1 Punkt pro Issue.

## Debugging/Logging

* Wird verschoben.
* Makro aus Vorlesung soll genutzt werden.

## Architektur

* Das Interface Diagramm hatte folgende Mängel die zu beheben sind.
  * Timer fehlt
  * Buttons fehlen
  * Metaldetektor nicht mit der Seriel Port sondern dem MainControl verbinden
* Es soll das Factory Pattern angewendet werden.
  * Factory Methoden müssen vom Main Controller aufgerufen werden.
  * Ein Factory Objekt pro Komponente
  * Eine Methode newInstance(Objekttyp) 

## Arbeitspakete

* Timer --> Jonas, Sebastian
* LightSystem --> Stephan
* Conveyer Belt, LED, Console --> Rene
* Light Barrier, Sorting Switch --> Dennis
* Metal Detector --> Matthis
* Main(Dispatcher) --> Sebstian
* Buttons, E-Stop --> Jonas
* Interrupts --> Jonas, Matthis, Dennis

### Dod

* UML Diagramm in einem neuen Ordner UML/Komponent
* Interface implementieren
* Baseklassen implementieren
