# MeshCom 4.0 Firmware
MeshCom is a project to exchange text messages via LORA radio modules. The primary goal is to realize networked off-grid messaging with low power and low cost hardware.

The technical approach is based on the use of LORA radio modules which transmit messages, positions, measured values, telecontrol and much more with low transmission power over long distances. MeshCom modules can be combined to form a mesh network, but can also be connected to a message network via MeshCom gateways, which are ideally connected via HAMNET. This enables MeshCom radio networks, which are not connected to each other via radio, to communicate with each other.

MeshCom is indeed an exciting project of the Institute of Citizen Science for Space & Wireless communication (www.icssw.org)  aimed at creating a resilient, text-based communication tool for amateur radio operators. It utilizes LORA™ modulation technology and the APRS protocol to establish a mesh network in the 70cm band Amateur band. The main objectives of MeshCom are to realize a roubust off-grid messaging system with low energy consumption and cost-effective hardware. The technical implementation is based on LORA™  radio modules, which can transmit messages, positions, measurements, and more over long distances with low transmit power. MeshCom modules can be connected to form a mesh network or establish a messaging network via MeshCom gateways, ideally connected through HAMNET.
Basic functions:
•	Each Node is identified by a Amateur Radio Callsign (with optional SSID)
•	Short test messages can be sent to ALL (everybody), with ACK from Server/Gateway
•	Short text messages can be sent DIRECTLY to other Callsign, with End-toEnd Aknowledgement
•	Some Nodes can als be to configured to act as GATEWAY to HAMNET or INTERNET (wifi)
•	Each Node should act as a repeater for all other MESHCOM messages on air
•	Servers and Gateways might have some functionalities to avoid the transmission of redundant trafic
•	Nodes will automatically send STATUS and POSITION messages
•	NODES with optional Sensors will send WX-Data or TELEMETRY Data periodically
•	Messages will be diplayed on small OLED Display or via BT connected smartphone or tablet device or via USB connected serial console

The main goal is to have a selfbuilding and selfhealing Mesh-Network, that can be enhanced by other components of the Amateur Radio Service, like HAMNET (IP-Network), centralised or distributed Meshcom servers. This will increase coverage to all continents and enable interconnection to other modes and services (APRS, WINLINK, DMR, TETRA-SDS, SOTA-WATCH, POCSAG,VARA-AC, …) building an unified communication plattform.
Particulary useful is Meshcom for Emergency Communication (EMCOM) in case of disaster or Blackout.
In all usecases terms  and rules of Amateur Radio Service (strictly non commercial, experimental) should be respected.
This is an open Citizen Science project that should help to promote Amateur Radio Service within academic and society.

Frequency used per Region: 
EU: 433.175
UK: tbd
Nordic: tbd
USA: 433.175
Afrika: 433.175
Asia/Pacific: tbd

Lora parameter:
SF: 11
Bandwith: 250kHz
CR: 4/6



# MeshCom Protocol
MeshCom 4.0 uses the APRS PROTOCOL REFERENCE for the source, destination, Digipeater and payload data as defined for APRS. (aprs101.pdf APRS PROTOCOL REFERENCE Version 1.0 2000, Page 12)
MeshCom 4.0 verwendet für die Payload-Daten das AX.25 Protokoll, wie es für APRS definiert ist. (aprs101.pdf APRS PROTOCOL REFERENCE Version 1.0 2000, Seite 12)

Verwendung finden:
- Kennung — APRS-Datentyp-Identifikator
- Meldungs-ID – 32-Bit LSB->MSB eindeutiger Wert
- MAX-HOP – max. 7  (Maske 0x07) default wird 5 verwendet was weitere 4 Weitergaben ermöglicht.
- 0x80 – Kennung ob diese Meldung bereits via MQTT-Server gelaufen ist
- 0x40 – Kennung das diese Meldung pro MeshClient mit dem Rufzeichen der weitergebenden Station ergänzt werden soll. Für Mess- und Kontrollzwecke.
- Quelladresse — Dieses Feld enthält das Rufzeichen und die SSID der Sendestation
- Zieladresse — Dieses Feld kann ein APRS-Ziel enthalten Rufzeichen oder „*“ für Übertragungen an ALLE.
- Digipeater — Es können 0 bis 8 Digipeater-Rufzeichen in diesem Feld enthalten sein. Hinweis: Diese Digipeater-Adressen können durch einen generischen APRS-Digipeater-Pfad überschrieben werden (angegeben durch die SSID der  Zieladresse).
- Information – Dieses Feld enthält Transportdaten. Das erste Zeichen dieses Feldes ist der APRS-Datentyp-Identifikator, der angibt welche Art von Daten folgen.
- Hardware-ID
- Modulations-ID
- Frame Check Sequence – Der FCS ist eine Sequenz von 16 Bits, die verwendet wird um die Integrität eines empfangenen Rahmens zu überprüfen.

Meldungen:
- Textmeldungen:
  - :|!MMMMMMMM|!HH|OE0XXX-99|>*|:|Text-Meldung|!00|!HW|!MOD|FCS#
- Textmeldungen mit Path aus Mesh:
   - :|!MMMMMMMM|!HH|OE0XXX-99,OE3XXX-12,OE3YYY-12|>*|:|Text-Meldung|!00|!HW|!MOD|FCS#
- Positionsmeldungen:
   - !|!MMMMMMMM|!HH|OE0XXX-99|>*|!|4800.00|N|/|01600.00|E|#| BBB /A=HHHH|!00|!HW|!MOD|FCS#
- Legende:
  - | … dient nur zur Darstellung der Trennungen hier im Text

Meldungselemente
- Medlungskennung : ! @ ... Text-, Positions-, Wetter-Meldung
- MMMMMMMM	Meldungs-ID	32-Bit LSB->MSB
- HH	MAX-HOP	8-Bit Bit-Maske 0x07
- Message via MQTT-Server	Bit-Maske 0x80
- Path im Mesh einfügen (mit Beistrich als Trennung)	Bit-Maske 0x40
- 4800.00	Latitude	Grad/dezimal x 100
- 01600.00	Longidude	Grad/dezimal x 100
- N	N ord / S üd	char
- /	APRS SYMBOL Gruppe (/ oder \)	char
- E	E ast / W est	char
- \#	APRS SYMBOL	char
- BBB	Akkuzustand in %	int 0 - 100
- /A=HHHH	GPS Meereshöhe (m)	int 0 - 9999
- Meldungsabschluss	schließt den APRS-Meldungsbereich ab	0x00
- HW ... Hardware-Type ID
- MOD ... LoRa-Modulation ID
- FCS#	Prüfsumme inkl. Kennung und 0x00 vom Meldungsabschluss	unsigned int 16-Bit
- GGGGGGGG	Gateway-ID (nur für MeshCom 2.0 Kompatibilität)	32-Bit LSB->MSB
- HW	Hardware-ID	8-Bit (siehe Tabelle)

MeshCom Hardware

- Hardware-ID	HW-Type	MCU-Type	LoRa-Type	HW-Kurzbezeichnung	HW-Version
- 1	TTGO ESP32-Paxcounter	ESP32	SX1278	TLORA	V2
- 2	TTGO ESP32-Paxcounter	ESP32	SX1278	TLORA	V1
- 3	TTGO ESP32-Paxcounter	ESP32	SX1278	TLORA	V2 1.6
- 4	TTGO T-Beam	ESP32	SX1278	T-BEAM	1.1
- 5	TTGO T-Beam	ESP32	SX1268	T-BEAM-1268	1.1 1268
- 6	TTGO T-Beam	ESP32	SX1262	T-BEAM-0.7	0.7
- 7	T-Echo LoRa SX1262	nRF	SX1262	T-ECHO	
- 8	T-Deck	ESP32-S3	SX1262	T-DECK	
- 9	Wisblock RAK4631	nRF	Wisblock nRF	RAK4631	
- 10	WiFi LoRa 32 v2	ESP32	SX1262	HELTEC-V2-1	V2
- 11	WiFi LoRa 32 v1	ESP32	SX1276	HELTEC-V1	V1
- 12	TTGO T-Beam	ESP32	SX1278	TBEAM-AXP2101	
- 39	Ebyte Lora E22	ESP32	SX1278	EBYTE-E22	
- 43	WiFi LoRa 32 v3	ESP32-S3	SX1262	HELTEC-V3	V3

MeshCom Modulationen

- 0	Erweiterter Bereich	10-20	schnell	
- 1	Erweiterter Bereich	10-20	langsam (robust)	0.275 kbps
- 2	Zusätzlich erweiterter Bereich	20-40	langsam (robust)	0.183 kbps
- 3	Normaler Bereich	5-10	langsam (robust)	
- 4	Normaler Bereich	5-10	schnell	5.469 kbps
- 5	Lokaler Bereich	0-5	langsam (robust)	
- 6	Lokaler Bereich	0-5	schnell	21.875 kbps
