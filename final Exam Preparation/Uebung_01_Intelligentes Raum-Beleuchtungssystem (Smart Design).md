# Szenario

In einem modernen Bürogebäude sollen mehrere Räume mit einem intelligenten Beleuchtungssystem ausgestattet werden. Ziel ist es, eine energieeffiziente und benutzerfreundliche Lösung zu entwickeln, die sowohl automatisch als auch manuell gesteuert werden kann.

Die Nutzerinnen und Nutzer sollen nicht aktiv eingreifen müssen, wenn ausreichend Licht vorhanden ist oder sich niemand im Raum befindet. Gleichzeitig soll jederzeit eine manuelle Steuerung möglich sein.

Jeder Raum wird von einem anderen Entwickler programmiert. Die beste Umsetzung soll anschließend für alle Räume übernommen werden.

## Hardware eines Raums

- eine LED zur Simulation der Beleuchtung
- einen Bewegungssensor (im Prototyp durch einen Taster ersetzt)
- einen Helligkeitssensor (im Prototyp durch ein Potentiometer ersetzt)
- einen weiteren Taster zur manuellen Steuerung
- ein OLED-Display zur Anzeige von Zuständen

Die Daten werden über MQTT an eine Zentrale gesendet. Die Auswertung der Daten ist nicht Teil der Aufgabe.

## Funktionsbeschreibung

### Automatikbetrieb

- Der Sensor erkennt eine Bewegung.
- Ist die Umgebungshelligkeit zu gering, wird das Licht eingeschaltet.
- Wenn keine Bewegung mehr erkannt wird, bleibt das Licht noch für 5 Sekunden eingeschaltet und wird danach automatisch ausgeschaltet.
- Ist die Umgebungshelligkeit ausreichend hoch, bleibt das Licht trotz Bewegung ausgeschaltet.

### Manueller Betrieb

- Über einen Taster kann das Licht unabhängig vom Automatikbetrieb ein- und ausgeschaltet werden.
- Der manuelle Betrieb hat Vorrang vor dem Automatikbetrieb.

### Anzeige (OLED-Display)

Auf dem Display sollen folgende Informationen dargestellt werden:

- Zustand des Lichts (AN / AUS)
- aktueller Modus (Automatik / Manuell)
- Helligkeitswert in Prozent

### Störung

Über einen zusätzlichen Taster wird eine Störung simuliert.

- Beim Drücken des Tasters: wird eine rote LED eingeschaltet und eine Nachricht an den MQTT-Broker gesendet
- Beim erneuten Drücken: wird die LED ausgeschaltet und eine weitere Nachricht gesendet

### Erfassung von Sensorwerten

Folgende Werte sollen an die Zentrale über MQTT gesendet werden:

- Helligkeit
- Bewegungsstatus
- Lichtstatus
- Modus (Automatik / Manuell)
- Fehlerstatus

**Topics (Beispiele):**

- `Raum1/Licht` = ON / OFF
- `Raum1/Helligkeit` = 70
- `Raum1/Bewegung` = True / False
- `Raum1/Modus` = Auto / Manuell
- `Raum1/Fehler` = True / False

## Aufgabenstellung

### Aufgabe 1: (30 Punkte)
Erstellen Sie einen Programmablaufplan (PAP) zu diesem Szenario.

### Aufgabe 2: (15 Punkte)
Bauen Sie die benötigte Hardware auf.

### Aufgabe 3: (40 Punkte)
Realisieren Sie die Software für das beschriebene System.

### Aufgabe 4: (15 Punkte)
Erstellen Sie eine Testliste und dokumentieren Sie die durchgeführten Tests.
