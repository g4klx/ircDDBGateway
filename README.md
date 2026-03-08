# ircDDBGateway

> **Note:** For new installations, consider using [DStarGateway](https://github.com/F4FXL/DStarGateway) instead. DStarGateway is an actively developed, wxWidgets-free rewrite of ircDDBGateway with additional features such as NAT traversal, RS-MS1A message forwarding, and automatic host file downloads. ircDDBGateway remains fully functional and is still in use at many sites, but DStarGateway is the recommended path forward for new deployments.

ircDDBGateway allows a D-Star repeater to interface into callsign routing via ircDDB and all of the different reflector types. It works with both [DStarRepeater](https://github.com/g4klx/DStarRepeater) (homebrew hardware) and Icom repeater stacks (ID-RP2C).

## Features

- Callsign routing via ircDDB (up to 4 networks simultaneously)
- D-Plus REF reflectors
- DExtra XRF reflectors
- DCS reflectors
- XLX reflectors
- CCS7 routing
- Supports Icom repeater stacks and homebrew repeaters
- Up to 4 repeater modules per gateway
- Icom DD mode under Linux with Internet access
- D-RATS data transfers
- DPRS to APRS-IS gateway
- Full multi-lingual text and voice announcements
- DTMF or UR call control
- Remote control interface
- STARnet digital voice server (up to 5 groups)
- Reflector usage policies
- MQTT telemetry publishing (log messages, link status events)

## Building

Builds on 32-bit and 64-bit Linux as well as on Windows using Visual Studio 2022 (x86 and x64).

### Standard Build

```
make
sudo make install
```

### With GUI Programs

```
make -f MakefileGUI
```

### MQTT Dependency

MQTT telemetry is always compiled in. Install `libmosquitto-dev` before building:

```
sudo apt-get install libmosquitto-dev
make
sudo make install
```

To disable MQTT at runtime, leave `mqttAddress` empty in the config file. See [MQTT.md](MQTT.md) for full configuration details, topic structure, and JSON format.

### Drop-in Replacement for dl5di OpenDV Packages

This compiles the program to be used as a drop-in replacement for the no longer maintained DL5DI OpenDV packages. Systemd unit files for running `ircddbgatewayd` as a daemon are also installed.

```
export TARGET=opendv
make
sudo make install
```

You may need `sudo -E make install` or `sudo TARGET=opendv make install` to pass the environment variable, depending on your system configuration.

Enable and start the service:

```
sudo systemctl enable ircddbgatewayd.service
sudo systemctl start ircddbgatewayd.service
```

To uninstall:

```
sudo systemctl disable --now ircddbgatewayd.service
sudo make uninstall
```

The uninstall will not remove your `/etc/ircddbgateway` configuration file.

## Configuration

Edit `/etc/ircddbgateway` (or `/etc/ircddbgateway_<name>` when using the `-name` option) to match your setup. An example configuration is provided in [linux/ircddbgateway.example](linux/ircddbgateway.example).

See [CONFIGURATION.md](CONFIGURATION.md) for a complete reference of all settings, defaults, and allowed values.

## ICOM Repeater Setup

If using an ICOM ID-RP2C, configure the repeater using the ICOM utility. By default the ID-RP2C uses IP address `172.16.0.1` and expects the controlling device at `172.16.0.20` with the default password `PASSWORD`. Ideally the ID-RP2C is connected directly to a secondary ethernet port on the device running `ircddbgatewayd`.

In the ICOM utility, set the port in "Communication Settings" to match the "Gateway" section port (20000 by default), then match it in Options > Network Setup.

Example configuration for a 70cm repeater on Repeater 1:

```
gatewayType=0
icomAddress=172.16.0.20
icomPort=20000
repeaterCall1=GB7XX
repeaterBand1=B
repeaterType1=1
repeaterAddress1=172.16.0.1
repeaterPort1=20000
```

## Companion Programs

Only `ircddbgatewayd` is required for basic operation. The following companion programs are also included:

| Program | Description |
|---------|-------------|
| `ircddbgatewayconfig` | GUI configuration editor |
| `texttransmit` | Send a text message via the gateway |
| `voicetransmit` | Send a voice announcement via the gateway |
| `timercontrol` | Scheduled reflector linking control |
| `timeserver` | Transmit time announcements |
| `remotecontrol` | Remote control client |
| `aprstransmit` | Send APRS data via the gateway |

## Licence

This software is licenced under the GPL v2.
