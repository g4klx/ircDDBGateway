This is the ircDDB Gateway. It allows a D-Star Repeater to interface into callsign routing via ircDDB and all of the different reflector types. It includes many facilities, including:

* Supports Icom stacks.
* Supports homebrew repeaters.
* Icom DD mode under Linux with Internet access.
* Callsign routing via ircDDB.
* D-Plus REF reflectors.
* DExtra XRF reflectors.
* DCS reflectors.
* XLX reflectors.
* CCS7 routing.
* D-RATS data transfers.
* Gateway DPRS data to APRS-IS.
* Full multi lingual text and voice announcements.
* DTMF or UR call control.
* Remote control interface.
* StarNet server.
* Ability to set policies for reflector usage.

There are many external programs that allow for inserting voice or text messages, as well as remote control operation.

They all build on 32-bit and 64-bit Linux as well as on Windows using Visual Studio 2017 on x86 and x64.

This software is licenced under the GPL v2.

# Build and installing
## Regular build
```shell
make
make -f MakefileGUI #only required if you want to build the GUI programs
sudo make install
```
## Drop-in replacement for dl5di OpenDV packages
This will conpile the program to be used as a drop in replacement for the no longer maintained DL5DI OpenDV packages. Systemd files to run ircddbgatewayd as daemon will also be installed.
```shell
export TARGET=opendv
make
make -f MakefileGUI #only required if you want to build the GUI programs
sudo make install
```
Note that you may need to use `sudo -E make install` to pass the environment variables, or just `sudo TARGET=opendv make install` to correctly create the opendv user/directories, depending on your system configuration.

Now you should edit the configuration in the file /etc/ircddbgateway to match your needs.

When building in TARGET=opendv mode, the necessary systemd unit files will be installed. To ensure ircddbgatewayd starts at system boot, and then immediately start it, use:
```shell
sudo systemctl enable ircddbgatewayd.service
sudo service ircddbgatewayd start
```

If you wish to remove the manually installed files you may use `sudo make uninstall`.
Note that this will remove the systemd unit, but will not first stop or disable the service. To do so, first use:
```shell
sudo systemctl disable --now ircddbgateway.service
```
It will also not remove your /etc/ircddbgateway configuration file.

# Setup

Only the ircddbgatewayd service is required for basic usage, all other compiled applications are optional.

## ICOM repeater configuration
If using an ICOM ID-RP2C you will need to use the ICOM utility to configure the repeater. By default the ID-RP2C uses the IP address 172.16.0.1, and expects the device controlling it (either your computer, or the computer running ircddbgatewayd) to be using the IP address 172.16.0.20, and uses the default password "PASSWORD". It may not be advisable to change this password as performing a hardware reset is not a documented feature. Ideally the ID-RP2C is connected directly to a secondary ethernet port on the device running ircddbgatewayd and configured with a static IP address, other configurations may prove problematic.

When configuring the repeater using the ICOM utility you will need to change the port in the "Communication Settings" section to use the same port as is used in the "Gateway" section (20000 by default), and then go into the Options/Network Setup menu of the ICOM app to change the port to match what you put into the "Communication Settings" section.

Once both of those fields are set to the same port number, ensure that the "Local RPT" section is set correctly for whichever physical plug your ID-RP2D is plugged into on the back of the ID-RP2C. Whichever number you have plugged in to should be set to "Voice", and have the correct band entered in the text box. ("B" for 70cm, for example.)

In your /etc/ircddbgateway config file the following options are important:
```
icomAddress=172.16.0.20
icomPort=20000
repeaterCall1=REPEATERCALLSIGN
repeaterBand1=B
repeaterType1=1
repeaterAddress=172.16.0.1
repeaterPort1=20000
```
Note that this assumes you're configuring "Repeater 1".
The repeaterAdress is the address of the ID-RP2C controller, and "icomAddress" is the address of the device running ircddbgatewayd. The "Type" being 1 indicates an ICOM repeater. The Band should be set to whichever band you entered in the "Local RPT" section of the ICOM configuration software, and the callsign should match the call used in in the ICOM software.
