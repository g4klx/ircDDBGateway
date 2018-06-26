OBJECTS = RemoteControlAppD.o RemoteControlCallsignData.o RemoteControlConfig.o RemoteControlLinkData.o RemoteControlRemoteControlHandler.o \
	  RemoteControlRepeaterData.o RemoteControlStarNetGroup.o RemoteControlStarNetUser.o

all:		remotecontrold

remotecontrold:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o remotecontrold

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 remotecontrold $(BINDIR)

clean:
		$(RM) remotecontrold *.o *.d *.bak *~

