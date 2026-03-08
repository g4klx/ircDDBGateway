# MQTT Support for ircDDBGateway

ircDDBGateway publishes log messages and link status events to an MQTT
broker, providing live telemetry for dashboards, home-automation systems,
or any MQTT client.

MQTT support is always compiled in. The `libmosquitto-dev` package is a
build dependency. To disable MQTT at runtime, leave `mqttAddress` empty
in the configuration file — no messages will be published and no
connection to the broker will be attempted.

## Building

Install `libmosquitto-dev`:

```
sudo apt-get install libmosquitto-dev
```

Then build as normal:

```
make
sudo make install
```

## Configuration

Add the following keys to your `ircddbgateway` configuration file
(the same flat key=value format used by all other settings):

```
mqttAddress=127.0.0.1
mqttPort=1883
mqttAuth=0
mqttUsername=mmdvm
mqttPassword=mmdvm
mqttKeepalive=60
mqttName=ircddb-gateway
```

| Key             | Default           | Description                                        |
|-----------------|-------------------|----------------------------------------------------|
| `mqttAddress`   | `127.0.0.1`       | MQTT broker hostname or IP address                 |
| `mqttPort`      | `1883`            | MQTT broker port                                   |
| `mqttAuth`      | `0`               | Enable authentication (`0` = off, `1` = on)        |
| `mqttUsername`   | `mmdvm`           | Username when `mqttAuth=1`                         |
| `mqttPassword`  | `mmdvm`           | Password when `mqttAuth=1`                         |
| `mqttKeepalive` | `60`              | Keepalive interval in seconds                      |
| `mqttName`      | `ircddb-gateway`  | Client name; also used as the MQTT topic prefix    |

If `mqttAddress` is left empty, MQTT is disabled at runtime even when
compiled in.

## MQTT Topics

All topics are automatically prefixed with the value of `mqttName`.
For example, with the default name `ircddb-gateway`:

### `ircddb-gateway/log`

Timestamped log messages. The format matches the log file output:

```
M: 2025-03-08 14:22:01: Starting ircDDBGateway
M: 2025-03-08 14:22:01: Callsign set to "GB7XX  G"
I: 2025-03-08 14:22:01: MQTT connected to 127.0.0.1:1883 as ircddb-gateway
M: 2025-03-08 14:22:01: Starting the ircDDB Gateway thread
```

### `ircddb-gateway/json`

Event-driven JSON messages published when link status changes. These use
the same JSON structure as [DStarGateway](https://github.com/F4FXL/DStarGateway),
making it possible to use the same dashboard code for both gateways.

All JSON messages are wrapped in a top-level object with one key. The
value is always an object containing a `timestamp` field.

#### Status Events

Published at gateway startup and shutdown:

```json
{"status":{"timestamp":"2025-03-08T14:22:01Z","message":"ircDDBGateway is starting"}}
```

```json
{"status":{"timestamp":"2025-03-08T18:00:00Z","message":"ircDDBGateway is stopping"}}
```

#### Linking Events

Published when a repeater module links to a reflector:

```json
{"link":{"timestamp":"2025-03-08T14:23:15Z","repeater":"GB7XX  B","action":"linking","reason":"network","reflector":"REF001 C","protocol":"dextra"}}
```

**Fields:**

| Field        | Description                                              |
|--------------|----------------------------------------------------------|
| `timestamp`  | ISO 8601 timestamp of the event                          |
| `repeater`   | Repeater callsign with module letter (8 chars)           |
| `action`     | `linking` — connection being established                 |
| `reason`     | `network`, `user`, or `timer` — what triggered the link  |
| `reflector`  | Reflector callsign with module letter (8 chars)          |
| `protocol`   | `dextra`, `d-plus`, `dcs`, or `ccs`                      |

#### Relinking Events

Published when a repeater re-establishes a link after a timeout:

```json
{"link":{"timestamp":"2025-03-08T14:30:00Z","repeater":"GB7XX  B","action":"relinking","reflector":"REF001 C","protocol":"ccs"}}
```

#### Unlinked Events

Published when a repeater module unlinks from a reflector:

```json
{"link":{"timestamp":"2025-03-08T14:25:00Z","repeater":"GB7XX  B","action":"unlinked","reason":"user"}}
```

**Reason values:**

| Reason    | Description                                      |
|-----------|--------------------------------------------------|
| `user`    | User-initiated unlink (DTMF or UR call command)  |
| `network` | Network disconnection or protocol error          |
| `timer`   | Inactivity or reconnect timer expired            |

#### Failed Events

Published when a link attempt fails:

```json
{"link":{"timestamp":"2025-03-08T14:24:00Z","repeater":"GB7XX  B","action":"failed"}}
```

### `ircddb-gateway/aprs-gateway/aprs`

APRS position data from the DPRS-to-APRS gateway, published as raw APRS
ASCII strings. Only present when APRS gateway functionality is enabled.

## Subscribing to MQTT Output

Use any MQTT client to subscribe. For example, with `mosquitto_sub`:

```bash
# Follow all ircDDBGateway topics:
mosquitto_sub -h 127.0.0.1 -t "ircddb-gateway/#"

# Log messages only:
mosquitto_sub -h 127.0.0.1 -t "ircddb-gateway/log"

# Link status events only:
mosquitto_sub -h 127.0.0.1 -t "ircddb-gateway/json"

# Pretty-print link events with jq:
mosquitto_sub -h 127.0.0.1 -t "ircddb-gateway/json" | jq .
```

## Comparison with DStarGateway and MMDVMHost

This implementation follows the same conventions as the wider MMDVM
ecosystem:

- Same `CMQTTConnection` class wrapping `libmosquitto`
- Same topic-prefix convention (`{name}/topic`)
- Same PID-based client ID scheme (avoids the `time_t` truncation
  issue on 32-bit ARM)
- Same configuration key names (`mqttAddress`, `mqttPort`, etc.)
- Same QoS default (EXACTLY_ONCE / QoS 2)
- JSON link events use the same field names as DStarGateway
  (`repeater`, `reflector`, `protocol`, `reason`, `action`)

ircDDBGateway is a **publish-only** MQTT client — it does not subscribe
to any MQTT topics or accept remote commands via MQTT.

## Troubleshooting

**"Unable to start MQTT connection" in logs:**
- Check that Mosquitto (or another MQTT broker) is running on the
  configured host and port
- Verify credentials if `mqttAuth=1`
- Check firewall rules if connecting to a remote broker

**No messages appearing:**
- Check that `mqttAddress` is not empty in the config file
- Verify the broker is accessible: `mosquitto_pub -h 127.0.0.1 -t test -m hello`
