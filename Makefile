export DATADIR := "/usr/share/ircddbgateway"
export LOGDIR  := "/var/log"
export CONFDIR := "/etc"
export BINDIR  := "/usr/bin"

export CXX     := $(shell wx-config --cxx)
export CFLAGS  := -O2 -Wall $(shell wx-config --cxxflags) -DLOG_DIR='$(LOGDIR)' -DCONF_DIR='$(CONFDIR)' -DDATA_DIR='$(DATADIR)'
export LIBS    := $(shell wx-config --libs adv,core)
export LDFLAGS := 

all:	ircDDBGateway/ircddbgateway ircDDBGatewayConfig/ircddbgatewayconfig APRSTransmit/aprstransmit RemoteControl/remotecontrol \
	StarNetServer/starnetserver TextTransmit/texttransmit TimerControl/timercontrol TimeServer/timeserver VoiceTransmit/voicetransmit

ircDDBGateway/ircddbgateway:	Common/Common.a ircDDB/IRCDDB.a
	make -C ircDDBGateway

ircDDBGatewayConfig/ircddbgatewayconfig:	GUICommon/GUICommon.a Common/Common.a
	make -C ircDDBGatewayConfig

APRSTransmit/aprstransmit:	Common/Common.a
	make -C APRSTransmit

RemoteControl/remotecontrol:	Common/Common.a GUICommon/GUICommon.a
	make -C RemoteControl

StarNetServer/starnetserver:	Common/Common.a ircDDB/IRCDDB.a
	make -C StarNetServer

TextTransmit/texttransmit:	Common/Common.a
	make -C TextTransmit

TimerControl/timercontrol:	Common/Common.a GUICommon/GUICommon.a
	make -C TimerControl

TimeServer/timeserver:	Common/Common.a GUICommon/GUICommon.a
	make -C TimeServer

VoiceTransmit/voicetransmit:	Common/Common.a
	make -C VoiceTransmit

GUICommon/GUICommon.a:
	make -C GUICommon

Common/Common.a:
	make -C Common

ircDDB/IRCDDB.a:
	make -C ircDDB

install:	all
	make -C Data install
	make -C APRSTransmit install
	make -C ircDDBGateway install
	make -C RemoteControl install
	make -C StarNetServer install
	make -C TextTransmit install
	make -C TimerControl install
	make -C TimeServer install
	make -C VoiceTransmit install
	make -C ircDDBGatewayConfig install

clean:
	make -C Common clean
	make -C ircDDB clean
	make -C GUICommon clean
	make -C APRSTransmit clean
	make -C ircDDBGateway clean
	make -C RemoteControl clean
	make -C StarNetServer clean
	make -C TextTransmit clean
	make -C TimerControl clean
	make -C TimeServer clean
	make -C VoiceTransmit clean
	make -C ircDDBGatewayConfig clean

