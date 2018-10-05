include common.mk

all:	ircDDBGateway/ircddbgatewayd

ircDDBGateway/ircddbgatewayd:	Common/Common.a ircDDB/IRCDDB.a
	make -C ircDDBGateway

ircDDBGatewayConfig/ircddbgatewayconfig:	GUICommon/GUICommon.a Common/Common.a
	make -C ircDDBGatewayConfig

APRSTransmit/aprstransmitd:	Common/Common.a
	make -C APRSTransmit

RemoteControl/remotecontrold:	Common/Common.a
	make -C RemoteControl

StarNetServer/starnetserverd:	Common/Common.a ircDDB/IRCDDB.a
	make -C StarNetServer

TextTransmit/texttransmitd:	Common/Common.a
	make -C TextTransmit

TimerControl/timercontrold:	Common/Common.a GUICommon/GUICommon.a
	make -C TimerControl

TimeServer/timeserverd:	Common/Common.a GUICommon/GUICommon.a
	make -C TimeServer

VoiceTransmit/voicetransmitd:	Common/Common.a
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

