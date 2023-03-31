export BUILD   ?= debug
ifeq ($(TARGET), opendv)
export DATADIR ?= /usr/share/opendv
export LOGDIR  ?= /var/log/opendv
export CONFDIR ?= /etc
export BINDIR  ?= /usr/sbin
else
export DATADIR ?= /usr/share/ircddbgateway
export LOGDIR  ?= /var/log
export CONFDIR ?= /etc
export BINDIR  ?= /usr/bin
endif

# Add -DDCS_LINK to the end of the CFLAGS line below to add DCS linking to StarNet
# Add -DDEXTRA_LINK to the end of the CFLAGS line below to add DExtra linking to StarNet

# Add -DUSE_GPSD to the end of the CFLAGS line to enable the use of gpsd, and add -lgps to
# end of the LIBS line.

DEBUGFLAGS     := -g -D_DEBUG
RELEASEFLAGS   := -DNDEBUG -DwxDEBUG_LEVEL=0
export CXX     := $(shell wx-config --cxx)
export CFLAGS  := -O2 -Wall $(shell wx-config --cxxflags) -DLOG_DIR='"$(LOGDIR)"' -DCONF_DIR='"$(CONFDIR)"' -DDATA_DIR='"$(DATADIR)"'
ifeq ($(BUILD), debug)
	export CFLAGS  := $(CFLAGS) $(DEBUGFLAGS)
else ifeq ($(BUILD), release)
	export CFLAGS  := $(CFLAGS) $(RELEASEFLAGS)
endif
export LIBS    := $(shell wx-config --libs base,net)
export LDFLAGS := 

.PHONY: all
all:	ircDDBGateway/ircddbgatewayd APRSTransmit/aprstransmitd RemoteControl/remotecontrold \
	StarNetServer/starnetserverd TextTransmit/texttransmitd TimerControl/timercontrold TimeServer/timeserverd VoiceTransmit/voicetransmitd

ircDDBGateway/ircddbgatewayd:	Common/Common.a ircDDB/IRCDDB.a force
	$(MAKE) -C ircDDBGateway

APRSTransmit/aprstransmitd:	Common/Common.a force
	$(MAKE) -C APRSTransmit

RemoteControl/remotecontrold:	Common/Common.a force
	$(MAKE) -C RemoteControl

StarNetServer/starnetserverd:	Common/Common.a ircDDB/IRCDDB.a force
	$(MAKE) -C StarNetServer

TextTransmit/texttransmitd:	Common/Common.a force
	$(MAKE) -C TextTransmit

TimerControl/timercontrold:	Common/Common.a force
	$(MAKE) -C TimerControl

TimeServer/timeserverd:	Common/Common.a force
	$(MAKE) -C TimeServer

VoiceTransmit/voicetransmitd:	Common/Common.a force
	$(MAKE) -C VoiceTransmit

Common/Common.a: force
	$(MAKE) -C Common

ircDDB/IRCDDB.a: force
	$(MAKE) -C ircDDB

.PHONY: installdirs
installdirs: force
	/bin/mkdir -p $(DESTDIR)$(DATADIR) $(DESTDIR)$(LOGDIR) $(DESTDIR)$(CONFDIR) $(DESTDIR)$(BINDIR)

.PHONY: install
install: all installdirs
ifeq ($(TARGET), opendv)
	useradd --user-group -M --system opendv --shell /bin/false || true

	#  Add the opendv user to the audio group so that it can open audio
	#  devices when using the audio based drivers such as the Sound Card
	#  one. Maybe this should be moved to DStarRepeater instead ...
	usermod --groups audio --append opendv || true
	usermod --groups dialout --append opendv || true
	usermod --groups gpio --append opendv || true
	mkdir /var/log/opendv || true
	chown opendv:opendv /var/log/opendv
endif
	$(MAKE) -C Data install
	$(MAKE) -C APRSTransmit install
	$(MAKE) -C ircDDBGateway install
	$(MAKE) -C RemoteControl install
	$(MAKE) -C StarNetServer install
	$(MAKE) -C TextTransmit install
	$(MAKE) -C TimerControl install
	$(MAKE) -C TimeServer install
	$(MAKE) -C VoiceTransmit install

.PHONY: clean
clean:
	$(MAKE) -C Common clean
	$(MAKE) -C ircDDB clean
	$(MAKE) -C APRSTransmit clean
	$(MAKE) -C ircDDBGateway clean
	$(MAKE) -C RemoteControl clean
	$(MAKE) -C StarNetServer clean
	$(MAKE) -C TextTransmit clean
	$(MAKE) -C TimerControl clean
	$(MAKE) -C TimeServer clean
	$(MAKE) -C VoiceTransmit clean
	$(MAKE) -C ircDDBGatewayConfig clean

.PHONY: uninstall
uninstall:
ifeq ($(TARGET), opendv)
	userdel opendv || true
	rm -r /var/log/opendv || true
	rm $(DESTDIR)/etc/systemd/system/ircddbgatewayd.service
endif
	rm -r $(DESTDIR)$(DATADIR) || true
	rm $(DESTDIR)$(BINDIR)/aprstransmitd || true
	rm $(DESTDIR)$(BINDIR)/ircddbgatewayd || true
	rm $(DESTDIR)$(BINDIR)/remotecontrold || true
	rm $(DESTDIR)$(BINDIR)/starnetserverd || true
	rm $(DESTDIR)$(BINDIR)/texttransmitd || true
	rm $(DESTDIR)$(BINDIR)/timercontrold || true
	rm $(DESTDIR)$(BINDIR)/timeserverd || true
	@echo "*** NOTE: Leaving /etc/ircddbgateway in place ***"

.PHONY: force
force :
	@true

