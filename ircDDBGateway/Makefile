OBJECTS = IRCDDBGatewayAppD.o IRCDDBGatewayStatusData.o IRCDDBGatewayThread.o IRCDDBGatewayThreadHelper.o

.PHONY: all
all:		ircddbgatewayd

ircddbgatewayd:	$(OBJECTS) ../ircDDB/IRCDDB.a ../Common/Common.a
		$(CXX) $(OBJECTS) ../Common/Common.a ../ircDDB/IRCDDB.a $(LDFLAGS) $(LIBS) -o ircddbgatewayd

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -I../ircDDB -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common -I../ircDDB $< > $*.d

.PHONY: install
install:
		install -g bin -o root -m 0775 ircddbgatewayd $(BINDIR)
		cp ircddbgateway-emptyconfig $(CONFDIR)/ircddbgateway
ifeq ($(TARGET), opendv)
		cp ../debian/ircddbgatewayd.ircddbgatewayd.service /lib/systemd/system/ircddbgatewayd.service
endif

.PHONY: clean
clean:
		$(RM) ircddbgatewayd *.o *.d *.bak *~

../Common/Common.a:
../ircDDB/IRCDDB.a:

