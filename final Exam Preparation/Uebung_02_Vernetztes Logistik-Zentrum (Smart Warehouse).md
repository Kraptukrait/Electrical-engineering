## Szenario: Vernetztes Logistik-Zentrum (Smart Warehouse)

In einem Logistikpark gibt es 5 Lagerbereiche mit einem automatischen Warenannahmesystem. Die Lieferanten haben vorab über eine Webseite Paketdaten und die zugehörige **Paket-ID** eingegeben. Die IDs werden im Prototyp manuell erfasst. Jedes Lager wird von einem anderen Programmierer realisiert. Die beste Umsetzung soll später für den gesamten Park übernommen werden.

Ein Arduino steuert sowohl die **Warenannahme** (Einfuhr) als auch den **Warenversand** (Ausfuhr).

### Vereinfachungen für den Prototyp

- Die Erfassung der Paket-IDs erfolgt über den **seriellen Monitor**.
- Anstelle der Lagerdauer in Stunden wird die Zeit in **Sekunden** gemessen.
- Sensoren werden durch einfache Hardware (Taster/Poti) ersetzt.
- Die Datenauswertung erfolgt über **MQTT** auf einem zentralen PC.

### Warenannahme (Einfuhr)

Ein Sensor (Taster) erkennt, dass ein Paket auf dem Band liegt. Die Paket-ID wird über den seriellen Monitor eingegeben. Das Tor (Servo/Schranke) öffnet sich. Wenn der Sensor kein Paket mehr erkennt, schließt das Tor 2 Sekunden später.

- Wird die ID nicht erkannt (nicht registriert), bleibt das Tor zu.
- Ist der Lagerbereich voll, darf kein Paket angenommen werden; das Tor bleibt zu. Die ID wird erst abgefragt, wenn wieder Platz frei ist.

### Warenversand (Ausfuhr)

Ein Taster simuliert den Abtransport eines Pakets. Es gibt kein Tor, aber eine **rote LED**, die leuchtet, bis der Versand freigegeben ist.

Bevor der Taster gedrückt wird, wird die Paket-ID eingegeben und erkannt. Die Lagerzeit wird gespeichert. Die rote LED geht aus und nach 3 Sekunden wieder an.

- Einfuhr und Ausfuhr geschehen nicht gleichzeitig. Während eine Annahme läuft, bleibt die rote LED der Ausfuhr an.
- Die Paket-ID und die Lagerzeit (Sekunden) werden an den MQTT-Broker gesendet.

### Erfassung Sensorwerte

Folgende Werte müssen im MQTT-Explorer sichtbar sein:

- **Luftfeuchtigkeit** (über Poti analog simulieren)
- **Helligkeit** (über LDR oder zweiten Poti)
- **Sabotage-Alarm:** Ein Taster erzeugt einen **Interrupt**
  - Nachricht an Broker senden
  - Eine **blaue LED** geht an
  - Erneuter Druck: LED aus und Nachricht an den Broker

### Anzeige OLED Display

Jeder Bereich zeigt die freien Lagerplätze aller 5 Bereiche an, den eigenen in der obersten Zeile.

**Zuweisung:** 1, 2, 3, 4, 5

**IDs:** Lx1 bis Lx5 (x = Bereichsnummer). Max. 5 Plätze pro Bereich.

### MQTT-Topics

| Topic | Wert |
| :--- | :--- |
| `Lx/frei` | Byte |
| `Sensor/Hum` | 0-100% |
| `Sensor/Alarm` | True/False |
| `Logistik/Paket` | String: "ID;Zeit" |

---

## Aufgabenstellung

### Aufgabe 1 (30 Punkte)

Erstellen Sie ein **PAP** zu diesem Szenario. Die Setup-Funktion muss die Pin-Konfigurationen und Initialisierungen enthalten.

### Aufgabe 2 (15 Punkte)

Skizzieren Sie den **Hardwareaufbau** (Schaltplan-Auszug oder Steckplan).

### Aufgabe 3 (40 Punkte)

Realisieren Sie die **Software**. Achten Sie auf die korrekte Einbindung der Bibliotheken und die MQTT-Kommunikation.

### Aufgabe 4 (15 Punkte)

Erstellen Sie eine **Testliste** mit 5 Szenarien (z.B. "Eingabe falsche ID", "Lager voll") und füllen Sie diese aus.
