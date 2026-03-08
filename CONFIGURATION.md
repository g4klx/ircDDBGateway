# ircDDBGateway Configuration Reference

> **Note:** The config parser treats any line beginning with `#` as a
> comment, and blank lines are skipped. Use `ircddbgateway.example` as
> your starting point for a clean config.

**Config file location:** `/etc/ircddbgateway`
(or `/etc/ircddbgateway_<name>` when using the `-name` command line option)

**Format:** `key=value` — one setting per line, no spaces around the `=`.
Boolean values use `0` for off/false and `1` for on/true.

---

## Gateway Settings

| Setting | Default | Description |
|---------|---------|-------------|
| `gatewayType=0` | `0` | Gateway type — see [Gateway Types](#gateway-types) below. |
| `gatewayCallsign=` | *(empty)* | Gateway callsign, padded to 8 characters (e.g. `GB7XX  G`). The final character is always `G` for gateway. |
| `gatewayAddress=` | *(empty)* | IP address to bind for gateway services. Leave empty for automatic. |
| `icomAddress=172.16.0.20` | `172.16.0.20` | Local IP address for Icom repeater stack communication. |
| `icomPort=20000` | `20000` | UDP port for Icom repeater stack communication. |
| `hbAddress=127.0.0.1` | `127.0.0.1` | IP address of the homebrew repeater (DStarRepeater). |
| `hbPort=20010` | `20010` | UDP port for homebrew repeater communication. |
| `latitude=0.000000` | `0.0` | Gateway latitude in decimal degrees (positive = North). |
| `longitude=0.000000` | `0.0` | Gateway longitude in decimal degrees (positive = East). |
| `description1=` | *(empty)* | First line of the gateway description (shown on reflector dashboards). |
| `description2=` | *(empty)* | Second line of the gateway description. |
| `url=` | *(empty)* | URL for the gateway (shown on reflector dashboards). |

### Gateway Types

| Value | Type | Description |
|:-----:|------|-------------|
| `0` | Repeater | Standard repeater gateway |
| `1` | Hotspot | Personal hotspot gateway |
| `2` | Dongle | DV Dongle/AMBE dongle gateway |
| `3` | STARnet | STARnet-only server (no repeater) |

---

## Repeater Settings (1–4)

Up to four repeater modules can be configured. Each module uses a numeric suffix (`1` through `4`). The settings below show the suffix `1` — replace with `2`, `3`, or `4` for additional modules.

| Setting | Default | Description |
|---------|---------|-------------|
| `repeaterCall1=` | *(empty)* | Repeater callsign, 7 characters (e.g. `GB7XX`). Leave empty to disable this module. |
| `repeaterBand1= ` | ` ` *(space)* | Module letter (`A`, `B`, `C`, `D`, or `E`). Combined with callsign to form the 8-character repeater ID (e.g. `GB7XX  B`). |
| `repeaterType1=0` | `0` | Repeater hardware type — see [Hardware Types](#hardware-types) below. |
| `repeaterAddress1=127.0.0.1` | `127.0.0.1` | IP address of the repeater hardware or DStarRepeater instance. |
| `repeaterPort1=20011` | `20011` | UDP port for repeater communication. Default ports are 20011–20014 for modules 1–4. |
| `reflector1=` | *(empty)* | Default reflector to link at startup (e.g. `REF001 C` or `XRF012 A`). |
| `atStartup1=0` | `0` | `1` = link to the default reflector at startup. |
| `reconnect1=0` | `0` | Reconnect behaviour — see [Reconnect Values](#reconnect-values) below. |
| `frequency1=0.00000` | `0.0` | Operating frequency in MHz (e.g. `438.50000`). Reported to reflector directories. |
| `offset1=0.0000` | `0.0` | Repeater offset in MHz (e.g. `-7.6000`). |
| `rangeKms1=0.000` | `0.0` | Coverage range in kilometres. |
| `latitude1=0.000000` | `0.0` | Repeater latitude in decimal degrees. |
| `longitude1=0.000000` | `0.0` | Repeater longitude in decimal degrees. |
| `agl1=0.000` | `0.0` | Antenna height above ground level in metres. |
| `description1_1=` | *(empty)* | First line of the repeater module description. |
| `description1_2=` | *(empty)* | Second line of the repeater module description. |
| `url1=` | *(empty)* | URL for this repeater module. |
| `band1_1=0` | `0` | Band data byte 1 (used by Icom stacks). |
| `band1_2=0` | `0` | Band data byte 2. |
| `band1_3=0` | `0` | Band data byte 3. |

### Hardware Types

| Value | Type | Description |
|:-----:|------|-------------|
| `0` | Homebrew | DStarRepeater-based homebrew repeater |
| `1` | Icom | Icom ID-RP2C repeater stack |
| `2` | Dummy | Dummy/test repeater (no hardware) |

### Reconnect Values

| Value | Behaviour |
|:-----:|-----------|
| `0` | Never — once unlinked, stay unlinked |
| `1` | Fixed — reconnect immediately to the default reflector |
| `2` | After 5 minutes |
| `3` | After 10 minutes |
| `4` | After 15 minutes |
| `5` | After 20 minutes |
| `6` | After 25 minutes |
| `7` | After 30 minutes |
| `8` | After 60 minutes |
| `9` | After 90 minutes |
| `10` | After 120 minutes |
| `11` | After 180 minutes |

---

## ircDDB Network Settings (1–4)

Up to four ircDDB networks can be configured simultaneously. Networks 1 and 2 are enabled by default. The settings below show network `1` — networks 2–4 use `2`, `3`, or `4` appended to the key names (e.g. `ircddbHostname2`).

> **Note:** Network 1 uses key names without a numeric suffix (e.g.
> `ircddbHostname` not `ircddbHostname1`).

| Setting | Default | Description |
|---------|---------|-------------|
| `ircddbEnabled=1` | `1` (nets 1–2), `0` (nets 3–4) | `1` = enable this ircDDB network. |
| `ircddbHostname=group1-irc.ircddb.net` | `group1-irc.ircddb.net` (net 1), `rr.openquad.net` (net 2), *(empty)* (nets 3–4) | Hostname of the ircDDB server. |
| `ircddbUsername=` | *(empty)* | Username for ircDDB authentication (usually your callsign). |
| `ircddbPassword=` | *(empty)* | Password for ircDDB authentication. |

---

## Protocol and Service Settings

| Setting | Default | Description |
|---------|---------|-------------|
| `aprsEnabled=0` | `0` | `1` = enable DPRS-to-APRS-IS gateway. Requires an APRS-IS connection. |
| `dextraEnabled=1` | `1` | `1` = enable DExtra (XRF) reflector protocol. |
| `dextraMaxDongles=5` | `5` | Maximum number of DExtra dongle connections allowed. |
| `dplusEnabled=0` | `0` | `1` = enable D-Plus (REF) reflector protocol. Requires registration. |
| `dplusMaxDongles=5` | `5` | Maximum number of D-Plus dongle connections allowed. |
| `dplusLogin=` | *(empty)* | Callsign for D-Plus authentication. Must be registered with US Trust. |
| `dcsEnabled=1` | `1` | `1` = enable DCS reflector protocol. |
| `ccsEnabled=1` | `1` | `1` = enable CCS7 call routing. |
| `ccsHost=CCS704  ` | `CCS704  ` | CCS server callsign (8 characters, space-padded). |
| `xlxEnabled=1` | `1` | `1` = enable XLX reflector protocol. |
| `xlxHostsFileUrl=...` | `http://xlxapi.rlx.lu/api.php?do=GetXLXDMRMaster` | URL to download the XLX hosts list. |

---

## STARnet Settings (1–5)

Up to five STARnet digital voice groups can be configured. Each group uses a numeric suffix (`1` through `5`).

| Setting | Default | Description |
|---------|---------|-------------|
| `starNetBand1=` | *(empty)* | Module letter for this STARnet group (e.g. `A`). Leave empty to disable. |
| `starNetCallsign1=` | *(empty)* | Callsign for the STARnet group (8 characters, e.g. `STN001 L`). |
| `starNetLogoff1=` | *(empty)* | Callsign to send to log off from the group. |
| `starNetInfo1=` | *(empty)* | Info text for the group. |
| `starNetPermanent1=` | *(empty)* | Comma-separated list of callsigns permanently subscribed to the group. |
| `starNetUserTimeout1=300` | `300` | User inactivity timeout in seconds. Users are removed from the group after this period. |
| `starNetGroupTimeout1=300` | `300` | Group inactivity timeout in seconds. The group is deactivated after this period. |
| `starNetCallsignSwitch1=0` | `0` | Callsign display mode — see [Callsign Switch Values](#callsign-switch-values) below. |
| `starNetTXMsgSwitch1=1` | `1` | `1` = transmit group status messages. |
| `starNetReflector1=` | *(empty)* | Reflector to link the STARnet group to (DExtra protocol). |

### Callsign Switch Values

| Value | Mode | Description |
|:-----:|------|-------------|
| `0` | Group Callsign | Show the group callsign in headers |
| `1` | User Callsign | Show the originating user's callsign in headers |

---

## Remote Control

| Setting | Default | Description |
|---------|---------|-------------|
| `remoteEnabled=0` | `0` | `1` = enable the remote control interface. |
| `remotePassword=` | *(empty)* | Password for remote control authentication. |
| `remotePort=0` | `0` | UDP port for remote control. `0` = disabled. |

---

## Miscellaneous

| Setting | Default | Description |
|---------|---------|-------------|
| `language=0` | `0` | Language for voice announcements — see [Language Values](#language-values) below. |
| `infoEnabled=1` | `1` | `1` = enable the `I` (info) callsign command. |
| `echoEnabled=1` | `1` | `1` = enable the echo (parrot) test feature. |
| `logEnabled=0` | `0` | `1` = enable logging to file. |
| `dratsEnabled=0` | `0` | `1` = enable D-RATS data transfer support. |
| `dtmfEnabled=1` | `1` | `1` = enable DTMF command decoding. |

### Language Values

| Value | Language |
|:-----:|----------|
| `0` | English (UK) |
| `1` | Deutsch |
| `2` | Dansk |
| `3` | Francais |
| `4` | Italiano |
| `5` | Polski |
| `6` | English (US) |
| `7` | Espanol |
| `8` | Svenska |
| `9` | Nederlands (NL) |
| `10` | Nederlands (BE) |
| `11` | Norsk |
| `12` | Portugues |

---

## GPSD Settings

| Setting | Default | Description |
|---------|---------|-------------|
| `gpsdEnabled=0` | `0` | `1` = enable GPSD support for automatic position updates. |
| `gpsdAddress=127.0.0.1` | `127.0.0.1` | GPSD server address. |
| `gpsdPort=2947` | `2947` | GPSD server port. |

---

## MQTT Settings

*MQTT is always compiled in. To disable at runtime, leave `mqttAddress` empty. See [MQTT.md](MQTT.md) for full details on topics, JSON format, and troubleshooting.*

| Setting | Default | Description |
|---------|---------|-------------|
| `mqttAddress=127.0.0.1` | `127.0.0.1` | MQTT broker hostname or IP address. Set to empty to disable MQTT at runtime even when compiled in. |
| `mqttPort=1883` | `1883` | MQTT broker port. |
| `mqttKeepalive=60` | `60` | Keepalive interval in seconds. |
| `mqttAuth=0` | `0` | `1` = authenticate with the broker using `mqttUsername` and `mqttPassword`. |
| `mqttUsername=mmdvm` | `mmdvm` | Broker username (when `mqttAuth=1`). |
| `mqttPassword=mmdvm` | `mmdvm` | Broker password (when `mqttAuth=1`). |
| `mqttName=ircddb-gateway` | `ircddb-gateway` | Client name and topic prefix for all published messages. |

### MQTT Topics

With the default `mqttName` of `ircddb-gateway`, the following topics are published:

| Topic | Content |
|-------|---------|
| `ircddb-gateway/log` | Timestamped log messages. |
| `ircddb-gateway/json` | JSON link status events (linking, unlinking, relinking, failed, status). |
| `ircddb-gateway/aprs-gateway/aprs` | APRS position data from the DPRS gateway. |

---

## Window Position (GUI only)

| Setting | Default | Description |
|---------|---------|-------------|
| `windowX=-1` | `-1` | Window X position. `-1` for system default. |
| `windowY=-1` | `-1` | Window Y position. `-1` for system default. |

---

# Companion Program Configuration

The following companion programs have their own separate config files.
The same `key=value` format and comment rules apply. Example configs
are provided in `linux/`.

---

## TimeServer

**Config file:** `/etc/timeserver`
(or `/etc/timeserver_<name>` when using the `-name` option)

**Example:** [linux/timeserver.example](linux/timeserver.example)

The TimeServer transmits time announcements to one or more repeater modules at a configurable interval.

| Setting | Default | Description |
|---------|---------|-------------|
| `callsign=` | *(empty)* | Gateway callsign (8 characters, e.g. `GB7XX  G`). |
| `sendA=0` | `0` | `1` = send time announcements to module A. |
| `sendB=0` | `0` | `1` = send time announcements to module B. |
| `sendC=0` | `0` | `1` = send time announcements to module C. |
| `sendD=0` | `0` | `1` = send time announcements to module D. |
| `sendE=0` | `0` | `1` = send time announcements to module E. |
| `address=127.0.0.1` | `127.0.0.1` | Address of the ircDDBGateway instance. |
| `language=0` | `0` | Announcement language — see [TimeServer Language Values](#timeserver-language-values) below. |
| `format=0` | `0` | Announcement format — see [Format Values](#format-values) below. |
| `interval=0` | `0` | Announcement interval — see [Interval Values](#interval-values) below. |
| `windowX=-1` | `-1` | Window X position (GUI only). |
| `windowY=-1` | `-1` | Window Y position (GUI only). |

### TimeServer Language Values

| Value | Language |
|:-----:|----------|
| `0` | English (UK) 1 |
| `1` | English (UK) 2 |
| `2` | English (US) 1 |
| `3` | English (US) 2 |
| `4` | Deutsch 1 |
| `5` | Deutsch 2 |
| `6` | Francais |
| `7` | Nederlands |
| `8` | Svenska |
| `9` | Espanol |
| `10` | Norsk |
| `11` | Portugues |

### Format Values

| Value | Format | Description |
|:-----:|--------|-------------|
| `0` | Voice Time | Voice announcement of the current time |
| `1` | Voice All | Voice announcement of time, date, and location |
| `2` | Text Time | Slow-data text with the current time |

### Interval Values

| Value | Interval |
|:-----:|----------|
| `0` | Every 15 minutes |
| `1` | Every 30 minutes |
| `2` | Every 60 minutes |

---

## TimerControl

**Config file:** `/etc/timercontrol`
(or `/etc/timercontrol_<name>` when using the `-name` option)

**Example:** [linux/timercontrol.example](linux/timercontrol.example)

TimerControl provides scheduled reflector linking — automatically linking and unlinking repeater modules at configured times.

| Setting | Default | Description |
|---------|---------|-------------|
| `address=` | *(empty)* | Address of the ircDDBGateway remote control interface. |
| `port=0` | `0` | Port of the ircDDBGateway remote control interface. Must match `remotePort` in the gateway config. |
| `password=` | *(empty)* | Password for the remote control interface. Must match `remotePassword` in the gateway config. |
| `delay=0` | `0` | `1` = delay scheduled actions by a random amount to avoid all repeaters acting simultaneously. |
| `windowX=-1` | `-1` | Window X position (GUI only). |
| `windowY=-1` | `-1` | Window Y position (GUI only). |

---

## Programs Without Config Files

The following companion programs take their parameters entirely from
command line arguments and do not use config files:

| Program | Description |
|---------|-------------|
| `texttransmit` | Sends a slow-data text message to a repeater module. |
| `voicetransmit` | Sends a voice announcement file to a repeater module. |
| `aprstransmit` | Sends APRS data to the gateway. |
| `remotecontrol` | GUI remote control client (uses wxWidgets config storage, not a text file). |
