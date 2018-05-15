export DATADIR := "/usr/local/etc"
export LOGDIR  := "/var/log"
export CONFDIR := "/etc"

export CXX := $(shell wx-config --cxx)
export CFLAGS := -g -O2 -Wall $(shell wx-config --cxxflags) -DLOG_DIR='$(LOGDIR)' -DCONF_DIR='$(CONFDIR)' -DDATA_DIR='$(DATADIR)'
export LIBS := $(shell wx-config --libs adv,core)
export LDFLAGS := -g

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

