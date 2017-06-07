# **Teammeeting 31.5.17**    
Zeit: 8:30 - 11:20   
Teilnehmer: Sebastian, Rene, Matthis, Stephan, Jonas, Dennis  
Moderator: Matthis  
Protokollführer: Dennis

**Themen:**
* Timer: Timer in Grundfunktionalität läuft und ist getestet
* Distancetracker: Distance-Handler(update(speed)), Tracker(update(), setDistance()), Adapter(distToTime(), timeToDist()) sollen als Singleton realisiert werden.
Zuständig: Sebastian, Dennis / Bei nötigen Veränderungen am Timer Jonas beauftragten.
* Calibration/ Startup Routine: Nötige Kalibrierungen bisher: 
DistanceTracker: Puck geflippt auflegen schnell hin und zurückfahren, dann langsam durch bis zur zweiten Anlage, Kalibrierug wie auf Band eins.   
Höhenmessung: calibration struct  
Calibration-Klasse zum Aufrufen der calibration der einzelnen Komponenten
Calibration Methoden in den Komponenten für händische Kalibrierung bis nächste Woche, eigentliche Kalibrierung vertagt.    
* Main: vertagt, da erst alle anderen Komponenten fertig sein müssen    
* Serial: Grundfunktion ist fertig, als Thread fertig machen(parallel)    
* Puck FSM: Implementiert, Problem Signale zusammenführen  
* Puckmanager: Bisher nur Grundgerüst  
* Recorder: Pulsed an Main, Sensorik zu Stubs, start recording(), stop recording(), play_recorded_data(), main parsed synchron   
 Textausgabe auf dem Terminal, Speichern als Binarydump  
struct: 
  - Time  
  - Code
  - Message   
 
* Kommunikations_Signale: 40 BIT, struct aus dem PulseWrapper verwenden. signals.h wird von Sebastian erstellt   
* Puck-Typ Definition: Makro  
* RDD: am Ende jeder sein Abschnitt  
* PulseWrapper: funktionieren nicht, falsche returns  
* Exceptions: überall wo Bibliotheken Aufrufe sind, **HAL Hardware Access Exception werfen** 
