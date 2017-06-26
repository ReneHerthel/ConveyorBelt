# Protokoll 1
## Themen
* Teamorgansisation
  * Verantwortlichkeiten
  * Absprachen
  * Repository
* Arbeitspakete

Anwesende:		Alle
Abwesende:		-
Start: 			08:48 Uhr 	
Ende: 			11:00 Uhr
Protokollant: 	Matthis
Moderator:		Sebastian

## Teamorgansisation

### Verantwortlichkeiten
Wir werden Scrum benutzen.

	Produktowner: Sebastian
		Sorgt für den Informationsfluss
	Scrummaster: Jonas
		behält den Roten Faden im Auge
	Team: Der Rest

Protokollant und Moderator werden bei den wöchentlichen Treffen rotierned wechseln.

Latex wurde als Dokumentaionstool festgelegt.		
		MikTex als Packege 		--> (alle) runterladen

Latexverantwortlicher: Stephan
Repositoryverantwortlicher: René

Es wird immer min. ein Teammitglied das Tutorium besuchen. (Sebastian)
organisiert. Es wird ein wöchentlicher Bericht aus dem Tutorium geben.

### Absprachen:
	Jour Fixe wird auf Mittwochs, 8:30 bis (max) 12:00 Uhr festgelegt.
	Wichtige Absprachen sind über Skype zu treffen.
	Toolchain:
		UML Tool: Umlet14.2 stand alone
		IDE: Momentics 5.01 (im Labor vorhanden)
		Dokumentaion: MikTex
	Coding Style:
		keine \n für {
		Camelcase für Variablennamen vergabe
		Für Konstanten mit ALLCAPS Snakecase (gilt auch für ENUMs)
		Doxygen
		Kommentar auf Englisch
		EP02_coding bis zum 5.4.17 lesen --> alle
	Das Protokoll des Jour Fixe soll spätestens am Folgetag online im Repo sein
	Die Milestones und Tasks Funktion von GitHub wird verwendet --> René eintragen

	Design for testabilties

### Git Repository

Das Repository wird bei GitHub geführt.

#### Regeln

* Keine Binaries einchecken
* keine PDFs

#### Ordnerstruktur
* doc
  * rdd
  * Uml
  * Protocol
    * Protocol_1
* sourceFolder

Es wird ein einfaches feature branching ohne continius integration als
git flow gewählt. Nur fertige, ausführbare Programme (features) auf dem
Master Branch

#### GIT-FLOW

1. erst auf eigenen Branch vom Master pullen
2. nur auf eigenem Branch arbeiten bis das feature fertig ist
3. nur vom Master Branch pullen, aber nicht auf ihn pushen
4. wenn das Feature fertig ist großen Merge auf dem eigenen Branch machen
5. dann auf den Master Branch pushen

## Arbeitpakete

Was|Wer|DoD|Bis Wann
---|---|---|--------
Tex Templates|Stephan|Template für Protokoll|
||Template für rdd|30.03.17
Toolchain|alle|Programme bestimmen|done
Repository Organisation|René|siehe Punkt 3|30.03.17
IDE|Matthis|Projekt Einrichtung|31.03.17
||Code auf Geme Box|
||Einstellungen in der IDE dokumentieren|
Systemkontext Diagramm|Jonas|Zu diesem Zeitpunkt vollständiges Diagramm|31.03.17
Komponenten Diagramm|Jonas|Zu diesem Zeitpunkt vollständiges Diagramm|31.03.17
Interface Design|Sebastian|Es lassen sich alle Signale wieder finden|31.03.17
Test Konzept|Sebastian|Schriftliche Ausarbeitung|31.03.17
Requirements|Dennis|im RDD eingetragen mit ID|31.03.17
Use Cases|Dennis|im RDD eingetragen mit ID|31.03.17
Ampel Steuerung|Matthis, Stephan|State Maschine modelieren|05.04.17
|||Boundery class
|||QNX Timer
