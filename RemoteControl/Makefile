OBJECTS = RemoteControlAppD.o RemoteControlCallsignData.o RemoteControlConfig.o RemoteControlLinkData.o RemoteControlRemoteControlHandler.o \
	  RemoteControlRepeaterData.o RemoteControlStarNetGroup.o RemoteControlStarNetUser.o

.PHONY: all
all:		remotecontrold

remotecontrold:	$(OBJECTS) ../Common/Common.a
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o remotecontrold

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common $< > $*.d

.PHONY: install
install:
		install -g root -o root -m 0755 remotecontrold $(DESTDIR)$(BINDIR)

.PHONY: clean
clean:
		$(RM) remotecontrold *.o *.d *.bak *~

../Common/Common.a:
