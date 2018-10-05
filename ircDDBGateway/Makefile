include ../common.mk

OBJECTS = IRCDDBGatewayAppD.o IRCDDBGatewayStatusData.o IRCDDBGatewayThread.o IRCDDBGatewayThreadHelper.o

all:		ircddbgatewayd

ircddbgatewayd:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a ../ircDDB/IRCDDB.a $(LDFLAGS) $(LIBS) -o ircddbgatewayd

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -I../ircDDB -c -o $@ $<

install:
		install -g bin -o root -m 0775 ircddbgatewayd $(BINDIR)

clean:
		$(RM) ircddbgatewayd *.o *.d *.bak *~

