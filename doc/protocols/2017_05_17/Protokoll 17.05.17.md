# Protokoll 17.05.17  

 ## Themen:  
- Main Controller Design  
- Puck Objekte FSM Design  
- Interrupt Pulse Msg ? Wie? Objekt?  
- Anforderung  

### Anforderung

Beim Inbetriebnahme der Anlagen müssen die Anlagen leer und alle Knöpfe rausgezogen sein.

Höhenmesswert wird als Höchster gemessener Wert definiert.

Puck-Übergabe wird immer mit der Geschwindigkeit _slow_ auf beiden Bändern durchgeführt.

### ISR Objektorientiert
Das bestehende ISR-Programm soll objektorientiert machen. Ein UML-Diagramm
liegt in dem UML Ordner
__Verantwortilchkeit: Denis__

### Puck Objekte FSM-Design
Die Pucks haben folgende Typen:
- normal
- flipped
- invalid
- BitCoded
 * bei diesem Typ wird das Bitpattern mit abgespeichert
__

Signale werden in das RDD eingetragen
Es sind Klassendiagramme,die FSM und Sequenzdiagramme für die Puckübergabe zu dokumentieren und zu implementieren.

__Verantwortlichkeit: Matthis, Jonas__

### MainController
Der MainController wird in mehrere Klassen aufgeteilt. Siehe Klassendiagramm.
__Verantwortlichkeit für MainController, Recorder, PulseMessageWrapper : Rene__
__Verantwortlichkeit für PuckManager und PuckSort(FSM) : Stephan__


