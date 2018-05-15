OBJECTS = RemoteControlApp.o RemoteControlCallsignData.o RemoteControlConfig.o RemoteControlFrame.o RemoteControlLinkData.o \
	  RemoteControlPreferences.o RemoteControlRemoteControlHandler.o RemoteControlRemoteSet.o RemoteControlRepeaterData.o \
	  RemoteControlRepeaterPanel.o RemoteControlStarNetGroup.o RemoteControlStarNetPanel.o RemoteControlStarNetUser.o

all:		remotecontrol

remotecontrol:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../GUICommon/GUICommon.a ../Common/Common.a $(LDFLAGS) $(LIBS) -o remotecontrol

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -I../GUICommon -c -o $@ $<

clean:
		$(RM) remotecontrol *.o *.d *.bak *~

